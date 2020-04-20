
/* Debug print switch */
#define DEBUG_SWITCH	1

/* Print function */
#define debug_out(x,...)	do{if(DEBUG_SWITCH) printf("[%s,%d] ",__func__,__LINE__);printf(x,##__VA_ARGS__);}while(0)

#define GENERAL_BUFF_SIZE	1024
#define	MAX_ARG_LEVEL		100
#define COMMAND_LINE_MAX_LEN	80	// 3.2 -1

//
#undef ENABLE_USERNAME_HOSTNAME
//
#ifndef ENABLE_USERNAME_HOSTNAME
#define ENABLE_USERNAME_HOSTNAME	1
#endif

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#ifdef ENABLE_USERNAME_HOSTNAME
#include <pwd.h>
#endif


#define HISTORY_CONTENT_SIZE	64
struct list_st
{
	char content[HISTORY_CONTENT_SIZE];
	struct list_st *next;
} *history_head;

struct cmd_history_array_st
{
int used;
char content[HISTORY_CONTENT_SIZE];
};
struct cmd_history_array_st history_array[1024] = {0};

/* 3.2 pid */
#define MAX_PID_RECORD	5
pid_t last5pid [MAX_PID_RECORD] = {0};
int index5pid = 0;
void update5pid(pid_t pid)
{
	last5pid[index5pid] = pid;
	index5pid++;
	if (index5pid >= MAX_PID_RECORD )
		index5pid = 0;
	return;
}
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

int show_cmd_line_prompt(char *buff);

int init_history_list(struct list_st *head)
{
	head = (struct list_st *)malloc(1 * sizeof(struct list_st));
	memset(head->content, 0, sizeof(head->content));
	head->next = NULL;
	return head?0:-1;
}

int cmd_add_history(char *buff)
{
	struct list_st *ptr = NULL;
	struct list_st *new = NULL;

	ptr = history_head;

debug_out("%s,%d\n",__func__,__LINE__);////
	while( NULL != (ptr->next) )
	{
		debug_out("%s,%d\n",__func__,__LINE__);
		ptr = ptr->next;
	}

debug_out("%s,%d\n",__func__,__LINE__);
	new = (struct list_st *)malloc(1 * sizeof(struct list_st));
debug_out("%s,%d\n",__func__,__LINE__);
	strncpy(new->content, buff, sizeof(new->content));

	ptr->next = new;
	new->next = NULL;

debug_out("%s,%d\n",__func__,__LINE__);
	return 0;
}

int cmd_add_history_array(char *buff)
{
	int index = 0;
	while( 0 != history_array[index].used )
		index++;

	strncpy(history_array[index].content, buff, HISTORY_CONTENT_SIZE);
	history_array[index].used = 1;

	return 0;
}

int cmd_show_history(char *arg)
{
	struct list_st *ptr = NULL;
	ptr = history_head;
	while(ptr->next)
	{
		ptr = ptr->next;
		debug_out("[history]%s\n",ptr->content);
	}
	return 0;
}

int cmd_show_history_array(void)
{
	int index = 0;
	while( 0!= history_array[index].used )
	{
		debug_out("-----%s\n",history_array[index].content);
		index++;
	}
	return 0;
}

/* Get line from stdin */
#if 0
int process_command_line(char *buff)
{
	show_cmd_line_prompt(buff);

	memset(buff, 0, GENERAL_BUFF_SIZE);
	gets(buff);// 3.2 -2

	if( (strlen(buff) <= COMMAND_LINE_MAX_LEN) && (strlen(buff)>0) )
	{
		cmd_add_history_array(buff);
		parse_command_line_all(buff);
	}

	return 1;
}
#endif
int process_command_line(char *buff)
{
	show_cmd_line_prompt(buff);

	memset(buff, 0, GENERAL_BUFF_SIZE);
	gets(buff);// 3.2 -2

	char *token = NULL;
	char *tmp = (char *)malloc(GENERAL_BUFF_SIZE * sizeof(char));
	memset(tmp, 0, GENERAL_BUFF_SIZE);
	memcpy(tmp, buff, GENERAL_BUFF_SIZE);
	while(NULL != (token = strsep(&tmp, ";")))// 3.3
	{
		if( (strlen(token) <= COMMAND_LINE_MAX_LEN) && (strlen(token)>0) )
		{
			cmd_add_history_array(token);
			parse_command_line_all(token);
		}
	}

	return 1;
}

#define DELIM_STRING_PIPE	"|"
#define DELIM_STRING_SPACE	" "
int parse_command_line_strsep(char *buff, char **target, char *delim)
{
	int index = 0;
	{
		if( 0 == strcmp(delim, DELIM_STRING_PIPE))
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
				debug_out("(%s)\n",target[1]);
			}
			return target[1]?1:0;
		}
		else if( 0 == strcmp(delim, DELIM_STRING_SPACE) )
		{
			for(index = 0; index < MAX_ARG_LEVEL; index++)
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
					debug_out("(%s)\n",target[index]?target[index]:"null");
					//debug_out("(%s)\n",target[1]?target[1]:"null");
				}
			}
			return 0;
		}
	}
}
int show_cmd_line_prompt(char *buff)
{
	char hostname[60] = {0};

	memset(buff, 0, GENERAL_BUFF_SIZE);
#ifdef ENABLE_USERNAME_HOSTNAME
	struct passwd *pwd = getpwuid(getuid());
	getcwd(buff, GENERAL_BUFF_SIZE);
	gethostname(hostname, sizeof(hostname));
	debug_out("[OS Shell]%s@%s:%s $ ", pwd->pw_name, hostname, buff);
#else
	getcwd(buff, GENERAL_BUFF_SIZE);
	debug_out("[OS Shell]%s $ ",buff);
#endif
	return 0;
}
struct builtin_cmd_st
{
	char *cmd;
	int (*handler)(char *);
};
int handler_exit(char *arg);
int handler_show(char *arg);
int handler_chdir(char *arg);
struct builtin_cmd_st builtin_cmd[]=
{
	{"exit",	handler_exit},
	{"show",	handler_show},
	{"history",	cmd_show_history_array},
	{"go",		handler_chdir},
	{"pid",		handler_pid},
	{"test",	NULL},
	{NULL,NULL},
};
int handler_chdir(char *arg)
{
	if( 0 != chdir(arg) )
	{
		debug_out("Chdir error!(%s) \n",strerror(errno));
		return 1;
	}
	return 0;
}
int handler_exit(char *arg)
{
	exit(0);
	return 0;
}
int handler_show(char *arg)
{
	debug_out("%s\n", arg?arg:"<null>");
	return 0;
}
int is_builtin_cmd(char **arg_cmd)
{
	int index = 0;

	if(!arg_cmd[0])
	return 1;

	while( NULL != builtin_cmd[index].cmd )
	{
		//debug_out("%s\n", builtin_cmd[index].cmd);
		//debug_out("%p\n", arg_cmd[0]);
		//debug_out("%s\n", arg_cmd[0]);
		if (strcmp(arg_cmd[0], builtin_cmd[index].cmd) == 0)
		{
			debug_out("command (%s) %s handler!\n", builtin_cmd[index].cmd, builtin_cmd[index].handler?"has":"has no");
			if(builtin_cmd[index].handler)
			{
				builtin_cmd[index].handler(arg_cmd[1]);
			}
			return 1;
		}
		index++;
	}

	return 0;
}
int exec_external_prog(int piped, char **arg, char **arg_p)
{
	if(piped)
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
				debug_out("(%s) \n", arg[0]);
				debug_out("(%s) \n", arg[1]);
				close(pipefd[0]);
				dup2(pipefd[1], 1);
				close(pipefd[1]);
				if ( execvp(arg[0], arg) < 0 )
				{
					debug_out("exec error (%s)!\n", strerror(errno));
					exit(0);
				}
				break;
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
						debug_out("(%s) \n", arg_p[0]);
						debug_out("(%s) \n", arg_p[1]);
						if ( execvp(arg_p[0], arg_p) < 0 )
						{
							debug_out("exec error (%s)!\n", strerror(errno));
							exit(0);
						}
						break;
					case -1:
						debug_out("Forking failed! (%s) \n", strerror(errno));
						return 2;
						break;
					default:
						update5pid(pid2);
						debug_out("++++");
						wait(NULL);
						debug_out("++++");
						wait(NULL);
						debug_out("++++");
						break;
				}
				debug_out("++++");

				break;
		}
	}
	else
	{
		pid_t pid = fork();
		switch(pid)
		{
			case 0:
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
				wait(NULL);
				break;
		}
	}

	return 0;
}
int parse_command_line_all(char *buff)
{
	int piped = 0;
	char *target[2];
	char *args_no_pipe[MAX_ARG_LEVEL];
	char *args_piped[MAX_ARG_LEVEL];

	piped += parse_command_line_strsep(buff, target, DELIM_STRING_PIPE);

	if(piped)
	{
		parse_command_line_strsep(target[0], args_no_pipe,  DELIM_STRING_SPACE);
		parse_command_line_strsep(target[1], args_piped,  DELIM_STRING_SPACE);
	}
	else
	{
		parse_command_line_strsep(buff, args_no_pipe,  DELIM_STRING_SPACE);
	}

	if( 0 == is_builtin_cmd(args_no_pipe) )
	{
		exec_external_prog(piped, args_no_pipe, args_piped);
	}

	return 0;
}


/* main thread */
int main(int argc, char **argv)
{
	char *buff = NULL;
	
	/* init */
	buff = (char *)malloc(GENERAL_BUFF_SIZE * sizeof(char));

	if (NULL == buff)
	{
		debug_out("malloc error (%s)! \n",strerror(errno));
		exit(2);
	}
	if ( 0 != init_history_list(history_head) )
	{
		debug_out("init cmd_history failed (%s)! \n",strerror(errno));
		exit(2);
	}

	while(1)
	{
		process_command_line(buff);
	}

	/* clean */
	free(buff);
	return 0;
}

