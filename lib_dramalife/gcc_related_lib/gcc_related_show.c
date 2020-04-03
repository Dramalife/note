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


/* Debug Print */
#ifdef _DLGCC_DEBUG_ENABLED_
#define dl_gcc_debug(fmt,...)	do{printf(fmt,##__VA_ARGS__);}while(0)
#else
#define dl_gcc_debug(f,...)	do{}while(0)
#endif

/* Library Code */
#ifdef _DL_GCC_LIB_ENABLE_
#endif


/* Demo Code */
#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(int argc, char **argv)
{
	MAKE_GCC_HAPPY(argc);
	MAKE_GCC_HAPPY(argv);
	dl_gcc_print_compile_info(0xf, dl_gcc_debug);
	return 0;
}
#endif
