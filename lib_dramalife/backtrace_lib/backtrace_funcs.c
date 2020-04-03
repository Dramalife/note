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
 * Code of dramalife-lib-backtrace .
 */
#ifdef _DL_BACKTRACE_LIB_ENABLE_
#ifdef __x86_64__
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
#elif (defined __ARM_ARCH_7A__)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <ucontext.h>
#include <string.h>

void dlbt_signal_handler(unsigned int sn , siginfo_t  *si , void *ptr);

typedef struct
{
	const char *dli_fname;	/* File name of defining object.  */
	void *dli_fbase;		/* Load address of that object.  */
	const char *dli_sname;	/* Name of nearest symbol.比如函数名*/
	void *dli_saddr;		/* Exact value of nearest symbol.比如函数的起始地址*/
} Dl_info;

struct ucontext_ce123
{
	unsigned long	  uc_flags;
	struct ucontext  *uc_link;
	stack_t		  uc_stack;
	struct sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask last for extensibility */
}ucontext_ce123_;

struct sigframe_ce123
{  
	struct sigcontext sc;//保存一组寄存器上下文  
	unsigned long extramask[1];  
	unsigned long retcode;//保存返回地址  
	//struct aux_sigframe aux __attribute__((aligned(8)));  
}sigframe_ce123; 

static int backtrace_ce123 (void **array, int size);
static char ** backtrace_symbols_ce123 (void *const *array, int size);


static int backtrace_ce123 (void **array, int size)
{
	if (size <= 0)
		return 0;

	int *fp = 0;
	int *next_fp = 0;
	int cnt = 0;
	int ret = 0;

	__asm__(
			"mov %0, fp\n" 
			: "=r"(fp)
	       );


	array[cnt++] = (void *)(*(fp-1));

	next_fp = (int *)(*(fp-3));

	while((cnt <= size) && (next_fp != 0))
	{
		array[cnt++] = (void *)*(next_fp - 1);
		next_fp = (int *)(*(next_fp-3));
	}

	ret = ((cnt <= size)?cnt:size);
	printf("Backstrace (%d deep)\n", ret);

	return ret;
}

static char ** backtrace_symbols_ce123 (void *const *array, int size)
{
# define WORD_WIDTH 8
	Dl_info info[size];
	int status[size];
	int cnt;
	size_t total = 0;
	char **result;

	/* Fill in the information we can get from `dladdr'.  */
	for (cnt = 0; cnt < size; ++cnt)
	{
		status[cnt] = _dl_addr (array[cnt], &info[cnt]);
		if (status[cnt] && info[cnt].dli_fname && info[cnt].dli_fname[0] != '\0')
		{
			/* We have some info, compute the length of the string which will be
			   "<file-name>(<sym-name>) [+offset].  */
			total += (strlen (info[cnt].dli_fname ?: "")
					+ (info[cnt].dli_sname ? strlen (info[cnt].dli_sname) + 3 + WORD_WIDTH + 3 : 1)
					+ WORD_WIDTH + 5);
		}
		else
		{
			total += 5 + WORD_WIDTH;
		}
	}


	/* Allocate memory for the result.  */
	result = (char **) malloc (size * sizeof (char *) + total);
	if (result != NULL)
	{
		char *last = (char *) (result + size);

		for (cnt = 0; cnt < size; ++cnt)
		{
			result[cnt] = last;

			if (status[cnt] && info[cnt].dli_fname && info[cnt].dli_fname[0] != '\0')
			{
				char buf[20];

				if (array[cnt] >= (void *) info[cnt].dli_saddr)
					sprintf (buf, "+%#lx", \
							(unsigned long)(array[cnt] - info[cnt].dli_saddr));
				else
					sprintf (buf, "-%#lx", \
							(unsigned long)(info[cnt].dli_saddr - array[cnt]));

				last += 1 + sprintf (last, "%s%s%s%s%s[%p]",
						info[cnt].dli_fname ?: "",
						info[cnt].dli_sname ? "(" : "",
						info[cnt].dli_sname ?: "",
						info[cnt].dli_sname ? buf : "",
						info[cnt].dli_sname ? ") " : " ",
						array[cnt]);
			}
			else
				last += 1 + sprintf (last, "[%p]", array[cnt]);
		}
		assert (last <= (char *) result + size * sizeof (char *) + total);
	}

	return result;
}

/* SIGSEGV信号的处理函数，回溯栈，打印函数的调用关系*/
void dlbt_signal_handler(unsigned int sn , siginfo_t  *si , void *ptr)
{
	/*int *ip = 0;
	  __asm__(
	  "mov %0, ip\n" 
	  : "=r"(ip)
	  );
	  printf("sp = 0x%x\n", ip);
	  struct sigframe_ce123 * sigframe = (struct sigframe_ce123 * )ip;*/
	 MAKE_GCC_HAPPY(sn);

	if(NULL != ptr)
	{
		printf("\n\nunhandled page fault (%d) at: 0x%p\n", si->si_signo,si->si_addr);

		struct ucontext_ce123 *ucontext = (struct ucontext_ce123 *)ptr;
		int pc = ucontext->uc_mcontext.arm_pc;		

		void *pc_array[1]; 
		pc_array[0] = pc;
		char **pc_name = backtrace_symbols_ce123(pc_array, 1);
		printf("%d: %s\n", 0, *pc_name);

#define SIZE 100
		void *array[SIZE];
		int size, i;
		char **strings;
		size = backtrace_ce123(array, SIZE);
		strings = backtrace_symbols_ce123(array, size);	

		for(i=0;i<size;i++)
		{
			printf("%d: %s\n", i+1, strings[i]);
		}
		free(strings);
	}
	else
	{
		printf("error!\n");
	}

	exit(-1);
}
#else
#error no inst
#endif
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
int sample_syscall_free()
{
	free((void *)sample_syscall_free);
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
#if 0
	signal(SIGSEGV, dlbt_signal_handler);
#else
	struct sigaction s;
	s.sa_flags = SA_SIGINFO;
	s.sa_sigaction = (void *)dlbt_signal_handler;
	sigaction (SIGSEGV,&s,NULL);
	sigaction (SIGABRT,&s,NULL);
#endif

	/* Set resource limit of coredump */
	dl_set_coredump_unlimit();

	if(argc > 1)
	{
		/* Sample - Segment Fault */
		if(matched_string(argv[1],"seg"))
			sample_segment_err1();
		else if(matched_string(argv[1],"kill"))
			sample_syscall_kill1();
		else if(matched_string(argv[1],"free"))
			sample_syscall_free();
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
