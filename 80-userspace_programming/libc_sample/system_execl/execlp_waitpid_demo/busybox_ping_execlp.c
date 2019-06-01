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


#include <terminal_color_dramalife.h>

#define pxxg_send_flag_reset(st) do{st->flag_run = 0;st->already_run = 0;}while(0)

struct pxxg_st
{
	int index;
	int flag_run;
	
	int already_run;
	time_t time_pxxg;

	pid_t pid_of_ping;	/* emergency brake */

	int ping_c;		/* ping -c */
	char ping_i[16];	/* ping -I */
	char ping_des_ip[24];	/* ipaddr  */
};

struct pxxg_st pst;

int pxxg_send_start(struct pxxg_st *st)
{
	int i;
	char cnt[16];
	sprintf(cnt,"%d",st->ping_c);

	st->flag_run = 1;

	for (i = 0; i < 1; ++i)
	{
		if ((st->pid_of_ping = vfork()) < 0)/* FORK ERR */
		{
			printf("vfork error");
			continue;
		}

		if (st->pid_of_ping == 0)/* CHILD */
		{
			st->flag_run = 2;

			printf("if:%s,ip:%s,cnt:%s \n",st->ping_i, st->ping_des_ip, cnt);
			int fd = open("/dev/null", O_RDWR | O_NONBLOCK | O_NOCTTY);
			if (fd >= 0) { 
				dup2(fd, STDIN_FILENO);
				dup2(fd, STDOUT_FILENO);
				//xmove_fd(fd, STDERR_FILENO);
				close(fd);
			}    

			if ( execlp("busybox","busybox",  "ping", "-c", cnt, "-I", st->ping_i , st->ping_des_ip ,
			//"-q",
			NULL) < 0)
			{
				printf("execlp error\n");
				exit(1);
			}
			st->flag_run = 3;
		}

	}

	printf("\n%d \n",(int)time(NULL));
	return -1;
}

void pxxg_stop_send(struct pxxg_st *st)
{
	//kill(st->pid_of_ping, SIGKILL);//WEXITSTATUS = 0
	kill(st->pid_of_ping, SIGQUIT);//WEXITSTATUS = 0
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
		printf("The process[pid:%d] normally exit, status:[%d] \n", st->pid_of_ping ,WEXITSTATUS(status));
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
		printf( "SIGNAL[%d] caused the child process[pid:%d] to terminate \n",WTERMSIG(status), st->pid_of_ping );
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

	strcpy(pst.ping_i, bind_ifname);
	strcpy(pst.ping_des_ip, monitor_ip);
	pst.ping_c = p_count;

	pxxg_send_start( (&pst) );/* SEND */
}

int
main(int argc, char *argv[])
{
	int status;

	pst.already_run = 0; 
	pst.flag_run = 0;
	strcpy(pst.ping_i, argv[1]);
	strcpy(pst.ping_des_ip,argv[2]);
	pst.ping_c = atoi(argv[3]);

//signal(SIGCHLD,SIG_DFL);
signal(SIGCHLD,SIG_IGN);

	rc_pxxg_send(argv[1],argv[2],atoi(argv[3]));

	pst.time_pxxg = time(NULL);

	while(1)/* zebra master fetch */
	{
		sleep(1);
		/* Add to main loop, start */
		//MAIN LOOP [*][ ]
		printf(CGREEN"cl ,RUN:%d\n" CNONE "\n", pst.already_run);
		//MAIN LOOP [*][*]
		if( pst.flag_run != 0 )
		{
			pst.already_run++;
		}

		if( 0 < waitpid(pst.pid_of_ping, &status, WNOHANG) )
		{
			if( WIFEXITED(status) )/* returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main(). */
			{
				printf("The process[pid:%d] normally exit, status:[%d] \n", pst.pid_of_ping ,WEXITSTATUS(status));
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
				printf( "SIGNAL[%d] caused the child process[pid:%d] to terminate \n",WTERMSIG(status), pst.pid_of_ping );
				printf(YELLOW"ping result unuseful "CNONE"\n");
			}
			//goto done;
			rc_pxxg_send(argv[1],argv[2],atoi(argv[3]));
		}
		if( (0 == pst.flag_run) && (0 == pst.already_run))
		{
			//TODO : change cfg
			//rc_pxxg_send("eth0","172.16.127.200",3);
		}
		if( pst.already_run > 10 )/* TIMEOUT */
		{
			printf(CYAN"flag_run:%d,already_run:%d" CNONE "\n", pst.flag_run, pst.already_run);
			pxxg_stop_send(&pst);
		}
		/* Add to main loop, end */
	}

	printf("done \n");
	return 0;
}
//sudo ./a.out eth0 172.16.127.200 1

