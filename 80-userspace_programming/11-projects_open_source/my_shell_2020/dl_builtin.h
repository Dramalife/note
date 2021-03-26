/*
 * 2020.10.02
 * Simple Shell
 * dramalife@live.com
 */
#ifndef _DL_BUILTIN_H_
#define _DL_BUILTIN_H_


struct dl_cmd_st
{
	char *cmd;
	int (*func)(void *);
};


/* cd */
#define SIZE_CWD_PTR	128
char cwd_ptr[SIZE_CWD_PTR];
#define SIZE_DL_PROMPT	SIZE_CWD_PTR
char dl_prompt[SIZE_DL_PROMPT];

int dlfun_exit(void *arg);
int dlfun_cd(void *arg);
int dlfun_where(void *arga);
int dlfun_pwd(void *arg);
int dl_sh_update_cwd(void *arg);
int dlfun_list(void *arg);
int dlfun_pid_of_the_shell(void *arg);
int dlfun_kill(void *arg);
int dlfun_prompt(void *arg);
int dlfun_printenv(void *arg);
int dlfun_setenv(void *arg);
int dlfun_setvar(void *arg);

extern int dl_checkif_builtin(void *arg);
extern int dl_sh_init(void *arg);
extern int dl_process_wildcard(char **des);
#endif
