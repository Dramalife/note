/*
 * [note](github.com/dramalife/note.git)
 * Dramalife@live.com
 * Init : 2020.03.04
 */

/* shm related */
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include <stdio.h>

void func_in_libxxx(void)
{
	printf("File:%12s,Func:%14s,Line:%4d. \n",__FILE__,__func__,__LINE__);
	shm_open("abcd",O_RDWR, 0);
}
