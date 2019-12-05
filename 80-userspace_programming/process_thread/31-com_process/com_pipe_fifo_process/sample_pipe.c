/*
单个进程中的管道几乎没有任何用处。
所以，通常调用 pipe 的进程接着调用 fork，这样就创建了父进程与子进程之间的 IPC 通道。
若要数据流从父进程流向子进程，则关闭父进程的读端（fd[0]）与子进程的写端（fd[1]）；
反之，则可以使数据流从子进程流向父进程。
*/
#include<stdio.h>
#include<unistd.h>

int main()
{
  int fd[2];  // 两个文件描述符
  pid_t pid;
  char buff[20];

  if(pipe(fd) < 0)  // 创建管道
  printf("Create Pipe Error!\n");

  if((pid = fork()) < 0)  // 创建子进程
  printf("Fork Error!\n");
  else if(pid > 0)  // 父进程
  {
    close(fd[0]); // 关闭读端
    write(fd[1], "hello world\n", 12);
  }
  else
  {
    close(fd[1]); // 关闭写端
    read(fd[0], buff, 20);
    printf("%s", buff);
  }

  return 0;
}
