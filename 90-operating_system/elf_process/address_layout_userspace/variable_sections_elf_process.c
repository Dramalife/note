/*
 * note "section of elf" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-70-generic #79-Ubuntu SMP Tue Nov 12 10:36:11 UTC 2019 \
 *	x86_64 x86_64 x86_64 GNU/Linux;
 * 
 * Source Url : https://www.cnblogs.com/51qianrushi/p/4294264.html
 *
 * Init : 2019.11.24
 * 	COPY FROM : "Source Url" ;
 * Update : 2019.11.24
 *	CHANGE PRINT FORMAT, MACRO USED !
 *
 */



#include <stdio.h>
#include <stdlib.h>

// For getpid()
#include <sys/types.h>
#include <unistd.h>



// 2019.11.24, Dramalife smiled ;-) 
void show_print(char *str, void *ptr)
{
	printf("NAME(%24s), ADDR(%16p), VAL(%8d) \n\n",str, ptr, *(int *)ptr );
}
#define A_MACRO(x)	do{show_print(#x,&x);}while(0)
#define A_MACRO222(x)	do{show_print(#x,x);}while(0)
#define SHOW_ALL_USING_MACRO_DRAMALIFE()	do{	\
A_MACRO(global_init_a		); 	\
A_MACRO(global_uinit_a		); 	\
A_MACRO(static_global_init_a	); 	\
A_MACRO(static_global_uinit_a	); 	\
A_MACRO(const_global_a		); 	\
A_MACRO(global_init_b		); 	\
A_MACRO(global_uinit_b		); 	\
A_MACRO(static_global_init_b	); 	\
A_MACRO(static_global_uinit_b	); 	\
A_MACRO(const_global_b		); 	\
A_MACRO(local_init_a		); 	\
A_MACRO(local_uinit_a		); 	\
A_MACRO(static_local_init_a	); 	\
A_MACRO(static_local_uinit_a	); 	\
A_MACRO(const_local_a		); 	\
A_MACRO(local_init_b		); 	\
A_MACRO(local_uinit_b		); 	\
A_MACRO(static_local_init_b	); 	\
A_MACRO(static_local_uinit_b	); 	\
A_MACRO(const_local_b		); 	\
A_MACRO222(malloc_p_a		); 	\
}while(0)


#define SHOW_ALL_PRINT_ORIGINAL_LIKE()	do{\
	printf("&global_init_a=		"	 \
					"[%16p,%8d]\n\n",&global_init_a,global_init_a); \
	printf("&global_uinit_a=	" \
					"[%16p,%8d]\n\n",&global_uinit_a,global_uinit_a); \
	printf("&static_global_init_a=	" \
					"[%16p,%8d]\n\n",&static_global_init_a,static_global_init_a); \
	printf("&static_global_uinit_a	" \
					"[%16p,%8d]\n\n",&static_global_uinit_a,static_global_uinit_a); \
	printf("&const_global_a=	" \
					"[%16p,%8d]\n\n",&const_global_a,const_global_a); \
	printf("&global_init_b=	        " \
					"[%16p,%8d]\n\n",&global_init_b,global_init_b); \
	printf("&global_uinit_b=	" \
					"[%16p,%8d]\n\n",&global_uinit_b,global_uinit_b); \
	printf("&static_global_init_b=	" \
					"[%16p,%8d]\n\n",&static_global_init_b,static_global_init_b); \
	printf("&static_global_uinit_b	" \
					"[%16p,%8d]\n\n",&static_global_uinit_b,static_global_uinit_b); \
	printf("&const_global_b=	" \
					"[%16p,%8d]\n\n",&const_global_b,const_global_b); \
	printf("&local_init_a=	        " \
					"[%16p,%8d]\n\n",&local_init_a,local_init_a); \
	printf("&local_uinit_a=	        " \
					"[%16p,%8d]\n\n",&local_uinit_a,local_uinit_a); \
	printf("&static_local_init_a=	" \
					"[%16p,%8d]\n\n",&static_local_init_a,static_local_init_a); \
	printf("&static_local_uinit_a	" \
					"[%16p,%8d]\n\n",&static_local_uinit_a,static_local_uinit_a); \
	printf("&const_local_a=	        " \
					"[%16p,%8d]\n\n",&const_local_a,const_local_a); \
	printf("&local_init_b=	        " \
					"[%16p,%8d]\n\n",&local_init_b,local_init_b); \
	printf("&local_uinit_b=	        " \
					"[%16p,%8d]\n\n",&local_uinit_b,local_uinit_b); \
	printf("&static_local_init_b=	" \
					"[%16p,%8d]\n\n",&static_local_init_b,static_local_init_b); \
	printf("&static_local_uinit_b	" \
					"[%16p,%8d]\n\n",&static_local_uinit_b,static_local_uinit_b); \
	printf("&const_local_b=	        " \
					"[%16p,%8d]\n\n",&const_local_b,const_local_b); \
	printf("malloc_p_a=		"		 \
					"[%16p,%8d]\n\n",malloc_p_a,*malloc_p_a); \
	}while(0)


int global_init_a = 1;//全局初始化的变量
int global_uinit_a;//全局未初始化的变量
static int static_global_init_a = 1;//全局静态初始化变量
static int static_global_uinit_a;//全局静态未初始化变量
const int const_global_a = 1;//全局常量

int global_init_b = 1;//全局初始化的变量
int global_uinit_b;//全局未初始化的变量
static int static_global_init_b = 1;//全局静态初始化变量
static int static_global_uinit_b;//全局静态未初始化变量
const int const_global_b = 1;//全局常量


int main(void)
{
	int local_init_a = 1;//局部初始化变量
	int local_uinit_a;//局部未初始化变量
	static int static_local_init_a = 1;//局部静态初始化变量
	static int static_local_uinit_a;//局部静态未初始化变量
	const int const_local_a = 1;//局部常量

	int local_init_b = 1;//局部初始化变量
		int local_uinit_b;//局部未初始化变量
	static int static_local_init_b = 1;//局部静态初始化变量
	static int static_local_uinit_b;//局部静态未初始化变量
	const int const_local_b = 1;//局部常量

	int *malloc_p_a;
	malloc_p_a = malloc(sizeof(int));//通过malloc分配得到的局部

	// Print maps
	char cmd[256];
	sprintf(cmd, "cat /proc/%d/maps", getpid());
	printf("CMD[%s] \n",cmd);
	system(cmd);

	SHOW_ALL_USING_MACRO_DRAMALIFE();
	//SHOW_ALL_PRINT_ORIGINAL_LIKE();

	while(1);

	return 0;
}
