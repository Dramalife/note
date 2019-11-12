#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void kill_sig2pid(int pid, int sig)
{ 
	kill(pid,sig);//kill - send signal to a process
	printf("[%s] Send signal(%d) to pid(%d). \n",__FILE__,sig,pid);
}
