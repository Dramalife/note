/*
 * note "datastruct - union" related file
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
 * $ ./mips-linux-uclibc-gcc --version
 * mips-linux-uclibc-gcc (GCC) 4.3.3
 * Copyright (C) 2008 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 *
 * $ uname -a
 * Linux host 2.6.31 #2 Mon Aug 12 11:09:22 CST 2019 mips GNU/Linux
 * ;
 * $ uname -a
 * Linux server 4.15.0-65-generic #74-Ubuntu SMP Tue Sep 17 17:06:04 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * REF URL : https://www.runoob.com/cprogramming/c-unions.html
 *
 * Init : 2019.10.12;
 * Update 
 *
 */



#include <stdio.h>
#include <string.h>
#include <sys/types.h>


/* Data Struct */
union Data
{
	int i;
	float f;
	char  str[20];
};


/* FUNC : "int endian_test(void)";
 * a.out: ELF 32-bit MSB executable, MIPS, MIPS32 rel2 version 1 (SYSV), dynamically linked, interpreter /lib/ld-, with debug_info, not stripped;
 * a.out: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/l, 
 *		for GNU/Linux 3.2.0, BuildID[sha1]=41f92edd2e1b30108089f2942a92db893e3e0485, not stripped;
 */
int endian_test(void)
{
	union Data data;

	printf("\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

	data.i= 0x01020304;
	if( data.str[0] == 0x01 )
	{
		printf("Big Endian! \n");/* Tested passed on MIPS32(BE). */
	}
	else if( data.str[0] == 0x04 )
	{
		printf("Little Endian! \n");/* Tested passed on x86_64(LE). */
	}
	else
	{
		printf("Unknown! \n");
	}

	return 0;
}

int size_union(void)
{
	union Data data;        

	printf("\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

#if ( (defined __SIZE_WIDTH__) && (__SIZE_WIDTH__ == 64)) || ( (defined __SIZEOF_POINTER__)&&(__SIZEOF_POINTER__ == 8) )
	printf( "Memory size occupied by data : %ld\n", sizeof(data));
#elif ( (defined __SIZEOF_POINTER__) && ((__SIZEOF_POINTER__ == 4)) )
	printf( "Memory size occupied by data : %d\n", sizeof(data));
#else
#error Get word size failed !
#endif

	//TODO - %jd
	//printf( "Memory size occupied by data : %jd\n", (int128_t)sizeof(data));

	return 0;
}

int value_set_overwrite(void)
{
	union Data data;        

	printf("\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

	data.i = 10;
	data.f = 220.5;
	strcpy( data.str, "C Programming");

	printf( "data.i : %d\n", data.i);
	printf( "data.f : %f\n", data.f);
	printf( "data.str : %s\n", data.str);

	return 0;
}

int value_set(void)
{
	union Data data;        

	printf("\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

	data.i = 10;
	printf( "data.i : %d\n", data.i);

	data.f = 220.5;
	printf( "data.f : %f\n", data.f);

	strcpy( data.str, "C Programming");
	printf( "data.str : %s\n", data.str);

	return 0;
}

#ifdef DL_NOTE_UNION_PART_BUILD
int main(void)
#else
int main_union(void)
#endif
{
	printf("[%s,%d]START! \n",__func__,__LINE__);

	size_union();
	value_set_overwrite();
	value_set();
	endian_test();
	return 0;
}

#if (DL_NOTE_UNION2_PART_BUILD == 3)
#error Just For Testing.
#endif

