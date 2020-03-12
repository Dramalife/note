/*
 * note "proc/PID/cmdline" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 *
 * This file is part of [note](https://github.com/Dramalife/note.git)
 *
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
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
 * Init : Thu Mar 12 16:50:17 CST 2020
 *	Init;
 * Update
 *
 */

/* Key_words:
 * syslog
 * popen[pipe]
 * proc/PID/cmd_line
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <syslog.h>


#define get_cmd(p,b)	do{\
	ptr = b;\
	sprintf(buff_cmd, "cat /proc/%d/cmdline", p);\
	fp = popen(buff_cmd, "r");\
	while( NULL != fgets(ptr, 32, fp) )\
	{\
		/*printf("output(%s) \n",ptr);*/\
		ptr += strlen(ptr);\
	}\
}while(0)

#define print_show(x,...)	do{printf(x,##__VA_ARGS__);syslog(LOG_USER|LOG_DEBUG,x,##__VA_ARGS__);}while(0)

/*
 * Usage:
 * # ./a.out
 * # cat /var/log/syslog | grep "pid_ppid"
 */
void main(void)
{
	pid_t mpid = getpid();
	pid_t mppid = getppid();


	openlog("pid_ppid", LOG_PID, LOG_USER);

	print_show("pid(%d), ppid(%d) \n",mpid, mppid);

	FILE *fp ;
	char buff_cmd[128]={0};
	char buff_pid_cmd[256]={0};
	char buff_ppid_cmd[256]={0};
	char *ptr ;

	get_cmd(mpid, buff_pid_cmd);
	get_cmd(mppid, buff_ppid_cmd);

	print_show("buff_pid_cmd(%s) \n",buff_pid_cmd);
	print_show("buff_ppid_cmd(%s) \n",buff_ppid_cmd);

}
