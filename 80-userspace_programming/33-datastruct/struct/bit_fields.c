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


#if (defined DL_NOTE_STRUCT_PART_BUILD)&& (DL_NOTE_STRUCT_PART_BUILD == 1)
int main(void)
#else
int main_bit_fields(void)
#endif
{
	struct bs
	{
		unsigned a:1;
		unsigned b:3;
		unsigned c:4;
	} bit,*pbit;

	bit.a=1;    /* 给位域赋值（应注意赋值不能超过该位域的允许范围） */
	bit.b=7;    /* 给位域赋值（应注意赋值不能超过该位域的允许范围） */
	bit.c=15;    /* 给位域赋值（应注意赋值不能超过该位域的允许范围） */
	printf("%d,%d,%d\n",bit.a,bit.b,bit.c);    /* 以整型量格式输出三个域的内容 */

	pbit=&bit;    /* 把位域变量 bit 的地址送给指针变量 pbit */
	pbit->a=0;    /* 用指针方式给位域 a 重新赋值，赋为 0 */
	pbit->b&=3;    /* 使用了复合的位运算符 "&="，相当于：pbit->b=pbit->b&3，位域 b 中原有值为 7，与 3 作按位与运算的结果为 3（111&011=011，十进制值为 3） */
	pbit->c|=1;    /* 使用了复合位运算符"|="，相当于：pbit->c=pbit->c|1，其结果为 15 */
	printf("%d,%d,%d\n",pbit->a,pbit->b,pbit->c);    /* 用指针方式输出了这三个域的值 */

	return 0;
}

