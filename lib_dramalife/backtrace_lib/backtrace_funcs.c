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
 * Init : 2019.07.11 21:53, wjy.
 * Update : 2019.07.13 17:08, wjy.rc.
 * Init : 2019.07.24, COPY from
 * 	"/70-gcc_gnu_compiler_collection/backtrace/main.c“
 * Update : 2019.11.08, Make lib executable;
 * Update : 
 */



#include<stdio.h>	/* man 3 */
#include <execinfo.h>	/* man 3 */
//#include <errno.h>
#include<signal.h>
#include<stdlib.h> /* EXIT_FAILURE */
#include<string.h> /* strncmp */
#include <sys/types.h>
#include <unistd.h>

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
	int ret = 0;
	char buff[64] = {0};  
	sprintf(buff,"cat /proc/%d/maps", getpid());  
	ret = system((const char*) buff);  

	printf("\n##############Backtrace_Start(%d),system-ret(%d)#############\n", signo,ret);  
	dump();  
	printf("\n##############Backtrace_End__(%d)#############\n", signo);  

	signal(signo, SIG_DFL); /* Resume signal handler */  
	raise(signo);           /* Resend signal */  
}  


/*
 * Make the lib executable
 */
#if (defined PROVIDE_MAIN_FUNCTION_IN_LIB) && (1 == PROVIDE_MAIN_FUNCTION_IN_LIB)

//MIF:Macro In File
#define MIF_REPLACE_RETURN_WITH_EXIT	0

// Designate ld in lib source
#if (defined DESIGNATE_LD_IN_LIB_FILE) && (1 == DESIGNATE_LD_IN_LIB_FILE)
//x86
asm(".pushsection .interp,\"a\"\n"
#if (defined __x86_64__) && (1 == __x86_64__)
		"        .string \"/lib/x86_64-linux-gnu/ld-2.27.so\"\n"
#elif (defined __i686__) && (1 == __i686__)
		"        .string \"/lib/i386-linux-gnu/ld-linux.so.2\"\n"
#else
#error NOT SUPPORTED YET !
#endif
		".popsection");
//ARM - TODO
//		(defined __ARM_EABI__) && (1 == __ARM_EABI__)
//		"        .string \"/lib/arm-linux-gnueabihf/ld-2.24.so\"\n"
#endif//DESIGNATE_LD_IN_LIB_FILE

/*
 * Add "main()" in library source, (and add "-Wl,-emain" option to gcc), Seg fault. 
 * (set PROVIDE_MAIN_FUNCTION_IN_LIB = 1 at ld option)
 *	Reason : library function "printf()" analysis err(gdb).
 * 	$ ./libbacktrace_funcs.so
 * 	Segmentation fault (core dumped)
 * Add "main()" in library source, and designate ld, printf ok, but Seg fault. 
 * (set PROVIDE_MAIN_FUNCTION_IN_LIB = 1 at ld option)
 *	Reason : lose standard exit function "_exit()", replace "return 0" with "_exit(0)" will fix this!
 *	$ /lib/x86_64-linux-gnu/ld-2.27.so ./libbacktrace_funcs.so
 * 	main,93.
 * 	Segmentation fault (core dumped)
 * Replace "return 0" with "_exit(0)" in "main()", and designate ld, printf ok, no fault, but depend on ld. 
 * (set MIF_REPLACE_RETURN_WITH_EXIT = 1 in this file)
 * 	$ /lib/x86_64-linux-gnu/ld-2.27.so ./libbacktrace_funcs.so
 * 	main,93.
 */
int main(void)
{
	printf("%s,%d. \n",__func__,__LINE__);
#if (0 == MIF_REPLACE_RETURN_WITH_EXIT)
	return 0;
#else
	_exit(0);
#endif
}

#if (defined PROVIDE_START_FUNCTION_IN_LIB) && (1 == PROVIDE_START_FUNCTION_IN_LIB)
void _start(void)
{
	int ret;
	ret = main();
	_exit(ret);
}
#endif//PROVIDE_START_FUNCTION_IN_LIB
#endif//PROVIDE_MAIN_FUNCTION_IN_LIB
