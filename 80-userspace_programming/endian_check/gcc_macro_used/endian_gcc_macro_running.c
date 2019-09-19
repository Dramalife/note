/*
 * note "endian" related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux;
 * 
 * Init : 2019.09 19;
 * Update 
 *
 */


#include <stdio.h>


/* Below are necessary ! */
#ifndef __BYTE_ORDER__ 
#error def
#endif
#ifndef __ORDER_LITTLE_ENDIAN__
#error def
#endif



void main(void)
{
	printf("%s endian \n", __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ? "little" : "big");
}

