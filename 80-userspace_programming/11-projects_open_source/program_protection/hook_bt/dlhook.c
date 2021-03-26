/*
 * Init : 2020.04
 *	copy from github.com/Dramalife/note.git
 * Update : 2020.05.08
 * 	printf() was hooked, should using dprintf(1,...) to print info in this lib
 */


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



#include "dlhook.h"


void get_stack_backtrace(void);


/* printf */
#if 1
typedef int (*PRINTF)(const char *format, ...);
PRINTF printf_glibc = NULL;
int printf(const char *format, ...)
{
	void *handle = dlopen("libc.so.6", RTLD_LAZY);
	printf_glibc = (PRINTF)dlsym(handle, "printf");
	
	get_stack_backtrace();

	va_list ap;
	char buff[256]={0};
	va_start(ap, format);
	vsnprintf(buff, sizeof(buff), format, ap);
	va_end(ap);
	int ret = printf_glibc(buff);
	return ret;
}
#endif

/* send stack to pdd via socket */
int send_to_pdd(char *c_msg, int c_size)
{
	int com_fd;
	int ret;
	int i;

	static struct sockaddr_un srv_addr;
	static struct sockaddr_un clt_addr;
	char clt_file[]="/tmp/xxxx";

	srv_addr.sun_family=AF_UNIX;
	strcpy(srv_addr.sun_path,UNIX_DOMAIN);
	
	com_fd=socket(PF_UNIX,SOCK_DGRAM,0);
	if(com_fd<0){
		perror("cannot create communication socket");
		return 1;
	}	
	
	mkstemp(clt_file);	
	clt_addr.sun_family=AF_UNIX;
	strcpy(clt_addr.sun_path,clt_file);
	unlink(clt_file);
	
	ret=bind(com_fd,(struct sockaddr*)&clt_addr,sizeof(clt_addr.sun_family)+strlen(clt_addr.sun_path));
        if(ret==-1){
                perror("cannot bind server socket");
                return 1;
        }

	char *buff = (char *)malloc( MSG_SIZE * sizeof(char) );
	memset(buff, 0, MSG_SIZE);
	if(buff)
	{
		struct message_pdd *msg_ptr = (struct message_pdd *)buff;
		msg_ptr->pid = getpid();
		msg_ptr->data = buff + MSG_SIZE - MSG_DATA_SIZE;
		//dprintf(1, "%d,%d\n",c_size,MSG_DATA_SIZE);
		strncpy(msg_ptr->data, c_msg, (c_size>=MSG_DATA_SIZE)?MSG_DATA_SIZE:c_size);
		//dprintf(1, "@@@@@%s\n",msg_ptr->data);
		int num=sendto(com_fd,msg_ptr,MSG_SIZE,0,(struct sockaddr*)&srv_addr,sizeof(struct sockaddr));
		if(-1 == num)
		{
			//perror("sendto");
		}
		free(buff);
		buff = NULL;
	}

	close(com_fd);
	unlink(clt_file);
	return 0;
}

void get_stack_backtrace(void)
{
#define BT_BUF_SIZE 100
	int j, nptrs;
	void *buffer[BT_BUF_SIZE];
	char **strings;

	nptrs = backtrace(buffer, BT_BUF_SIZE);
	//dprintf(1, "backtrace() returned %d addresses\n", nptrs);

	/* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
	   would produce similar output to the following: */

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	int en_show = 0;
	char dl_buff[BT_BUF_SIZE]={0};
	char *dl_ptr;
	send_to_pdd(MSG_START_STR, strlen(MSG_START_STR));
	for (j = 0; j < nptrs; j++)
	{
#if 0 //show 1st usr func
		if( strstr(strings[j], "dlhook") )
		{
			en_show = 1;
		}
		else if(en_show)
		{
			// ./for_gdb.out(func_d+0x1b) [0x7f5d39a4]
			dprintf(1, "%s\n", strings[j]);
			strncpy(dl_buff, strings[j], sizeof(dl_buff));
			dl_ptr = strchr(dl_buff, '+');
			memset(dl_ptr, 0, strlen(dl_ptr));
			dl_ptr = strchr(dl_buff, '(');
			dl_ptr++;
			dprintf(1, "==>%s \n",dl_ptr);
			en_show = 0;
		}
#else // show all usr func
		if( strstr(strings[j], ".out") )
		{
			// ./for_gdb.out(func_d+0x1b) [0x7f5d39a4]
			//dprintf(1, "%s\n", strings[j]);
			strncpy(dl_buff, strings[j], sizeof(dl_buff));
			dl_ptr = strchr(dl_buff, '+');
			memset(dl_ptr, 0, strlen(dl_ptr));
			dl_ptr = strchr(dl_buff, '(');
			dl_ptr++;

			/* Compatible with x86, ignore "_start" */
			if( NULL == strstr(dl_ptr, "_start") )
			{
				//dprintf(1, "==>%s \n",dl_ptr);
				send_to_pdd(dl_ptr, strlen(dl_ptr));
			}
		}
#endif
	}
	send_to_pdd(MSG_END_STR, strlen(MSG_END_STR));

	free(strings);
}

/* strcmp */
typedef int (*STRCMP)(const char *, const char *);
STRCMP strcmp_glibc = NULL;

/* scanf */
#if 0
typedef int (*SCANF)(const char *format, ...);
SCANF scanf_glibc = NULL;
int scanf(const char *format, ...)
{
	//void *handle = dlopen("libc.so.6", RTLD_LAZY);
	//scanf_glibc = (SCANF)dlsym(handle, "scanf");
	
	get_stack_backtrace();

	va_list ap;
	va_start(ap, format);
	int ret = scanf_glibc(format, ap);
	va_end(ap);
	return ret;
}
#endif

/* system */
typedef int (*SYSTEM)(const char *command);
SYSTEM system_glibc = NULL;
int system(const char *command)
{
	void *handle = dlopen("libc.so.6", RTLD_LAZY);
	system_glibc = (SYSTEM)dlsym(handle, "system");

	get_stack_backtrace();

	return system_glibc(command);
}

/* sleep */
typedef unsigned int (*SLEEP)(unsigned int seconds);
SLEEP sleep_glibc = NULL;
unsigned int sleep(unsigned int seconds)
{
	void *handle = dlopen("libc.so.6", RTLD_LAZY);
	sleep_glibc = (SLEEP)dlsym(handle, "sleep");

	get_stack_backtrace();

	return sleep_glibc(seconds);
}

#if 0
#define REG_HOOK_FUNC(HFRTYPE, HFTYPE, HFARGS, HFNAME)	\
typedef #HFRTYPE	(*#HFTYPE)(#HFARGS);\
#HFTYPE #HFNAME##_glibc = NULL;\
#HFRTYPE #HFNAME(#HFARGS)
#endif

/* random */
#if 0
REG_HOOK_FUNC(long int, RANDOM, void, random)
{
	void *handle = dlopen("libc.so.6", RTLD_LAZY);
	random_glibc = (RANDOM)dlsym(handle, "random");

	get_stack_backtrace();

	return random_glibc();
}
#else
typedef long int (*RANDOM)(void);
RANDOM random_glibc = NULL;
long int random(void)
{
	void *handle = dlopen("libc.so.6", RTLD_LAZY);
	random_glibc = (RANDOM)dlsym(handle, "random");

	get_stack_backtrace();

	return random_glibc();
}
#endif

