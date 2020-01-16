/*
 * note "sample - fd" related file
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
 *
 * ;
 *
 * $ uname -a
 * Linux server 4.15.0-74-generic #84-Ubuntu SMP Thu Dec 19 08:06:28 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 *
 * Init : Thu Jan 16 21:09:20 CST 2020
 * 	ls -al /proc/PID/fd;
 * Update
 *
 */


/* Dependence
 * 	HEADERS : note/lib_dramalife/lib_dramalife.h
 * 	OBJS	: note/lib_dramalife/ipc_lib/build/obj/ipc_lib_pipe.o
 */


#include <stdio.h>
#include <errno.h>
#include <string.h>//strerror

/* getpid() */
#include <sys/types.h>
#include <unistd.h>

#include "lib_dramalife.h"


int main(void)
{
	FILE *fp = NULL;
	pid_t mypid = 0;
#define CMD_STR_LEN	128
#define BUF_STR_LEN	(64 + 512)
	char cmd[CMD_STR_LEN];
	memset(cmd, 0, CMD_STR_LEN);
	char buff[BUF_STR_LEN];
	memset(buff, 0, BUF_STR_LEN);

	fp = fopen("./1.txt","r");
	mypid = getpid();
	printf("My pid(%d) \n",mypid);

	sprintf(cmd,"ls -al /proc/%d/fd",mypid);
	printf("CMD(%s) \n",cmd);
	dramalife_get_cmd_n_result(cmd, "r", buff, sizeof(buff));

	printf("=====\n%s\n=====\n",buff);

	if(!fp)
	{
		printf("error(%s) \n",strerror(errno));
		return errno;
	}

	while(1)
	{
	}

	return 0;
}
