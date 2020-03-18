/*
 * [note](github.com/dramalife/note.git)
 * Dramalife@live.com
 * Init : 2020.03.04
 * Update : 2020.03.17, Add _LIB_USE_VAR_DEFINED_BY_APP
 */

/* shm related */
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include <stdio.h>

#ifdef _LIB_USE_VAR_DEFINED_BY_APP
extern int var_a;
#endif

void func_in_libxxx(void)
{
	printf("File:%-12s,Func:%-14s,Line:%-4d. \n",__FILE__,__func__,__LINE__);
	shm_open("abcd",O_RDWR, 0);

#ifdef _LIB_USE_VAR_DEFINED_BY_APP
	printf("File:%-12s,Func:%-14s,Line:%-4d,Var:%d. \n",__FILE__,__func__,__LINE__,var_a);
#endif
}
