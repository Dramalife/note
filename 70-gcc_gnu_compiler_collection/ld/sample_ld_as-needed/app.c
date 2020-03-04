/*
 * [note](github.com/dramalife/note.git)
 * Dramalife@live.com
 * Init : 2020.03.04
 */
#include <stdio.h>

extern void func_in_libxxx(void);

int main(void)
{
	printf("File:%12s,Func:%14s,Line:%4d. \n",__FILE__,__func__,__LINE__);
	func_in_libxxx();
	return 0;
}
