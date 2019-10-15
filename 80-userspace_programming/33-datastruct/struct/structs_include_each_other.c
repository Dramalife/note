/*
 * note "DataStruct - struct" related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * $ mips-linux-uclibc-gcc --version
 * mips-linux-uclibc-gcc (GCC) 4.3.3
 * Copyright (C) 2008 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-65-generic #74-Ubuntu SMP Tue Sep 17 17:06:04 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
 * ;
 * # uname -a
 * Linux host 2.6.31 #2 Mon Aug 30 11:11:11 CST 2020 mips GNU/Linux
 * ;
 * 
 * REF : https://www.runoob.com/cprogramming/c-structures.html
 *
 * Init : 2019.10.15;
 * Update 
 *
 */



#include <stdio.h>



struct B;    //对结构体B进行不完整声明

//结构体A中包含指向结构体B的指针
struct A
{
	struct B *partner;
	//other members;
};

//结构体B中包含指向结构体A的指针，在A声明完后，B也随之进行声明
struct B
{
	struct A *partner;
	//other members;
};



#if (defined DL_NOTE_STRUCT_PART_BUILD)&& (DL_NOTE_STRUCT_PART_BUILD == 1)
int main(void)
#else
int main_structs_include_each_other(void)
#endif
{
	printf("[%s,%d] TODO \n", __func__, __LINE__);
	return 0;
}
