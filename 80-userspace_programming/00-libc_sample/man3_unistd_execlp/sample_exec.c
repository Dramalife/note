#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char num_a[64];
char timeout_a[64];
char block_a[64];
int main(void)
{
	int num = 6;
	int timeout = 20;
	int block = 56;
	char addr [64];


	sprintf(num_a,"%d",num);
	sprintf(timeout_a, "%d",timeout);
	sprintf(block_a,"%d",block);
	sprintf(addr, "8.8.8.8");

	char argvv[8][64] = {0};
	printf("%s,%d \n",__func__,__LINE__);
	strcpy(argvv[0], "-c");
	printf("%s,%d \n",__func__,__LINE__);
	strcpy(argvv[1], num_a);
	strcpy(argvv[2], "-w");
	printf("%s,%d \n",__func__,__LINE__);
	strcpy(argvv[3], timeout_a);
	strcpy(argvv[4], "-s");
	printf("%s,%d \n",__func__,__LINE__);
	strcpy(argvv[5], block_a);
	printf("%s,%d (%s)\n",__func__,__LINE__,addr);
	//strcpy(argvv[6], addr);
	strncpy(argvv[6], addr, strlen(addr));
	printf("%s,%d \n",__func__,__LINE__);
	strcpy(argvv[7], "-q");
	printf("%s,%d \n",__func__,__LINE__);

	pid_t pid = fork();
	switch(pid)
	{
		case -1:
			perror("fork");
			break;
		case 0:
			printf("child\n");
			if( execlp("ping","ping", "-c", num_a, "-w", timeout_a, "-s", block_a, addr, "-q", NULL) < 0)
				//if( execlp("ping","ping", "-c", "7", "-w", "18", "-s", "64", "8.8.8.8", "-q", NULL) < 0)
				//if(execve("/bin/ping", argvv,NULL) < 0)
				//if( execlp("ping","ping", "-c", num, "-w", timeout, "-s", block, addr, "-q", NULL) < 0)
				//if( execlp("busybox","busybox","ping", "-c", num_a, "-I", "enp0s3", addr, "-q", NULL) < 0)
				perror("execlp");
			exit(1);
		default:
			while(1)
			{
			}
			break;
	}

	return 0;
}
