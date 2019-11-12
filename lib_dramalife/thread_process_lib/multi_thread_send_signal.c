#include <stdio.h>
#include <pthread.h>

//signal
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

extern void kill_sig2pid(int pid, int sig);

#define C_START	1
#define C_END	0
void child_print(pthread_t tid, pthread_t vt_pid, unsigned char stage)
{
	printf(
#if (defined __x86_64__) && (1 == __x86_64__)
			"[%s,%d]thread (%ld) %s, target-pid(%ld). \n",__func__,__LINE__
#else
			"[%s,%d]thread (%d) %s, target-pid(%d). \n",__func__,__LINE__
#endif
			,tid
			,(stage==C_START)?"start":"end"
			,vt_pid
	      );
}

#define MMM	10
void *child1(void *arg)
{
	int i;
	pthread_t tid=pthread_self();
	pthread_t *t_pid = (pthread_t *)arg;

	child_print(tid,*t_pid,C_START);
	for(i=0;i<MMM;i++)
		kill_sig2pid(*t_pid,SIGSEGV);
	child_print(tid,*t_pid,C_END);
}
void *child2(void *arg)
{
        int i;
	pthread_t tid=pthread_self();
	pthread_t *t_pid = (pthread_t *)arg;

	child_print(tid,*t_pid,C_START);
	for(i=0;i<MMM;i++)
		kill_sig2pid(*t_pid,SIGILL);
	child_print(tid,*t_pid,C_END);
}

int main(int argc, char **argv)
{
        pthread_t tid1,tid2;
	pthread_t target_pid;

	target_pid = atoi(argv[1]);

#if (defined __x86_64__) && (1 == __x86_64__)
        printf("[%s,%d]target_pid(%ld) \n",__func__,__LINE__,target_pid);
#else
        printf("[%s,%d]target_pid(%d) \n",__func__,__LINE__,target_pid);
#endif

        pthread_create(&tid1,NULL,child1,(void *)&target_pid);
        pthread_create(&tid2,NULL,child2,(void *)&target_pid);

	while(1)
	;

        return 0;
}
