#ifndef _LIB_DRAMALIFE_BACKTRACE_LIB_H_
#define _LIB_DRAMALIFE_BACKTRACE_LIB_H_


#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


/* Debug Print */
#if 1
#define dlbt_debug(fmt,...)	do{\
	printf("[%s] ","[libdl-bt] "/*__FILE__*/);\
	printf(fmt,##__VA_ARGS__);\
}while(0)
#else
#define dlbt_debug(fmt,...)	do{}while(0)
#endif


/* Extern Functions */
extern void signal_handler(int signo);


#endif
