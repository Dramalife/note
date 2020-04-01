/*
   note debug print related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "gcc_related_show.h"


//#if __GNUC__ == 4 && __GNUC_MINOR__ == 8 && __GNUC_PATCHLEVEL__ == 5
//#error 4.8.5
//#elif 0
//#endif


void gcc_related_show_no_arg_in(unsigned int options)
{
	dl_compile_info_print(options);
}


#ifdef _DL_GCC_RELATED_SHOW_HAS_MAIN_
int main(int argc, char **argv)
{
	MAKE_GCC_HAPPY(argc);
	MAKE_GCC_HAPPY(argv);
	dl_compile_info_print(0xf);
	return 0;
}
#endif

