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


/* Extern Functions - x86_64 */
#define IN_FILE_PLAT_MACRO_X86 \
extern void dlbt_signal_handler(int signo);
//#define signal_handler	dlbt_signal_handler


/* Extern Functions - armv7a */
#define IN_FILE_PLAT_MACRO_ARM \
#include <stdio.h>\
#include <stdlib.h>\
#include <signal.h>\
#include <assert.h>\
#include <ucontext.h>\
#include <string.h>\
extern void dlbt_signal_handler(unsigned int sn , siginfo_t  *si , void *ptr);


#if	defined(_DL_PLAT_X86_64_)
IN_FILE_PLAT_MACRO_X86
#elif	defined(_DL_PLAT_ARM_V7A_)
IN_FILE_PLAT_MACRO_ARM
#elif	defined(_DL_PLAT_ARM_V8A_)
IN_FILE_PLAT_MACRO_X86
#else
#error no inst
#endif


#endif
