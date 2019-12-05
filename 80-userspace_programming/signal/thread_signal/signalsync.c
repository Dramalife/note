/*
 * note "signal - thread" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 *
 * $ uname -a
 * Linux server 4.15.0-70-generic #79-Ubuntu SMP Tue Nov 12 10:36:11 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : 2019.12.03
 *	COPY FROM BarrySong/training/thread/signalsync.c ;
 * Update : 2019.12.03
 *	Format ;
 * Update : 2019.12.05
 *	Add description of function "pthread_detach" form manual page ;
 *	Replace some functions with macros ;
 * Update 
 *
 */



#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>


#define SEND_PRINT_SIGNAL(p,s,i)	do{						\
	kill(p, s);									\
	printf(										\
	"[%s,%d] "                                                                      \
	"Process(%d) send(%s) to pid(%d), cnt(%d)\n"                                    \
	,__func__,__LINE__								\
	, getpid(), #s, p, i);								\
}while(0)

#define RECV_PRINT_SIGNAL(p,s,c)	do{						\
	printf("[%s,%d] "                                                               \
	"Thread(%d) receive(%d), cnt(%d) \n"                                            \
	,__func__,__LINE__                                                              \
	, p, s, *c);									\
	(*c)++;										\
}while(0)

void sig_handler(int signum)
{
	int *cnt = NULL;
	static int j = 0;
	static int k = 0;

	/* used to show which thread the signal is handled in. */
	pthread_t  pid_thread = pthread_self();

	if(0)
	{
	}
	else if(signum == SIGUSR1)
	{
		cnt = &j;
	}
	else if(signum == SIGRTMIN)
	{
		cnt = &k;
	}
	else
	{
		cnt = NULL;
	}

	if(cnt)
	{
		RECV_PRINT_SIGNAL(pid_thread, signum, cnt);
	}
}

void* worker_thread()
{
	pthread_t  ppid = pthread_self();

	/*
	 * The  pthread_detach()  function  marks  the  thread  identified  by thread as detached.  \
	 * When a detached thread terminates, its resources are automatically
	 * released back to the system without the need for another thread to \
	 * join with the terminated thread.
	 * --man 3 pthread_detach
	 */
	pthread_detach(ppid);

	while (1) 
	{
		printf(
				"[%s,%d] "
				"thread(%d) running... \n"
				,__func__,__LINE__
				,ppid
		      );
		sleep(10);
	}
}

void* sigmgr_thread()
{
	sigset_t   waitset;
	siginfo_t  info;
	int        rc;
	pthread_t  ppid = pthread_self();

	/*
	 * The  pthread_detach()  function  marks  the  thread  identified  by thread as detached.  \
	 * When a detached thread terminates, its resources are automatically
	 * released back to the system without the need for another thread to \
	 * join with the terminated thread.
	 * --man 3 pthread_detach
	 */
	pthread_detach(ppid);

	sigemptyset(&waitset);
	sigaddset(&waitset, SIGRTMIN);
	sigaddset(&waitset, SIGUSR1);

	while (1)  
	{
		rc = sigwaitinfo(&waitset, &info);
		if (rc != -1) 
		{
#if 0
			printf(
					"[%s,%d] "
					"fetch signal(%d) \n"
					,__func__,__LINE__
					,rc
			      );
#endif
			sig_handler(info.si_signo);
		} else 
		{
			printf("sigwaitinfo() returned err: %d; %s\n", errno, strerror(errno));
		}
	}
}


int main()
{
	sigset_t set, oldset;
	int             i;
	pid_t           pid = getpid();
	pthread_t       ppid;


	/* Block SIGRTMIN and SIGUSR1 which will be handled in
	 * dedicated thread sigmgr_thread()
	 * Newly created threads will inherit the pthread mask from its creator
	 */
	sigemptyset(&set);
	sigaddset(&set, SIGRTMIN);
	sigaddset(&set, SIGUSR1);

	/* A new thread inherits a copy of its creator's signal mask. */
	if (pthread_sigmask(SIG_BLOCK, &set, &oldset) != 0)
	{
		printf("!! Set pthread mask failed\n");
	}

	/* Create the dedicated thread sigmgr_thread() which will handle
	 * SIGUSR1 and SIGRTMIN synchronously
	 */
	pthread_create(&ppid, NULL, sigmgr_thread, NULL);

	/* Create 5 worker threads, which will inherit the thread mask of
	 * the creator main thread
	 */
	for (i = 0; i < 5; i++) 
	{
		pthread_create(&ppid, NULL, worker_thread, NULL);
	}

	/* send out 50 SIGUSR1 and SIGRTMIN signals */
	for (i = 0; i < 50; i++) 
	{
		SEND_PRINT_SIGNAL(pid, SIGUSR1, i);
		SEND_PRINT_SIGNAL(pid, SIGRTMIN, i);
		sleep(5);
	}
	exit (0);
}

