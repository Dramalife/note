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
 * Init : 2019.09 19, Test passed at :
 *				ELF 32-bit MSB  executable, MIPS, MIPS32 rel2 version 1 (SYSV), dynamically linked (uses shared libs), stripped
 *				ELF 32-bit LSB  executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=35fbc00e14ca6d72705711f5890e4b74c465d59c, not stripped
 * ;
 * Update 
 *
 */


#include <stdio.h>


int main(void)
{
	int i = 1;
	unsigned char *pointer = (unsigned char *)&i;
	printf("%s endian \n", *pointer ? "little":"big");

	/* mips32-MSB-result:
	 * # ./*int.out
	 * big endian 
	 */
}
