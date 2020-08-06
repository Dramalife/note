/*
 * note "syslog - sample" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-99-generic #100-Ubuntu SMP Wed Apr 22 20:32:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Thu Aug  6 17:36:29 CST 2020
 *  * ;
 * Update : Thu Aug  6 17:36:29 CST 2020
 *  
 * Update
 *
 */


/*
 * CN:
 * 	可用于动态链接库中函数输出打印信息到syslog;
 * EN:
 *	Can be used to output and print information from functions in the dynamic link library to syslog;
 */


#include <syslog.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>



/* Macro && Function */
#if 0
#define SYS_PRINT(f,...)	do{ \
	char *psysprint=(char *)malloc(512*sizeof(char)); \
	memset(psysprint, 0, 512); \
	snprintf(psysprint, 512, f, __VA_ARGS__); \
	sys_print(psysprint); \
}while(0)
static inline void sys_print(const char *cont )
{
	int level=0, options=0;

	level = LOG_INFO;
	options |= LOG_PID;
	options |= LOG_PERROR;

	openlog(__func__, options, LOG_USER);

	syslog(LOG_USER | level, "%s", cont);

	closelog();

	return;
}
#endif



/* Function */
#if 1
static inline void sys_print(const char *format, ... )
{
	int level=0, options=0;
	va_list ap;

#define LOCAL_BUFF_SIZE	1024
	char *buff = (char *)malloc(LOCAL_BUFF_SIZE * sizeof(char));

	if( NULL == buff )
		return;

	va_start(ap, format);

	level = LOG_INFO;
	options |= LOG_PID;
	options |= LOG_PERROR;

	vsnprintf(buff, LOCAL_BUFF_SIZE, format, ap);

	openlog(__func__, options, LOG_USER);
	syslog(LOG_USER | level, "%s", buff);
	closelog();

	va_end(ap);

	free(buff);

	return;
}
#endif


int main(int argc, char **argv)
{

	//SYS_PRINT("%s,%d",__func__,__LINE__);
	sys_print("%s,%d",__func__,__LINE__);

	return 0;
}

