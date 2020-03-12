#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>//system()

char cmd[128];
int main(/*int argc, char *args[]*/void)
{
	int ret;

	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"echo %s,%d,%d  >> ./1.log",__func__,__LINE__,(int)time(NULL));
	ret = system(cmd);

	// 获取当前进程的PID
	pid_t pid = getpid();
	printf("pid = %d\n", pid);

	// 获取当前进程的PPID
	pid_t ppid = getppid();
	printf("ppid = %d\n", ppid);

	sprintf(cmd,"cat /proc/%d/cmdline >> ./1.log",pid);
	ret = system(cmd);
	ret = system("echo "" >> ./1.log");
	sprintf(cmd,"cat /proc/%d/cmdline >> ./1.log",ppid);
	ret = system(cmd);
	ret = system("echo "" >> ./1.log");

	if(ret)
	{
	
	}

	return 0;
}

