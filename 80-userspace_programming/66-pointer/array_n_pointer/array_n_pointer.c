/*
 * note "array & pointer" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
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
 *
 * $ uname -a
 * Linux server 4.15.0-70-generic #79-Ubuntu SMP Tue Nov 12 10:36:11 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : 2019.12.17
 *	KEY_WORD : [array], [pointer], [sizeof], [pointer/address offset];
 * Update 
 *
 */



#include <stdio.h>

int argu(char arg_array[])
{
	printf("sizeof_array_arg(%d) \n",arg_array);	//get array size failed in this way
}

int main(void)
{
#define BUFF_SIZE	15
	char c_array[BUFF_SIZE] = {'\0'};
	char *c_pointer = (char *)malloc(BUFF_SIZE * sizeof(char));

	/* Difference between array and pointer 1 ---"sizeof" */
	printf(
			"SIZEOF: \n"
			"sizeof_char_array(%d),var_address(0x%x)-stack-increase \n"
			"sizeof_char_pointer(%d),var_address(0x%x)-heap-decrease \n"
			,sizeof(c_array), &c_array	// 15 = (array_len * sizeof(type) )
			,sizeof(c_pointer), &c_pointer	// 8(x86_64)
	      );
	argu(c_array);

	//Fill data for testing
	memset(c_array, 'A', BUFF_SIZE);
	memset(c_pointer, 'P', BUFF_SIZE);

	/* Difference between array and pointer 2 ---"&"(get address) */
	/* array pointer  &  pointer to pointer */
	/* Address of array
	 * 	type array[array_len];
	 * 	&array + 1 : offset sizeof(array) (array_len * sizeof(type))
	 */
	printf(
			"&array		"	"0x%x"	"\n"
			"&pointer	"	"0x%x"	"\n"
			"&array  +1	"	"0x%x"	"\n"//pointer2array   + 1	//addr + sizeof(array)!!!!!	//addr + Fbytes(x86_64)
			"&pointer+1	"	"0x%x"	"\n"//pointer2pointer + 1	//addr + sizeof(pointer)	//addr + 8bytes(x86_64)
			,&c_array
			,&c_pointer
			,(&c_array   + 1)//offset sizeof(array)
			,(&c_pointer + 1)
	      );
	void *p2array = &c_array;
	void *p2pointer = &c_pointer;
	printf(
			"pointer2array	"	"0x%x"	"\n"
			"pointer2pointer"	"0x%x"	"\n"
			"p2a + 1	"	"0x%x"	"\n"
			"p2p + 1	"	"0x%x"	"\n"
			,p2array
			,p2pointer
			,p2array + 1	//addr +1 byte
			,p2pointer + 1	//addr +1 byte
	      );

	return 0;
}
