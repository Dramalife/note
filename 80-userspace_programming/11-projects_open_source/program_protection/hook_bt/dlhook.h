#ifndef DLHOOK
#define DLHOOK
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* dynamic library */
#include <dlfcn.h>

/* backtrace */
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* socket-unix */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
//#define UNIX_DOMAIN "/tmp/.unix.domain"
#define UNIX_DOMAIN ".unix.domain"
#define MSG_START_STR	"###start###"
#define MSG_END_STR	"###end###"


/* Program Detect Daemon */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#define DFILE_END_LINE	"#ELINE"


/*va_args*/
#include <stdarg.h>


//#define _DL_PLAT_X86_64_	1
#define _DL_PLAT_ARM_V7A_	1

/* Debug Print */
#ifdef _DLBT_DEBUG_ENABLED_
#define dlbt_debug(fmt,...)	do{\
	printf("[%s] ","[libdl-bt] "/*__FILE__*/);\
	printf(fmt,##__VA_ARGS__);\
}while(0)
#else
#define dlbt_debug(fmt,...)	do{}while(0)
#endif


#define MAKE_GCC_HAPPY(x)	


/* Extern Functions - x86_64 */
#define IN_FILE_PLAT_MACRO_X86 \
extern void dlbt_signal_handler(int signo);


#if	defined(_DL_PLAT_X86_64_)
IN_FILE_PLAT_MACRO_X86
#elif	defined(_DL_PLAT_ARM_V7A_)
/* Extern Functions - armv7a */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <ucontext.h>
#include <string.h>
extern void dlbt_signal_handler(unsigned int sn , siginfo_t  *si , void *ptr);
#elif	defined(_DL_PLAT_ARM_V8A_)
IN_FILE_PLAT_MACRO_X86
#else
#error no inst
#endif



struct message_pdd
{
#define MSG_DATA_SIZE	1024//(MSG_SIZE - sizeof(struct message_pdd))
#define MSG_SIZE	sizeof(struct message_pdd) + MSG_DATA_SIZE
	int pid;
	char *data;
};

//int printf(const char *format, ...);
int scanf(const char *format, ...);

#endif
