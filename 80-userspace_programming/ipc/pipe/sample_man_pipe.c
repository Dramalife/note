/*
 * note "IPC - pipe" related file
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
 * SRC : man 2 pipe
 * 
 * Init : 2019.12.07
 *	COPY FROM "man 2 pipe" ;
 * Update : 2019.12.07
 *	Add : print pipe buff size ;
 * Update 
 *
 */


/* The following program creates a pipe, and then fork(2)s to create a child process; the child inherits a duplicate set of file descriptors
 * that refer to the same pipe.  After the fork(2), each process closes the file  descriptors  that  it  doesn't  need  for  the  pipe  (see
 * pipe(7)).   The  parent  then  writes  the  string contained in the program's command-line argument to the pipe, and the child reads this
 * string a byte at a time from the pipe and echoes it on standard output.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>


extern int dramalife_get_pipe_max_size(void);
extern int dramalife_get_cmd_result(const char *cmd, const char *type, char *output);

	int
main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;

	/* Pipe buff size, <limits.h> 
	 *   When data written by multi-processes, 
	 * each time should not exceed PIPE_BUF bytes, 
	 * else kernel will divide the data into few parts, 
	 * which causing data crossover.
	 *   It doesn`t matter when only one process 
	 * writes data.
	 */
	printf("PIPE_BUF(%d), pipe_max_size(%d) \n"
			,PIPE_BUF
			,dramalife_get_pipe_max_size()
	      );

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {    /* Child reads from pipe */
	
		/* If not, will not see EOF. */
		close(pipefd[1]);          /* Close unused write end */

		while (read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);

	} else {            /* Parent writes argv[1] to pipe */

		/* Why closing unused read fd? We need signal SIGPIPE or EPIPE ;-) */
		close(pipefd[0]);          /* Close unused read end */
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}

