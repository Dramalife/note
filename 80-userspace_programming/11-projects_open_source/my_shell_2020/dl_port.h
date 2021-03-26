#ifndef _DL_PORT_H_
#define _DL_PORT_H_

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




#define DELIM_STRING_PIPE	"|"
#define DELIM_STRING_REDIRECTION_IN	"<"
#define DELIM_STRING_REDIRECTION_OUT	">"
#define DELIM_STRING_SPACE	" "
#define TYPE_PIPE	1
#define TYPE_REDI	2
#define TYPE_REDO	3


#define TFB_PID	1
#define TFB_STA	2
#define TFB_WAIT	3


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
int builtin_which(char *arga);
int handler_watchuser(char *arg);

int status_wait;

struct task_os_shell_st *task_new(pid_t pid, int status);
void signal_handler(int signo);

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
	char *string;
};

extern struct BUILTIN_ST_NAME builtin_cmd[];
extern struct signal_status_st sig_sta[];
extern struct task_os_shell_st* task_head;
extern struct list_st *history_head;


extern pid_t last5pid [MAX_PID_RECORD];
extern int index5pid;
extern int flag_pause;
extern int flag_recept;

#endif
