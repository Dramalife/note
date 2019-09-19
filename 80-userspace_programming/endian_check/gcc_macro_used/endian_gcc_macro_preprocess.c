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


/* Below are necessary ! */
/* CASE - gcc(GCC)-4.8.5; TODO:more accurate; */
#if __GNUC__ == 4 && __GNUC_MINOR__ == 8 && __GNUC_PATCHLEVEL__ == 5
/* 	CHECK i686; */
#if ! defined(__i686)
#error def
#endif
/* 	CHECK if macros used are defined; */
#ifndef __BYTE_ORDER__ 
#error def
#endif
/* 	CHECK if macros used are defined; */
#ifndef __ORDER_LITTLE_ENDIAN__
#error def
#endif
#define DLWJY_X86

/* CASE - mips-linux-gcc(GCC)-4.3.3 */
#elif __GNUC__ == 4 && __GNUC_MINOR__ == 3 && __GNUC_PATCHLEVEL__ == 3
/*	CHECK mips;*/
#if ! __mips__ == 1
#error def
#endif
/*	CHECK bitsize;*/
#if ! _MIPS_SZPTR == 32
#error mips32 only
#endif
/* 	CHECK if macros used are defined; */
#ifndef __MIPSEB__
#error def
#endif
#define DLWJY_MIPS32

/* CASE - TODO */
#elif 0

/* CASE - END */
#endif

#if defined(DLWJY_X86) &&  (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)/* X86 - LittleEndian */ ||\
	defined(DLWJY_MIPS32) &&  !(__MIPSEB__ == 1)/* MIPS32 - Not BigEndian */
void func(void)
{
	printf("%s,%d ,For little endian \n",__func__,__LINE__);
}
#else
void func(void)
{
	printf("%s,%d ,For big endian \n",__func__,__LINE__);
	/* MIPS32
	 * # ./*pre.out
	 * func,82 ,For big endian 
	 */
}
#endif

void main(void)
{
	func();
}

