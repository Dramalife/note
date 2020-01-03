/* >>> man waitpid <<<
NOTES
A  child  that terminates, but has not been waited for becomes a "zombie".  The kernel maintains a minimal set of information about the zombie process (PID, termination
status, resource usage information) in order to allow the parent to later perform a wait to obtain information about the child.  As long as a zombie is not removed from
the  system  via  a wait, it will consume a slot in the kernel process table, and if this table fills, it will not be possible to create further processes.  If a parent
process terminates, then its "zombie" children (if any) are adopted by init(8), which automatically performs a wait to remove the zombies.

POSIX.1-2001 specifies that if the disposition of SIGCHLD is set to SIG_IGN or the SA_NOCLDWAIT flag is set for SIGCHLD (see sigaction(2)), then children that terminate
do  not  become  zombies  and  a call to wait() or waitpid() will block until all children have terminated, and then fail with errno set to ECHILD.  (The original POSIX
standard left the behavior of setting SIGCHLD to SIG_IGN unspecified.  Note that even though the default disposition of SIGCHLD is "ignore", explicitly setting the dis‐
position  to  SIG_IGN results in different treatment of zombie process children.)  Linux 2.6 conforms to this specification.  However, Linux 2.4 (and earlier) does not:
if a wait() or waitpid() call is made while SIGCHLD is being ignored, the call behaves just as though SIGCHLD were not being ignored, that is, the call blocks until the
next child terminates and then returns the process ID and status of that child.
*/

/* Dramalife@live.com, 20190601 */
/* KEYWORDS : vfork, waitpid, execve */

/* COMPILE
 * $ gcc vfork_exec_wait_ping.c -I ../../../lib_dramalife/
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

//#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <lib_dramalife.h>
//#include <terminal_color_dramalife.h>
#define YELLOW	CYELLOW
#define CYAN	CCYAN

#define pxxg_send_flag_reset(st) do{st->ping_stage = 0;st->ping_timeout_cnt = 0;}while(0)

struct pxxg_st
{
	int index;
#define DL_PING_STAGE_INIT	
	int	ping_stage;
	
	int 	ping_timeout_cnt;
	time_t 	ping_start_time;

	pid_t 	ping_pid;	/* emergency brake */

	int	ping_cnt;	/* ping -c */
	char	ping_iface[16];	/* ping -I */
	char	ping_host[24];	/* HOST ip address */
};

struct pxxg_st pst;

int pxxg_send_start(struct pxxg_st *st)
{
	int i;
	char cnt[16];
	sprintf(cnt,"%d",st->ping_cnt);

	st->ping_stage = 1;

	for (i = 0; i < 1; ++i)
	{
		if ((st->ping_pid = vfork()) < 0)/* FORK ERR */
		{
			printf("vfork error");
			continue;
		}

		if (st->ping_pid == 0)/* CHILD */
		{
			st->ping_stage = 2;

			printf("if:%s,ip:%s,cnt:%s \n",st->ping_iface, st->ping_host, cnt);

			/* memory changes would be visible in the parent, 
			 * but changes to the state of open file descriptors  would
			 * not be visible. --vfork(2)
			 */
			int fd = open("/dev/null", O_RDWR | O_NONBLOCK | O_NOCTTY);
			if (fd >= 0) { 
				dup2(fd, STDIN_FILENO);
				dup2(fd, STDOUT_FILENO);
				//xmove_fd(fd, STDERR_FILENO);
				close(fd);
			}    

			if ( execlp("busybox","busybox",  "ping", "-c", cnt, "-I", st->ping_iface , st->ping_host ,
			//"-q",
			NULL) < 0)
			{
				printf("execlp error\n");
				exit(1);
			}
			st->ping_stage = 3;
		}

	}

	printf("\n%d \n",(int)time(NULL));
	return -1;
}

void pxxg_stop_send(struct pxxg_st *st)
{
	//kill(st->ping_pid, SIGKILL);//WEXITSTATUS = 0
	kill(st->ping_pid, SIGQUIT);//WEXITSTATUS = 0
	//system("kill -9 $(pidof ping) 1>/dev/null 2>&1");
	pxxg_send_flag_reset(st);
}

int pxxg_result_record(int arg_result,int arg_unuse)
{
	printf("%s,%d,arg0:%d,arg1:%d \n",__func__, __LINE__, arg_result, arg_unuse);
	return 0;
}


int pxxg_send_is_exit( int(*handle)(int,int),  int status, struct pxxg_st *st)
{
	int ret = -1;
	pxxg_send_flag_reset(st);

	if( WIFEXITED(status) )/* returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main(). */
	{
		printf("The process[pid:%d] normally exit, status:[%d] \n", st->ping_pid ,WEXITSTATUS(status));
		if(0 == WEXITSTATUS(status))
		{
			printf(CGREEN"ping ok " CNONE "\n");
			ret = 0;
		}
		else
		{
			printf(CRED"ping err "CNONE"\n");
			ret = 1;
		}
	}
	else if( WIFSIGNALED(status) )/* returns true if the child process was terminated by a signal. */
	{
		printf( "SIGNAL[%d] caused the child process[pid:%d] to terminate \n",WTERMSIG(status), st->ping_pid );
		printf(YELLOW"ping result unuseful "CNONE"\n");
		ret = 2;
	}
	if(ret > -1)
	{
		(*handle)(ret,888);
	}
	return ret;
}


int rc_pxxg_send(char *bind_ifname, char *monitor_ip, int p_count)
{

	strcpy(pst.ping_iface, bind_ifname);
	strcpy(pst.ping_host, monitor_ip);
	pst.ping_cnt = p_count;

	pxxg_send_start( (&pst) );/* SEND */
}

int
main(int argc, char *argv[])
{
	int status;

	pst.ping_timeout_cnt = 0; 
	pst.ping_stage = 0;
	strcpy(pst.ping_iface, argv[1]);
	strcpy(pst.ping_host,argv[2]);
	pst.ping_cnt = atoi(argv[3]);

/*  */
//signal(SIGCHLD,SIG_DFL);

/* ignore child signal */
signal(SIGCHLD,SIG_IGN);

	rc_pxxg_send(argv[1],argv[2],atoi(argv[3]));

	pst.ping_start_time = time(NULL);

	while(1)/* zebra master fetch */
	{
		sleep(1);
		/* Add to main loop, start */
		//MAIN LOOP [*][ ]
		printf(CGREEN"cl ,RUN:%d\n" CNONE "\n", pst.ping_timeout_cnt);
		//MAIN LOOP [*][*]
		if( pst.ping_stage != 0 )
		{
			pst.ping_timeout_cnt++;
		}

		if( 0 < waitpid(pst.ping_pid, &status, WNOHANG) )
		{
			if( WIFEXITED(status) )/* returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main(). */
			{
				printf("The process[pid:%d] normally exit, status:[%d] \n", pst.ping_pid ,WEXITSTATUS(status));
				if(0 == WEXITSTATUS(status))
				{
					printf(CGREEN"ping ok " CNONE "\n");
				}
				else
				{
					printf(CRED"ping err "CNONE"\n");
				}
			}
			else if( WIFSIGNALED(status) )/* returns true if the child process was terminated by a signal. */
			{
				printf( "SIGNAL[%d] caused the child process[pid:%d] to terminate \n",WTERMSIG(status), pst.ping_pid );
				printf(YELLOW"ping result unuseful "CNONE"\n");
			}
			//goto done;
			rc_pxxg_send(argv[1],argv[2],atoi(argv[3]));
		}
		if( (0 == pst.ping_stage) && (0 == pst.ping_timeout_cnt))
		{
			//TODO : change cfg
			//rc_pxxg_send("eth0","172.16.127.200",3);
		}
		if( pst.ping_timeout_cnt > 10 )/* TIMEOUT */
		{
			printf(CYAN"ping_stage:%d,ping_timeout_cnt:%d" CNONE "\n", pst.ping_stage, pst.ping_timeout_cnt);
			pxxg_stop_send(&pst);
		}
		/* Add to main loop, end */
	}

	printf("done \n");
	return 0;
}
//sudo ./a.out eth0 172.16.127.200 1

