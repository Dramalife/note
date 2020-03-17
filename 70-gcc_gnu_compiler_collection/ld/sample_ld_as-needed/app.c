/*
 * [note](github.com/dramalife/note.git)
 * Dramalife@live.com
 * Init : 2020.03.04
 * Update : 2020.03.17, Add _LIB_USE_VAR_DEFINED_BY_APP
 */
#include <stdio.h>

extern void func_in_libxxx(void);

#ifdef _LIB_USE_VAR_DEFINED_BY_APP
int var_a=6;
#endif

int main(void)
{
	printf("File:%-12s,Func:%-14s,Line:%-4d. \n",__FILE__,__func__,__LINE__);
	func_in_libxxx();

#ifdef _LIB_USE_VAR_DEFINED_BY_APP
	printf("File:%-12s,Func:%-14s,Line:%-4d,Var:%d. \n",__FILE__,__func__,__LINE__,var_a);
#endif

	return 0;
}
