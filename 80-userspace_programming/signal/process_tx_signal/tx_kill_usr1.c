#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void kill_pid_sig(int pid, int sig)
{ 
	kill(pid,sig);//kill - send signal to a process
	printf("[%s] Send signal(%d) to pid(%d). \n",__FILE__,sig,pid);
}

int main(int argc, char **argv)
{ 
	int pid_target,ret;

	printf("[%s] argc(%d),argv1(%s) \n",__FILE__,argc,*argv);

	if(argc < 2)
	{
		printf("[%s] Input rxer`spid: \n",__FILE__);
		ret = scanf("%d", &pid_target);
		printf("[%s] scanf-ret(%d) \n",__FILE__,ret);
	}
	else if(argc == 2)
	{
		pid_target = atoi(argv[1]);
	}

	kill_pid_sig(pid_target, SIGUSR1);

	return 0;

}
