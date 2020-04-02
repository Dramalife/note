/*
 * note gcc debug-backtrace related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * Init : 2019.07.11 21:53, wjy.
 * Update : 2019.07.13 17:08, wjy.rc.
 * Init : 2019.07.24, COPY from
 * 	"/70-gcc_gnu_compiler_collection/backtrace/main.c“
 * Update : 2019.11.08, Make lib executable;
 * Update : 
 */



#include "../lib_dramalife.h"
//#include<stdio.h>	/* man 3 */
//#include <execinfo.h>	/* man 3 */
////#include <errno.h>
//#include<signal.h>
//#include<stdlib.h> /* EXIT_FAILURE */
//#include<string.h> /* strncmp */
//#include <sys/types.h>
//#include <unistd.h>

/*
 * If not defined "DEMO", as lib.
 */
#ifndef _DL_BACKTRACE_LIB_DEMO_
/*
 * In-file used function
 */
static void dl_backtrace_dump(void)  
{  
#define BACKTRACE_SIZE   16  
	int tmp, buff_cnt;
	void *buffer[BACKTRACE_SIZE];
	char **info_trace;

	buff_cnt = backtrace(buffer, BACKTRACE_SIZE);

	dlbt_debug("backtrace() returned %d addresses\n", buff_cnt);

	info_trace = backtrace_symbols(buffer, buff_cnt);
	if (info_trace == NULL)
	{  
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}  

	for (tmp = 0;tmp < buff_cnt;tmp++)  
	{
		dlbt_debug("[%02d] %s\n", tmp, info_trace[tmp]);
	}

	free(info_trace);
}  

/*
 * Hanlder of singal, ex.SIGSEGV.
 */
void dlbt_signal_handler(int signo)  
{  
	/*
	 * Show maps 
	 * popen is better !
	 */ 
	int ret = 0;
	char buff[64] = {0};
	sprintf(buff,"cat /proc/%d/maps", getpid());
	ret = system((const char*) buff);

	/* Print backtrace */
	dlbt_debug("##############Backtrace_Start__signo(%d),system-ret(%d)#############\n", signo, ret);
	dl_backtrace_dump();
	dlbt_debug("##############Backtrace_End__(%d)#############\n", signo);

	/* Resume signal handler & Resend the signal */
	signal(signo, SIG_DFL);
	raise(signo);
}  
#endif




/*******************************************************************************
 * DEMO 
 * Demo of "note/lib_dramalife/backtrace_lib"
 *******************************************************************************/
#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
#include "../lib_dramalife.h"
int sample_segment_err1(void)
{
	int ret = 0;
	int *tmpp = NULL;

	*tmpp = 1;/* Causing Segment Fault */  

	ret = *tmpp++;

	return ret;
}

int sample_syscall_kill1(void)
{
	return system("kill 0");
}

int matched_string(const char *str1, const char *str2)
{
	return strncmp(str1, str2, sizeof(str2) - 1) ? 0 : 1;
}

int main(int argc, char **argv)
{
	/* Register signal handler */
	signal(SIGSEGV, dlbt_signal_handler);

	/* Set resource limit of coredump */
	dl_set_coredump_unlimit();

	if(argc > 1)
	{
		/* Sample - Segment Fault */
		if(matched_string(argv[1],"seg"))
			sample_segment_err1();
		else if(matched_string(argv[1],"kill"))
			sample_syscall_kill1();
		/* Unuseful, using Makefile now. */
		else if(matched_string(argv[1],"dump"))
		{
			char tmp[100];
			sprintf(tmp,"objdump -dx %s > %s.dump",argv[0], argv[0]);
			int ret = system(tmp);
			printf("CMD is [%s],ret(%d) \n", tmp, ret);
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
#endif
