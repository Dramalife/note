#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "sh.h"
#include "dl_builtin.h"

	int
main(int argc, char **argv, char **envp)
{
	char	buf[MAXLINE];
	char	buf_origin[MAXLINE];
	char    *arg[MAXARGS];  // an array of tokens
	char    *ptr;
	char    *pch;
	pid_t	pid;
	int	status, i, arg_no;

	dl_sh_init(NULL);

	printf("%s %s--> ",dl_prompt, getcwd(NULL,0));	/* print prompt (printf requires %% to print %) */

	dl_loop(NULL);
	exit(0);
}
