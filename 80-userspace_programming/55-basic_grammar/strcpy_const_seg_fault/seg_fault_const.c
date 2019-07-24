/*
   note c const related file
   Copyright (C) 2019 Dramalife

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/* 
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC
 * 2015 i686 i686 i686 GNU/Linux
 */

/* Ref Url : https://blog.csdn.net/m0_37806112/article/details/81252151 */

#include<string.h>
#include<stdlib.h> /*malloc*/
#include<signal.h>
#include<stdio.h>


/* ccp0 is a pointer to const char */
const char *ccp0 = "asdfghjkl"; 

/* ccp1 is a pointer to const char */
char const *ccp1;

/* cpc is a const pointer to char */
char * const cpc;

/* Ref end. */


extern void signal_handler(int signo);
extern void dump(void);
extern int vdso_get(int argc, char **argv);

#define DEFAULT_SIZE (100 * sizeof(char))
#define VDSO_FILE_NAME "/tmp/vdso.txt"

/* ARG IN DECLARE  : const char *ccp0 = "asdfghjkl"; (Global)
   ERR SEG FAULT   : Y */
void seg_err_funa(char *pp)
{
	sprintf(pp, __func__);
}

/* ARG IN DECLARE  : const char *ccp0 = "asdfghjkl"; (Global)
   ERR SEG FAULT   : Y */
void seg_err_funz(const char **pp)
{
	sprintf(*pp, __func__);
}

/* ARG IN DECLARE  : const char *ccp0 = "asdfghjkl"; (Global)
   ERR SEG FAULT   : No */
void seg_err_fun_new_mem(const char **pp)
{
	*pp = (char *)malloc(100);
	sprintf(*pp, __func__);
}

void local_int_pointer(void)
{
	const int bufsize = 1024;/* IF declared as global, Segmentation fault. */
	int *p = &bufsize;
	*p = 2048;
	printf("bufsize = %d\n", bufsize);

	return;
}

void local_char_pointer(void)
{
#if 0	
	/* seg fault : const char *p2cc = "aaa" */
	const char *p2cc = "aaa"; 
#else	
	/* no fault  : const char p2cc[] = "aaa" */
	const char p2cc[] = "aaa"; 
#endif
	char *tmp = p2cc;

	sprintf(tmp,"3333");
	printf("%d,%s \n", __LINE__, p2cc);

	return;
}

int main(void)
{
	char *tmp;

	signal(SIGSEGV, signal_handler);
#if 1
	/* Get vdso from "/proc/self/mem", and disassemble it. */
	char *argv[3]={"program",VDSO_FILE_NAME,"vdso"};
	vdso_get(3, argv);
	system("objdump -d /tmp/vdso.txt > vdso.ass");
#endif
	tmp = ccp0;
	//ccp1 = tmp;

#if 1
	/* Point to the newly malloced memory. */
	printf("%d,%s \n",__LINE__,ccp0);
	seg_err_fun_new_mem(&ccp0);
#else
	/* When defined as global : const char *ccp0 = "asdfghjkl" */
	printf("%d,%s \n",__LINE__,ccp0);
	seg_err_funz(&ccp0);//seg fault
	//seg_err_funz(&tmp); //seg fault

	printf("%d,%s \n",__LINE__,ccp0);
	//seg_err_funa(ccp0);
#endif

	/* char *strcpy(char *dest, const char *src) */
	//strcpy(ccp0, "1234567");//seg fault
	printf("%d,%s \n",__LINE__,ccp0);

	//tmp[1] = 'Z';/*worked*/
	printf("%d,%s \n",__LINE__,ccp0);

	/* char *strcat(char *dest, const char *src) */
	//strcat(ccp0, "88");/* gcc:warning, seg fault */
	printf("%d,%s \n",__LINE__,ccp0);

	//ccp0[1] = 'c';	/* gcc:error */
	printf("%d,%s \n",__LINE__,ccp0);

	local_char_pointer();

	local_int_pointer();

	return 0;
}

