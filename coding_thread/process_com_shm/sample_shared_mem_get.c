/*
Date ： 2019/03/13

source url :
  https://www.cnblogs.com/liunianshiwei/p/6110384.html
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<errno.h>

typedef struct _Teacher
{
    char name[64];
    int age;
}Teacher;

int main(int argc, char *argv[])
{
    int ret = 0;
    int    shmid;
    //shmid = shmget(0x2234, sizeof(Teacher), IPC_CREAT |IPC_EXCL | 0666);
    //打开获取共享内存
    shmid = shmget(0x2234, 0, 0);
    if (shmid == -1)
    {
        perror("shmget err");
        return errno;
    }
    printf("shmid:%d \n", shmid);
    Teacher *p = NULL;
    //将共享内存段连接到进程地址空间
    p = shmat(shmid, NULL, 0);
    if (p == (void *)-1 )
    {
        perror("shmget err");
        return errno;
    }

    printf("name:%s\n", p->name);
    printf("age:%d \n", p->age);
    //将共享内存段与当前进程脱离
    shmdt(p);

    printf("键入1 程序暂停，其他退出\n");

    int num;
    scanf("%d", &num);
    if (num == 1)
    {
        pause();
    }
    return 0;
}
