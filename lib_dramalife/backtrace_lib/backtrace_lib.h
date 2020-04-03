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
#ifdef _DLBT_DEBUG_ENABLED_
#define dlbt_debug(fmt,...)	do{\
	printf("[%s] ","[libdl-bt] "/*__FILE__*/);\
	printf(fmt,##__VA_ARGS__);\
}while(0)
#else
#define dlbt_debug(fmt,...)	do{}while(0)
#endif


/* 
 * Extern Functions - x86_64
 */
#ifdef  __x86_64__
#define signal_handler	dlbt_signal_handler
extern void dlbt_signal_handler(int signo);
/*
 * Extern Functions - armv7a
 */
#elif (defined __ARM_ARCH_7A__)
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <ucontext.h>
#include <string.h>
extern void dlbt_signal_handler(unsigned int sn , siginfo_t  *si , void *ptr);
/*
 * Extern Functions - UNKNOWN(error)
 */
#else
#error no inst
#endif


#endif
