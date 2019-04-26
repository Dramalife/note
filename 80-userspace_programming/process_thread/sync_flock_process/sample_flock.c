/*
Title : Process sync - file lock
Date : 2019.03.14
source url : (https://blog.csdn.net/qq_35396127/article/details/78942245)
*/
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

void sys_err(char*str)
{
    perror(str);
    exit(1);
}


int main(int argc,char *argv[])
{
    int fd;
    struct flock f_lock;

    if( argc< 2 )
    {
        printf("./a.out filename\n");
        exit(1);
    }

    if( ( fd = open(argv[1],O_RDWR)) < 0 )
        sys_err("open");

//    f_lock.l_type = F_WRLCK;          // 选用写锁
    f_lock.l_type = F_RDLCK;            // 选用读锁
    f_lock.l_whence = 0;
    f_lock.l_len = 0;                 // 0 表示整个文件加锁

    fcntl(fd,F_SETLKW,&f_lock);
    printf("get flock\n");

    sleep(10);

    f_lock.l_type = F_UNLCK;
    fcntl(fd,F_SETLKW,&f_lock);
    printf("un flock\n");

    close(fd);
    return 0;
}
