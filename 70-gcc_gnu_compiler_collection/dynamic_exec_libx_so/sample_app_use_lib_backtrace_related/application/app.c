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
*/

/*
Init : 2019.08.23, COPY FROM "note/70-gcc_gnu_compiler_collection/backtrace/sample1/main.c"
			DEL backtrace related funcs replaced by libx.so
Update
*/


/* CONFIG START */
#define USE_MY_SHARED_LIB	1
#define LIB_HAVE_HEADER_FILE	0
/* CONFIG END   */

#include<stdio.h>	/* man 3 */
#include <execinfo.h>	/* man 3 */
//#include <errno.h>
#include<signal.h>
#include<stdlib.h> /* EXIT_FAILURE */
#include<string.h> /* strncmp */

#if LIB_HAVE_HEADER_FILE
//#error 111 //for test.
#include "../lib_shared/backtrace_funcs_symbol.h"
#else
extern void dump(void);
extern void signal_handler(int signo);
#endif

#if (0 == USE_MY_SHARED_LIB) /* REPLACED BY LIBX.SO */
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
#endif

int sample_segment_err1(void)
{
	int ret = 0;  
	int *tmpp = NULL;  

	*tmpp = 1;  /* Causing Segment Fault */  

	ret = *tmpp++;  

	return ret;  
}

int sample_syscall_kill1(void)
{
	system("kill 0");
	return 0;
}

int matched_string(const char *str1, const char *str2)
{
	return strncmp(str1, str2, sizeof(str2) - 1) ? 0 : 1;
}

int main(int argc, char **argv)
{
	signal(SIGSEGV, signal_handler); 

	if(argc > 1)
	{
		if(matched_string(argv[1],"seg"))/* Sample - Segment Fault */
		{
			sample_segment_err1();
		}
		else if(matched_string(argv[1],"kill"))
		{
			sample_syscall_kill1();
		}
		else if(matched_string(argv[1],"dump"))/* Unuseful, using Makefile now. */
		{
			char tmp[100];
			sprintf(tmp,"objdump -dx %s > %s.dump",argv[0], argv[0]);
			system(tmp);
			printf("CMD is [%s] \n", tmp);
		}
	}
	else
	{
		printf("Help:\nSee line %d of the source code!\n",__LINE__);
	}

	while(1)
	{
	}

	return 0;
}

