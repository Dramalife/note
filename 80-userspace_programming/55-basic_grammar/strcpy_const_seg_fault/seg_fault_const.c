/*
 * note c const related file
 * Copyright (C) 2019 Dramalife

 * This file is part of [note](https://github.com/Dramalife/note.git)

 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* GCC VERSION
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* KERNEL VERSION
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC
 * 2015 i686 i686 i686 GNU/Linux
 */

/* Ref Url : https://www.cnblogs.com/liwei0526vip/p/8620595.html
	     https://www.runoob.com/w3cnote/const-char.html	*/

#include<string.h>
#include<stdlib.h> /*malloc*/
#include<signal.h>
#include<stdio.h>

/* ccp0_ptr is a pointer to const char */
const char *ccp0_ptr = "asdfghjkl"; 

const char ccp0_array[] = "abcabcabc"; 

/* ccp1 is a pointer to const char */
char const *ccp1;

/* cpc is a const pointer to char */
char * const cpc;

extern void signal_handler(int signo);
extern void dump(void);
extern int vdso_get(int argc, char **argv);

#define DEFAULT_SIZE (100 * sizeof(char))
#define VDSO_FILE_NAME "/tmp/vdso.txt"

void point_to_new_malloc(void)
{
	/*  global_ptr   : gcc-ok, exec-ok;
	 *  local_ptr    : gcc-ok, exec-ok;
	 *  global_array : gcc-error:incompatible types when assigning to type
	 *  ‘const char[11]’ from type ‘char *’
	 *  local_array  : gcc-error:incompatible types when assigning to type
	 *  ‘const char[11]’ from type ‘char *’
	 */
	const char *ptr_malloc = "7878787878"; 
	ptr_malloc = (char *)malloc(100 * sizeof(char));
	sprintf(ptr_malloc, __func__);
	printf("%s+%d:%s \n",__func__,__LINE__, ptr_malloc);
}

#define LI_BUFSIZE_GLOBAL1_LOCAL0	0
#if (1 == LI_BUFSIZE_GLOBAL1_LOCAL0)
const int bufsize = 1024;
#endif
void local_int_pointer(void)
{
#if (0 == LI_BUFSIZE_GLOBAL1_LOCAL0)
	const int bufsize = 1024;
#endif
	int *p = &bufsize;

	/* 0 == LI_BUFSIZE_GLOBAL1_LOCAL0
	 * gcc-ok, exec-ok*/
	/* 1 == LI_BUFSIZE_GLOBAL1_LOCAL0
	 * gcc-ok, exec-error
	 * why-error:TODO.*/
	*p = 2048;

	printf("bufsize = %d\n", bufsize);

	return;
}


const char *gchar_ptr = "8989898989"; 	 //nm-D
const char gchar_array[] = "9090909090"; //nm-R
void global_char_pointer(void)
{
	char *tmp_ptr = gchar_ptr;
	char *tmp_array = gchar_array;

	/* gcc-ok, exec-ok 
	 * D:The symbol is in the initialized data section.*/
	gchar_ptr = NULL;

	/* gcc-error : incompatible types when assigning to type ‘const
	 * 		char[11]’ from type ‘void *’ 
	 * R:The symbol is in a read only data section.*/
	//gchar_array = NULL;

	/* gcc-ok,exec-error */
	//sprintf(gchar_ptr, "abc");

	/* gcc-ok,exec-error */
	//sprintf(tmp_ptr, "abc");

	/* gcc-error : assignment of read-only location ‘*gchar_ptr’ */
	//gchar_ptr[0] = 'A';

	/* gcc-ok,exec-error */
	//tmp_ptr[0] = 'A';

	printf("%s,%d(%s) \n",__func__,__LINE__, gchar_ptr);

	/* gcc-ok,exec-error */
	//sprintf(gchar_array, "abc");

	/* gcc-ok,exec-error */
	//sprintf(tmp_array, "abc");

	/* gcc-error : assignment of read-only location ‘gchar_array[0]’ */
	//gchar_array[0] = 'A';

	/* gcc-ok,exec-error */
	//tmp_array[0] = 'A';

	printf("%s,%d(%s) \n",__func__,__LINE__, gchar_array);
}

void local_char_pointer(void)
{
#define LVAR_DEF_PTR1_ARRAY0	0 /* char *p2cc, or, char p2cc[]. */
#define LVAR_USE_P2CC1_TMP0	0 /* p2cc, or, char *tmp. */

#if LVAR_DEF_PTR1_ARRAY0
	/* seg fault : const char *p2cc = "aaa" */
	const char *p2cc = "aaa"; 
#else	
	/* no fault  : const char p2cc[] = "aaa" */
	const char p2cc[] = "aaa"; 
#endif

	char *tmp = p2cc;

#if LVAR_USE_P2CC1_TMP0
	/* LVAR_DEF_PTR1_ARRAY0 == 0,
	   gcc-ok , exec-ok .
	   why-ok : int sprintf(char *str, const char *format, ...);
	   char *str = p2cc, DANGEROUS !!! */
	/* LVAR_DEF_PTR1_ARRAY0 == 1,
	   gcc-ok , exec-error : Segmentation fault.
	   why-error : TODO.
	 */
	sprintf(p2cc,"2222");

	/* LVAR_DEF_PTR1_ARRAY0 == 0,
	   gcc-error , cannot-exec : 
	   assignment of read-only location ‘p2cc[2]’ */
	/* LVAR_DEF_PTR1_ARRAY0 == 1,
	   gcc-error , cannot-exec :
	   assignment of read-only location ‘*(p2cc + 2u)’ */
	//p2cc[2] = 'A';

#else   /* LVAR_USE_P2CC1_TMP0 == 0 */
	/* LVAR_DEF_PTR1_ARRAY0 == 0, 
	   gcc-ok , exec-ok . */
	/* LVAR_DEF_PTR1_ARRAY0 == 1,
	   gcc-ok , exec-error:Segmentation fault
	   why-error : TODO.*/
	sprintf(tmp,"3333");
	tmp[2] = 'Z';
#endif
	printf("%s+%d:%s ,define{PTR1_ARRAY0(%d),P2CC1_TMP0(%d)}\n",__func__, __LINE__,
	p2cc,LVAR_DEF_PTR1_ARRAY0,LVAR_USE_P2CC1_TMP0);

	return;
}

int main(void)
{
	signal(SIGSEGV, signal_handler);
#if 1
	/* Get vdso from "/proc/self/mem", and disassemble it. */
	char *argv[3]={"program",VDSO_FILE_NAME,"vdso"};
	vdso_get(3, argv);
	system("objdump -d /tmp/vdso.txt > vdso.ass");
#endif

	/* Point to the newly malloced memory */
	point_to_new_malloc();

	local_char_pointer();

	local_int_pointer();

	global_char_pointer();

	return 0;
}

