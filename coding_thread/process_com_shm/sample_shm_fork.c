#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>

#define SIZE 1024

int main()
{
        int shmid;
        char *shmaddr;
        struct shmid_ds buf;
        int flag = 0;
        int pid;
        //创建共享内存
        shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT|0600);
        if ( shmid < 0 )
        {
                perror("get shm ipc_id error");
                return -1;
        }
        //创建子进程 调用fork会返回两次 父进程返回创建的进程，子进程返回0
        pid = fork();
        if( pid == 0 )
        {//子进程
                //将共享内存映射到本地进程
                shmaddr = (char *)shmat(shmid, NULL, 0);
                if( (int)shmaddr == -1 )
                {
                        perror("shmat addr error");
                        return -1;
                }

                strcpy( shmaddr, "Hi,I am child process!\n");
                //断开映射
                shmdt( shmaddr);
                return 0;
        }
        else if( pid > 0 )
        {//父进程
                //可能会出现父进程比子进程提前结束执行，所以，延迟等待子进程先执行完
                sleep(3);
                //得到共享内存的状态，把共享内存的shmid_ds结构复制到buf中
                flag = shmctl ( shmid, IPC_STAT, &buf);
                if( flag == -1 )
                {
                        perror("shmctl shm error");
                        return -1;
                }

                printf("shm_segsz=%d bytes\n", buf.shm_segsz);
                printf("parent pid=%d,shm_cpid=%d\n",getpid(),buf.shm_cpid);
                printf("chlid pid=%d,shm_lpid=%d\n",pid,buf.shm_lpid);
                //把共享内存映射到本地
                shmaddr = (char *)shmat(shmid, NULL, 0);
                if( (int)shmaddr == -1 )
                {
                        perror("shmat addr error");
                        return -1;
                }
                printf("%s",shmaddr);
                //断开共享内存连接
                shmdt(shmaddr);
                //删除共享内存
                shmctl(shmid,IPC_RMID,NULL);
        }
        else
        {
                perror("fork error");
                shmctl(shmid,IPC_RMID,NULL);
        }
        return 0;
}
