/*
   note debug print related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include "gcc_related_show.h"

/*
USE : 
gcc_related_show_no_arg_in( GCC_R_SHOW_VERSION | GCC_R_SHOW_DATE |
GCC_R_SHOW_TIME );
No arg in,such as "__LINE__"
*/
void gcc_related_show_no_arg_in(unsigned int options)
{
#if __GNUC__ == 4 && __GNUC_MINOR__ == 8 && __GNUC_PATCHLEVEL__ == 5
#error 4.8.5
#elif 0
#endif
	if( options & GCC_R_SHOW_VERSION)
		printf("GCC VER:(%s)",__VERSION__);
	if( options & GCC_R_SHOW_DATE)
		printf(" DATE:(%s)",__DATE__);
	if( options & GCC_R_SHOW_TIME)
		printf(" TIME:(%s)",__TIME__);


printf("\n VERSION IN INT :(%d)(%d)(%d) \n",__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__);
	printf("\n");
	return;
}

