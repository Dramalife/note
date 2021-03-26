/*
 * OS Shell
 * 2020.04.21
 *
 */


#include "dl_port.h"
#ifndef _DL_PORT_H_

/* Debug print switch */
#define DEBUG_SWITCH	0

/* Print function */
#define debug_out(x,...)	do{if(DEBUG_SWITCH) printf("[%s,%d] ",__func__,__LINE__);printf(x,##__VA_ARGS__);}while(0)
//#define debug_out(x,...)	do{if(DEBUG_SWITCH) printf(x,##__VA_ARGS__);}while(0)

/* SIZE */
#define GENERAL_BUFF_SIZE	1024
#define	MAX_ARG_NUM		100
#define COMMAND_LINE_MAX_LEN	80	// 3.2 -1
#define HISTORY_CONTENT_SIZE	64
#define MAX_PID_RECORD	5
/* task control - status */
#define S_RUNNING	1// - run background
#define S_STOPPED 	2//- ctrl + z
#define S_TERM		3// CTRL +C
#define S_FG		4
#define S_BG		5

/* hostname enable */
#undef ENABLE_USERNAME_HOSTNAME
#ifndef ENABLE_USERNAME_HOSTNAME
#define ENABLE_USERNAME_HOSTNAME	1
#endif

/* Headers */
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#ifdef ENABLE_USERNAME_HOSTNAME
#include <pwd.h>
#endif




/* function declearation */
int show_cmd_line_prompt(void);
int handler_exit(char *arg);
int handler_show(char *arg);
int handler_status(char *arg);
int handler_chdir(char *arg);
int handler_pid(char *arg);
int show_all_task(char *arg);
int handler_fg(char *arg);
int handler_bg(char *arg);
int cmd_show_history_list(void);
int task_manage_sig_handler(pid_t pid, int signal);
int handler_watchuser(char *arg);

int status_wait = -1;

struct task_os_shell_st *task_new(pid_t pid, int status);

/* datastruct : built-in command */
#define HANDLE_VAR_NAME	handler
#define BUILTIN_ST_NAME	builtin_cmd_st
struct BUILTIN_ST_NAME
{
#define BTTYPE_OSSHELL	1
#define BTTYPE_SIMPLE	2
	int type; // os_shell OR simple_shell, difference : arg(char ** | char *)
	char *cmd;
	int (*HANDLE_VAR_NAME)(char *);
};
/* cmd history - link list */
struct list_st
{
	char *content[HISTORY_CONTENT_SIZE];
	struct list_st *next;
};
struct task_os_shell_st
{
	int no;// [0]
	pid_t pid;// <PID>
	int status;// "Stopped"
	int need_wait;
	struct task_os_shell_st *next;
};
struct signal_status_st
{
	int signal;
	int status;
	char *string
};
#else
#include "dl_builtin.h"
#endif



/*****
 * Built-in : watchuser 
 * File : showusers.c
 */
pthread_t tid_watchuser = -1;
extern int watchuser_main(int argc, char **argv);
struct st_builtin_watchuser
{
	char name[GENERAL_BUFF_SIZE];
	struct st_builtin_watchuser *next;
};
struct st_builtin_watchuser gv_watchuser_care;




struct BUILTIN_ST_NAME builtin_cmd[]=
{
	{.type=BTTYPE_OSSHELL,		.cmd="exit",			.HANDLE_VAR_NAME=handler_exit},
	{.type=BTTYPE_OSSHELL,		.cmd="show",			.HANDLE_VAR_NAME=handler_show},
	{.type=BTTYPE_OSSHELL,		.cmd="status",			.HANDLE_VAR_NAME=handler_status},
	{.type=BTTYPE_OSSHELL,		.cmd="history",			.HANDLE_VAR_NAME=cmd_show_history_list},
	{.type=BTTYPE_OSSHELL,		.cmd="go",				.HANDLE_VAR_NAME=handler_chdir},
	//{.type=BTTYPE_OSSHELL,		.cmd="pid",				.HANDLE_VAR_NAME=handler_pid},
	{.type=BTTYPE_OSSHELL,		.cmd="jobs",			.HANDLE_VAR_NAME=show_all_task},
	{.type=BTTYPE_OSSHELL,		.cmd="fg",				.HANDLE_VAR_NAME=handler_fg},
	{.type=BTTYPE_OSSHELL,		.cmd="continue",			.HANDLE_VAR_NAME=handler_fg},
	{.type=BTTYPE_OSSHELL,		.cmd="bg",				.HANDLE_VAR_NAME=handler_bg},

	/// Simple Shell (mysh) Start
	{.type=BTTYPE_SIMPLE,		.cmd="exit",	.HANDLE_VAR_NAME=dlfun_exit},	
	{.type=BTTYPE_SIMPLE,		.cmd="cd",	.HANDLE_VAR_NAME=dlfun_cd},	
	/* Both which and where will start searching for the target from the front of the path/PATH value. */
	{.type=BTTYPE_SIMPLE,		.cmd="where",	.HANDLE_VAR_NAME=dlfun_where},	
	{.type=BTTYPE_SIMPLE,		.cmd="pwd",	.HANDLE_VAR_NAME=dlfun_pwd},	
	//{.type=BTTYPE_SIMPLE,		.cmd="ls",	.HANDLE_VAR_NAME=dlfun_list},	
	{.type=BTTYPE_SIMPLE,		.cmd="list",	.HANDLE_VAR_NAME=dlfun_list},	
	{.type=BTTYPE_SIMPLE,		.cmd="pid",	.HANDLE_VAR_NAME=dlfun_pid_of_the_shell},	
	{.type=BTTYPE_SIMPLE,		.cmd="kill",	.HANDLE_VAR_NAME=dlfun_kill},	
	{.type=BTTYPE_SIMPLE,		.cmd="prompt",	.HANDLE_VAR_NAME=dlfun_prompt},	
	{.type=BTTYPE_SIMPLE,		.cmd="printenv",	.HANDLE_VAR_NAME=dlfun_printenv},	
	{.type=BTTYPE_SIMPLE,		.cmd="setenv",	.HANDLE_VAR_NAME=dlfun_setenv},
	{.type=BTTYPE_SIMPLE,		.cmd="set",    .HANDLE_VAR_NAME=dlfun_setvar},
	/// Simple Shell (mysh) End
	{.type=BTTYPE_SIMPLE,		.cmd="watchuser",		.HANDLE_VAR_NAME = handler_watchuser},
	{.type=BTTYPE_OSSHELL,		.cmd="which",			.HANDLE_VAR_NAME = builtin_which},
	{.type=BTTYPE_OSSHELL,		.cmd="test",			.HANDLE_VAR_NAME=NULL},
	{.type=BTTYPE_OSSHELL,		.cmd=NULL,				.HANDLE_VAR_NAME=NULL},
};

struct signal_status_st sig_sta[]=
{
	{SIGINT,	S_TERM,		"Terminated"},
	{SIGTSTP,	S_STOPPED,	"Stopped"},
	{SIGCONT,	S_RUNNING,	"Running"},
	{0 ,	S_FG,	"Frong-ground"},
	{0 ,	S_BG,	"Back-ground"},
	{0, 0, NULL},
};
struct task_os_shell_st* task_head;
struct list_st *history_head;


// 8888
pid_t last5pid [MAX_PID_RECORD] = {0};
int index5pid = 0;
int flag_pause = 0;
int flag_recept = 1;


/* history - add record (link list) */
int cmd_add_history_link_list(char *buff)
{
	struct list_st *pnow = NULL;
	struct list_st *new = NULL;

	pnow = history_head;

	while( NULL != (pnow->next) )
	{
		pnow = pnow->next;
	}

	new = (struct list_st *)malloc(1 * sizeof(struct list_st));
	strncpy(new->content, buff, sizeof(new->content));
	pnow->next = new;
	new->next = NULL;

	return 0;
}
int cmd_show_history_list(void)
{
	struct list_st *ptr = history_head;

	while( NULL != (ptr->next) )
	{
		debug_out("%s\n",ptr->content);
		ptr = ptr->next;
	}
	debug_out("%s\n",ptr->content);
}
/* cmd history - link list init */
int init_history_list(struct list_st **head)
{
	*head = (struct list_st *)malloc(1 * sizeof(struct list_st));
	memset((*head)->content, 0, sizeof((*head)->content));
	(*head)->next = NULL;
	return (*head)?0:-1;
}

/* 3.2 CMD - pid */
void update5pid(pid_t pid)
{
	last5pid[index5pid] = pid;
	index5pid++;
	if (index5pid >= MAX_PID_RECORD )
		index5pid = 0;
	task_new(pid, S_RUNNING);
	return;
}
/* handler of cmd - pid */
int handler_pid(char *arg)
{
	int index = 0;
	for(index = (MAX_PID_RECORD-1); index >= 0; index--)
	{
		if( 0 != last5pid[index])
			debug_out("[%d] %d\n",index+1,last5pid[index]);
	}
	return 0;
}
/* welcom & help info print */
void show_welcom(void)
{
	debug_out(
			"GCC VERSION (%s) \n"
			"COMPILE DATE (%s) \n"
			,__VERSION__,__DATE__
		 );
	debug_out(
			"\n**********************\n"
			"Redirection : \n"
			"wc -l os_shell.c\n"
			"wc -l < os_shell.c\n"
			"ls -al\n"
			"ls -al > 1.txt\n"
			"**********************\n"
		 );
	return;
}

/* Get line from stdin */
int process_command_line(char *buff)
{
	unsigned char flag_needfree = 0;
	if( NULL == buff )
	{
		buff = (char *)malloc(GENERAL_BUFF_SIZE * sizeof(char));
		flag_needfree = 1;
	}

	show_cmd_line_prompt();

	memset(buff, 0, GENERAL_BUFF_SIZE);

#if 0 /* os shell mode */
	gets(buff);// 3.2 -2
#else /* mysh mode */
	/* Get line from STDIN */
	if( NULL == fgets(buff, GENERAL_BUFF_SIZE, stdin) )
	{
		/* Ctrl + D (EOF) */
		extern int shell_var_ignoreeof;
		if ( shell_var_ignoreeof-->0 )
		{		
			printf("`Use \"exit\" to leave tcsh.\n");
			return 1;
		}
		printf("\n");
		exit(0);
	}
	/* Return only */
	if( strlen(buff)==1 && buff[strlen(buff) - 1] == '\n' )
	{
		return 1;
	}
	/* Got command */
	if (buff[strlen(buff) - 1] == '\n')
	{
		buff[strlen(buff) - 1] = 0; /* replace newline with null */
	}
#endif

	char *token = NULL;
	char *tmp = (char *)malloc(GENERAL_BUFF_SIZE * sizeof(char));
	memset(tmp, 0, GENERAL_BUFF_SIZE);
	memcpy(tmp, buff, GENERAL_BUFF_SIZE);
	while(NULL != (token = strsep(&tmp, ";")))// 3.3
	{
		if( (strlen(token) <= COMMAND_LINE_MAX_LEN) && (strlen(token)>0) )
		{
			cmd_add_history_link_list(token);
			parse_command_line_all(token);
		}
	}

	if( flag_needfree )
	{
		free(buff);
	}

	return 1;
}

#ifndef _DL_PORT_H_
#define DELIM_STRING_PIPE	"|"
#define DELIM_STRING_REDIRECTION_IN	"<"
#define DELIM_STRING_REDIRECTION_OUT	">"
#define DELIM_STRING_SPACE	" "
#define TYPE_PIPE	1
#define TYPE_REDI	2
#define TYPE_REDO	3
#define TYPE_REDO_E	4 // stderr : redirect both standard output (stdout) and standard error (stderr) of command on the left to file on the right.
#endif
/* parse & separate command line */
int parse_command_line_strsep(char *buff, char **target, char *delim)
{
	int index = 0;

	if( 0/*below*/
			|| 0 == strcmp(delim, DELIM_STRING_PIPE)
			|| 0 == strcmp(delim, DELIM_STRING_REDIRECTION_IN)
			|| 0 == strcmp(delim, DELIM_STRING_REDIRECTION_OUT)
	  )
	{
		for(index = 0; index < 2; index++)
		{
			if( NULL == (target[index] = strsep(&buff, delim)) )
				break;
		}
		if(target[0])
		{
			//debug_out("(%s)\n",target[0]);
		}
		if(target[1])
		{
			//debug_out("(%s)\n",target[1]);
		}
		return (0 == strcmp(delim, DELIM_STRING_PIPE))?(target[1]?TYPE_PIPE:0):\
			   ( (0 == strcmp(delim, DELIM_STRING_REDIRECTION_IN))?(target[1]?TYPE_REDI:0):\
			     ( (0 == strcmp(delim, DELIM_STRING_REDIRECTION_OUT))?(target[1]?TYPE_REDO:0):\
			       ( (0) ) ) );
	}
	else if( 0 == strcmp(delim, DELIM_STRING_SPACE) )
	{
		for(index = 0; index < MAX_ARG_NUM; index++)
		{
			if( NULL == (target[index] = strsep(&buff, delim)) )
			{
				break;
			}
			if( 0 == strlen(target[index]))
			{
				index--;
			}
			else
			{
				//debug_out("(%s)\n",target[index]?target[index]:"null");
				//debug_out("(%s)\n",target[1]?target[1]:"null");
			}
		}
		return 0;
	}
}
/* show prompt */
int show_cmd_line_prompt(void)
{
	char hostname[60] = {0};
	char *buff = (char *)malloc(GENERAL_BUFF_SIZE * sizeof(char));
	struct passwd *pwd = NULL;

	memset(buff, 0, GENERAL_BUFF_SIZE);

#if 0 /* OS-Shell mode */

#ifdef ENABLE_USERNAME_HOSTNAME
	pwd = getpwuid(getuid());
	getcwd(buff, GENERAL_BUFF_SIZE);
	gethostname(hostname, sizeof(hostname));
	debug_out("[OS Shell]%s@%s:%s $ ", pwd->pw_name, hostname, buff);
#else
	getcwd(buff, GENERAL_BUFF_SIZE);
	debug_out("[OS Shell]%s $ ",buff);
#endif

#else /* mysh mode */
	printf("%s %s--> ",dl_prompt, getcwd(NULL,0));	/* print prompt (printf requires %% to print %) */
#endif

	free(buff);
	return 0;
}
/* handler of built-in cmd - go ARG */
int handler_chdir(char *arg)
{
	if( 0 != chdir(arg) )
	{
		debug_out("Chdir error!(%s) \n",strerror(errno));
		return 1;
	}
	return 0;
}
/* handler of built-in cmd - exit */
int handler_exit(char *arg)
{
	exit(0);
	return 0;
}
/* handler of built-in cmd - show */
int handler_show(char *arg)
{
	debug_out("%s\n", arg?arg:"<null>");
	return 0;
}
int handler_status(char *arg)
{
	if(-1 == status_wait)
		debug_out("Have not executed program yet!\n");
	else
		debug_out("last status (%d)\n", status_wait);
	return 0;
}
int handler_bg(char *arg)
{
	//debug_out("%s\n", arg?arg:"<null>");
	int job_no = atoi(arg);
	struct task_os_shell_st *tmp = task_head;
	while(tmp->next)
	{
		tmp = tmp->next;
		if(tmp->no == job_no)
			break;
	}
	//task_manage_ground(tmp->pid ,1);
	//debug_out("TC-%d \n",tcgetpgrp(0));
	task_manage_fg_bg(tmp->pid, SIGCONT);
	tmp->status=S_BG;
	//debug_out("TC-%d \n",tcgetpgrp(0));
	//tcsetpgrp(0, getpid());
	//tcsetpgrp(1, getpid());
	//tcsetpgrp(2, getpid());
	return 0;
}
int handler_fg(char *arg)
{
	debug_out("%s\n", arg?arg:"<null>");
	int job_no = atoi(arg);
	struct task_os_shell_st *tmp = task_head;
	while(tmp->next)
	{
		tmp = tmp->next;
		if(tmp->no == job_no)
			break;
	}
	//task_manage_ground(tmp->pid ,1);
	task_manage_fg_bg(tmp->pid, SIGCONT);
	return 0;
}
int handler_watchuser(char *arg)
{
	char **argv = (char **)arg;
	char *name = argv[1];
	char *sw = argv[2];
	struct st_builtin_watchuser *head = &gv_watchuser_care;

	if( NULL == name )
	{
		debug_out("%s : ERROR ! no arg! \n", __func__);
		return -2;
	}

	if( NULL == sw )	// eg. $ watchuser dramalife
	{
		// Add to list
		/* Check if exist */
		while( head->next )
		{
			// Skip head
			head = head->next;
			if( 0 == strncmp(name, head->name, strlen(name)) )
				goto add_or_remove_finish;
		};
		// Create node
		struct st_builtin_watchuser *new = (struct st_builtin_watchuser *)malloc(sizeof(struct st_builtin_watchuser));
		memset(new, 0, sizeof(struct st_builtin_watchuser));
		strncpy( new->name, name, strlen(name) );
		new->next = NULL;

		// Insert
		head->next = new;
	}
	else			// eg. $ watchuser dramalife off
	{
		if( 0 == strncmp( sw, "off", strlen("off") ) )
		{
			// Del from list
			/* Check if exist */
			struct st_builtin_watchuser *prev = head;
			while( head->next )
			{
				// Skip head
				head = head->next;
				if( 0 == strncmp(name, head->name, strlen(name)) )
				{
					// Remove
					prev->next = head->next;
					free(head);
					goto add_or_remove_finish;
				}
				prev = head;
			};
		}
	}
	if( -1 == tid_watchuser )
	{
		pthread_create(&tid_watchuser, NULL, watchuser_main, (void *)&gv_watchuser_care);
	}

add_or_remove_finish:
	return 0;
}


/* check if cmd is built-in command */
int is_builtin_cmd(char **arg_cmd)
{
	int index = 0;

	if(!arg_cmd[0])
		return 1;

	for(index=0; index< MAX_ARG_NUM && arg_cmd[index]; index++)
	{
		debug_out("[%d] %s\n", index, arg_cmd[index]);
	}

	index = 0;
	while( NULL != builtin_cmd[index].cmd )
	{
		//debug_out("%s\n", builtin_cmd[index].cmd);
		//debug_out("%p\n", arg_cmd[0]);
		//debug_out("%s\n", arg_cmd[0]);
		if (strcmp(arg_cmd[0], builtin_cmd[index].cmd) == 0)
		{
			debug_out("Command (%s) (type=%d) (%s) handler!\n", builtin_cmd[index].cmd, builtin_cmd[index].type, builtin_cmd[index].handler?"has":"has no");
			if(builtin_cmd[index].handler)
			{
				if( BTTYPE_OSSHELL == builtin_cmd[index].type )
				{
					builtin_cmd[index].handler(arg_cmd[1]);
				}
				else if( BTTYPE_SIMPLE == builtin_cmd[index].type )
				{
					builtin_cmd[index].handler(arg_cmd);
				}
				else
				{
				}
			}
			return 1;
		}
		index++;
	}

	return 0;
}
/* exec program (no pipe & no redirect) */
int exec_external_prog_simple(char **arg)
{
	pid_t pid = fork();
	switch(pid)
	{
		case 0:
			//setsid();
			if ( execvp(arg[0], arg) < 0 )
			{
				//debug_out("exec error (%s)!\n", strerror(errno));
				debug_out("Commands not found!\n");
			}
			exit(0);
			break;
		case -1:
			debug_out("Forking failed! (%s) \n", strerror(errno));
			break;
		default:
			update5pid(pid);
			//wait(NULL);
			break;
	}
	return 0;
}
/* exec program(with pipe) */
int exec_external_prog_pipe(char **arg, char **arg_p)
{
	int pipefd[2];
	pid_t pid2;
	if( pipe(pipefd) < 0 )
	{
		debug_out("Init pipe failed ! (%s)\n", strerror(errno));
		return 1;
	}

	pid_t pid1 = fork();
	switch(pid1)
	{
		case 0:
			debug_out("(%s)(%s) \n", arg[0], arg[1]);
			close(pipefd[0]);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			if ( execvp(arg[0], arg) < 0 )
			{
				debug_out("exec error (%s)!\n", strerror(errno));
				exit(0);
			}
		case -1:
			debug_out("Forking failed! (%s) \n", strerror(errno));
			break;
		default:
			update5pid(pid1);
			pid2 = fork();
			switch(pid2)
			{
				case 0:
					close(pipefd[1]);
					dup2(pipefd[0], 0);
					close(pipefd[0]);
					debug_out("(%s)(%s) \n", arg_p[0], arg_p[1]);
					if ( execvp(arg_p[0], arg_p) < 0 )
					{
						debug_out("exec error (%s)!\n", strerror(errno));
						exit(0);
					}
				case -1:
					debug_out("Forking failed! (%s) \n", strerror(errno));
					return 2;
					break;
				default:
					update5pid(pid2);
					wait(NULL);
					wait(NULL);
					break;
			}

			break;
	}
	return 0;
}
/* exec program(with redirect) */
int exec_external_prog_redirect(int type, char **arg, char **arg_p)
{
	pid_t pid1;
	int fd_file;

	debug_out("(%s)(%s) \n",arg_p[0], arg_p[1]);

	if( -1 == (fd_file = open(arg_p[0], O_CREAT|O_RDWR, 0664)) )
	{
		debug_out("redirect error! (%s)\n", strerror(errno));
		return 1;
	}

	pid1 = fork();
	switch(pid1)
	{
		case 0:	// Child process
			debug_out("(%s)(%s) \n", arg[0], arg[1]);
			if( TYPE_REDI == type)
			{
				dup2(fd_file, 0); // stdin
			}
			else
			{
				dup2(fd_file, 1); // stdout
				// stderr
			}
			close(fd_file);
			if ( execvp(arg[0], arg) < 0 )
			{
				debug_out("exec error (%s)!\n", strerror(errno));
				exit(0);
			}
		case -1:
			debug_out("Forking failed! (%s) \n", strerror(errno));
			break;
		default: // Parent process
			update5pid(pid1);
			wait(NULL);

			break;
	}
	return 0;
}
/* exec program */
int exec_external_prog(int piped, char **arg, char **arg_p)
{
	switch(piped)
	{
		case TYPE_PIPE:
			exec_external_prog_pipe(arg, arg_p);
			break;
		case TYPE_REDI:
			exec_external_prog_redirect(TYPE_REDI, arg, arg_p);
			break;
		case TYPE_REDO:
			exec_external_prog_redirect(TYPE_REDO, arg, arg_p);
			break;
		default:
			exec_external_prog_simple(arg);
			break;
	}

	return 0;
}
/* parse cmd */
int parse_command_line_all(char *buff)
{
	int piped = 0;
	char *target[2];
	char *args_no_pipe[MAX_ARG_NUM] = {NULL};
	char *args_piped[MAX_ARG_NUM];


	if( 0 == (piped = parse_command_line_strsep(buff, target, DELIM_STRING_PIPE)) )
		if( 0 == (piped = parse_command_line_strsep(buff, target, DELIM_STRING_REDIRECTION_IN)) )
			piped = parse_command_line_strsep(buff, target, DELIM_STRING_REDIRECTION_OUT);

	switch(piped)
	{
		case TYPE_PIPE:
			parse_command_line_strsep(target[0], args_no_pipe,  DELIM_STRING_SPACE);
			parse_command_line_strsep(target[1], args_piped,  DELIM_STRING_SPACE);
			break;
		case TYPE_REDI:
		case TYPE_REDO:
			parse_command_line_strsep(target[0], args_no_pipe,  DELIM_STRING_SPACE);
			parse_command_line_strsep(target[1], args_piped,  DELIM_STRING_SPACE);
			break;
		default:
			parse_command_line_strsep(buff, args_no_pipe,  DELIM_STRING_SPACE);
			break;
	}

	if( 0 == is_builtin_cmd(args_no_pipe) )
	{
		exec_external_prog(piped, args_no_pipe, args_piped);
	}

	return 0;
}
int task_data_init(struct task_os_shell_st **data)
{
	*data = (struct task_os_shell_st *)malloc(sizeof(struct task_os_shell_st));
	if( NULL == *data )
		return -1;
	(*data)->next = NULL;

	return 0;
}
struct task_os_shell_st *task_new(pid_t pid, int status)
{
	struct task_os_shell_st *temp = task_head;
	struct task_os_shell_st *new = (struct task_os_shell_st *)malloc(sizeof(struct task_os_shell_st));

	if (!new)
	{
		debug_out("malloc!!(%s)\n",strerror(errno));
		return NULL;
	}
	//new->no = 0;
	new->pid = pid;
	new->status = status;
	new->need_wait = 1;
	new->next = NULL;
	while(temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
	return new;
}
struct  signal_status_st *get_sta_by_signal(int signal)
{
	int index = 0;
	for(index = 0; sig_sta[index].string != NULL; index++)
	{
		if(sig_sta[index].signal == signal)
			return &sig_sta[index];
	}
	return NULL;
}
struct  signal_status_st *get_sta_by_status(int status)
{
	int index = 0;
	for(index = 0; sig_sta[index].string != NULL; index++)
	{
		if(sig_sta[index].status == status)
			return &sig_sta[index];
	}
	return NULL;
}
void task_set_status(struct task_os_shell_st *tmp, int signal)
{
#if 1
	// (signal)<-->status<-->sta_string
	//		|
	//		|
	//		task->status
	struct signal_status_st *sta = get_sta_by_signal(signal);
	if(sta)
	{
		tmp->status = sta->status;
		debug_out("%d %s\n",tmp->pid, sta->string);//19955 Terminated
	}
	else
		debug_out("error!\n");
#else
	int index = 0;
	for(index = 0; sig_sta[index].string != NULL; index++)
	{
		if(sig_sta[index].signal == signal)
			tmp->status = sig_sta[index].status;
	}
#endif
}
void task_set_status_fg_bg(struct task_os_shell_st *tmp, int signal)
{
	// (signal)<-->status<-->sta_string
	//		|
	//		|
	//		task->status
	struct signal_status_st *sta = get_sta_by_signal(signal);
	if(sta)
	{
		tmp->status = sta->status;
		debug_out("%d %s\n",tmp->pid, sta->string);//19955 Terminated
	}
	else
		debug_out("error!\n");
}
#ifndef _DL_PORT_H_
#define TFB_PID	1
#define TFB_STA	2
#define TFB_WAIT	3
#endif
#if 1////Old
struct task_os_shell_st *task_find_by(int type, int data_arg)
{
	struct task_os_shell_st *tmp = task_head;
	struct task_os_shell_st *ret = NULL;
	while(tmp->next)
	{
		tmp = tmp->next;
		switch (type)
		{
			case TFB_PID:
				if( tmp->pid == (pid_t)data_arg )
					return tmp;
				break;
			case TFB_STA:
				if( tmp->status == (int)data_arg )
					return tmp;
				break;
			case TFB_WAIT:
				if( tmp->need_wait == (int)data_arg )
					return tmp;
				break;
			default:
				return NULL;
				break;
		}
	}
	switch (type)
	{
		case TFB_PID:
			if( tmp->pid == (pid_t)data_arg )
				return tmp;
			break;
		case TFB_STA:
			if( tmp->status == (int)data_arg )
				return tmp;
			break;
		case TFB_WAIT:
			if( tmp->need_wait == (int)data_arg )
				return tmp;
			break;
		default:
			return NULL;
			break;
	}
	return NULL;

}
#else
struct task_os_shell_st *task_find_switch(struct task_os_shell_st *tmp, int type, int data_arg)
{
	switch (type)
	{
		case TFB_PID:
			if( tmp->pid == (pid_t)data_arg )
				return tmp;
			break;
		case TFB_STA:
			if( tmp->status == (int)data_arg )
				return tmp;
			break;
		case TFB_WAIT:
			if( tmp->need_wait == (int)data_arg )
				return tmp;
			break;
		default:
			return NULL;
			break;
	}
}
struct task_os_shell_st *task_find_by(int type, int data_arg)
{
	struct task_os_shell_st *tmp = task_head;
	struct task_os_shell_st *ret = NULL;
	while(tmp->next)
	{
		tmp = tmp->next;
		if( NULL != (ret = task_find_switch(tmp, type, data_arg)) )
			return ret;
	}
	if( NULL != (ret = task_find_switch(tmp, type, data_arg)) )
		return ret;
	return NULL;

}
#endif
#include "get_path.h"
int builtin_which(char *arga)
{
	struct pathelement *p, *tmp;
	char *cmd;
	char *arg[2]={NULL, arga};

	printf("Executing built-in [which]\n");

	if (arg[1] == NULL) {  // "empty" which
		printf("which: Too few arguments.\n");
		return -1;
	}

	p = get_path();
	/***
	  tmp = p;
	  while (tmp) {      // print list of paths
	  printf("path [%s]\n", tmp->element);
	  tmp = tmp->next;
	  }
	 ***/

	printf("%s,%d \n",__func__,__LINE__);
	cmd = which(arg[1], p);
	extern char *gch;
	cmd = gch; // PATCH
	printf("%s,%d cmd_addr=%p \n",__func__,__LINE__,cmd);
	if (cmd) {
		printf("%s\n", cmd?cmd:"null");
		free(cmd);
	}
	else               // argument not found
		printf("%s: Command not found\n", arg[1]);

	while (p) {   // free list of path values
		tmp = p;
		p = p->next;
		free(tmp->element);
		free(tmp);
	}
	return 0;
}
int show_all_task(char *arg)
{
	int index = 0;
	struct task_os_shell_st *tmp = task_head;
	struct signal_status_st *sta = NULL;
	while(tmp->next)
	{
		tmp = tmp->next;
		sta = get_sta_by_status(tmp->status);
		tmp->no = index;//update index
		debug_out("[%d] %d %d %s \n",tmp->no, tmp->pid, tmp->status, sta?sta->string:"null");
		index++;
	}
	return 0;
}
/* Send signal to pid & record status */
int task_manage_fg_bg(pid_t pid, int signal)
{
	//stop || background
	struct task_os_shell_st *task_pid;
	kill(pid, signal);
	if( NULL != (task_pid = task_find_by(TFB_PID, (int)pid)) )
		task_set_status_fg_bg(task_pid, signal);
	else
		debug_out("unknown pid!\n");
	return 0;
}
int task_manage_sig_handler(pid_t pid, int signal)
{
	//stop || background
	struct task_os_shell_st *task_pid;
	kill(pid, signal);
	if( NULL != (task_pid = task_find_by(TFB_PID, (int)pid)) )
		task_set_status(task_pid, signal);
	else
		debug_out("unknown pid!\n");
	return 0;
}
int task_manage_ground(pid_t pid, int ground)
{//0-back,  1-front
	switch(ground)
	{
		case 0:
			break;
		case 1:
			tcsetpgrp(0, pid);
			break;
		default:
			break;
	}
	return 0;
}
void signal_handler(int signo)
{
	struct task_os_shell_st *task_pid;
	int sta = S_RUNNING;
	//debug_out("recv signal(%d) \n", signo);

	// get pid by status(fg-running)
	if( NULL != (task_pid = task_find_by(TFB_STA, (int)sta)) )
		task_manage_sig_handler(task_pid->pid, signo);

	if(0)
	{
		pid_t pid_fg = tcgetpgrp(0);
		debug_out("pid_fg(%d)\n",pid_fg);
		pid_fg = tcgetpgrp(1);
		debug_out("pid_fg(%d)\n",pid_fg);
		pid_fg = tcgetpgrp(2);
		debug_out("pid_fg(%d)\n",pid_fg);
		show_cmd_line_prompt();
		debug_out("\n");
	}

	flag_pause = 1;
	flag_recept = 1;

	fflush(NULL);
}

#ifndef _DL_PORT_H_
/* main thread */
int main(int argc, char **argv)
{

	// PS
	// T    stopped by job control signal
	// +    is in the foreground process group

	signal(SIGINT, signal_handler);// ctrl + c
	signal(SIGTSTP, signal_handler);// ctrl + z 	// T+
	//kill(pid, SIGCONT); 				// S+
	// SIGCONT

	/* init */
	if ( 0 != init_history_list(&history_head) )
	{
		debug_out("init cmd_history failed (%s)! \n",strerror(errno));
		exit(2);
	}
	if( 0 != task_data_init(&task_head) )
	{
		debug_out("init task data failed (%s)! \n",strerror(errno));
		exit(2);
	}

	show_welcom();
	while(1)
	{
		if(flag_recept)
		{//TODO : wait of pid (killed by SIGINT) will block until getting input.
			process_command_line(NULL);
		}


		struct task_os_shell_st *task_run = task_head->next;
		while(task_run)// wait all pid(s) need wait
		{
			if(task_run->need_wait)
			{
				static pid_t pid_poll = 0;
				pid_poll = waitpid(task_run->pid, &status_wait, WNOHANG);//wait no-pipe no-redirect
				switch(pid_poll)
				{
					case 0:// again
						flag_recept = 0;
						break;
					case ECHILD:// vaule=10
						debug_out("not my child !(%s)\n",strerror(errno));
						task_run->need_wait = 0;
						break;
					case -1:
						flag_recept = 1;
						break;
					default:
						task_run->status = S_TERM;
						task_run->need_wait = 0;
						fflush(NULL);
						//debug_out("pid (%d) exit.\n",pid_poll);
						break;
				}
			}
			if( NULL == task_find_by(TFB_STA, (int)S_RUNNING) )// no fg
			{
				flag_recept = 1;
			}
			task_run = task_run->next;
		}
	}

	return 0;
}
#endif

