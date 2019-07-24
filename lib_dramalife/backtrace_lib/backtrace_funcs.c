/*
* note gcc debug-backtrace related file
* Copyright (C) 2019 Dramalife@live.com
* 
* This file is part of [note](https://github.com/Dramalife/note.git)
* 
* note is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/*
Init edit : 2019.07.11 21:53, wjy.
Update	::: 2019.07.13 17:08, wjy.rc.
	Init : 2019.07.24, COPY from
	"/70-gcc_gnu_compiler_collection/backtrace/main.c“
*/

#include<stdio.h>	/* man 3 */
#include <execinfo.h>	/* man 3 */
//#include <errno.h>
#include<signal.h>
#include<stdlib.h> /* EXIT_FAILURE */
#include<string.h> /* strncmp */

void dump(void)  
{  
#define BACKTRACE_SIZE   16  
	int tmp, buff_cnt;  
	void *buffer[BACKTRACE_SIZE];  
	char **info_trace;  

	buff_cnt = backtrace(buffer, BACKTRACE_SIZE);  

	printf("backtrace() returned %d addresses\n", buff_cnt);  

	info_trace = backtrace_symbols(buffer, buff_cnt);  
	if (info_trace == NULL)
	{  
		perror("backtrace_symbols");  
		exit(EXIT_FAILURE);  
	}  

	for (tmp = 0; tmp < buff_cnt; tmp++)  
	{
		printf("[%02d] %s\n", tmp, info_trace[tmp]);  
	}

	free(info_trace);  
}  


void signal_handler(int signo)  
{  
	/* Show maps */ 
	char buff[64] = {0};  
	sprintf(buff,"cat /proc/%d/maps", getpid());  
	system((const char*) buff);  

	printf("\n##############Backtrace_Start(%d)#############\n", signo);  
	dump();  
	printf("\n##############Backtrace_End__(%d)#############\n", signo);  

	signal(signo, SIG_DFL); /* Resume signal handler */  
	raise(signo);           /* Resend signal */  
}  

