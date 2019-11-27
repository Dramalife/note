/*
* note gcc 80-55 struct related file
* Copyright (C) 2019 Dramalife@live.com
* 
* This file is part of [note](https://github.com/Dramalife/note.git)
* 
* note is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* INIT : 2019.08.08
* UPDATE : 2019.11.27
* 	init struct variable, sizeof struct, sizeof type;
* UPDATE : 
*
* $ gcc --version
* gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
* Copyright (C) 2015 Free Software Foundation, Inc.
* This is free software; see the source for copying conditions.  There is NO
* warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* 
* $ uname -a
* Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015
* i686 i686 i686 GNU/Linux
* 
*/

#include<stdio.h>
#include <string.h>

struct st_one_item
{
	int num;
};

void test_chg_num(struct st_one_item *argin)
{
	argin->num ++;
	return ;
}

int main(void)
{
	// init struct && sizeof struct|int
	struct st_one_item stn = {9};// init struct
	test_chg_num( &stn );
	printf("n=(%d) \n", stn.num );/* n=(10) */
	printf("sizeof(struct st_one_item):[%d] \n", sizeof(struct st_one_item));// sizeof(struct)
	printf("sizeof(int):[%d] \n", sizeof(int));				 // sizeof(int)

	// memcpy from type int to type struct
	int i2struct = 20;// [value] int => struct
	memcpy(&stn, &i2struct, sizeof(int) );
	printf("[MEMCPY int => struct] int=(%d), st.num=(%d) \n", i2struct, stn.num );

	// convert type int to type struct
	int t2struct = 9;
	int t2struct_before = t2struct;
	test_chg_num((struct st_one_item *)&t2struct);
	printf("[TYPE int => struct] int_before=(%d), int_after=(%d)  \n",t2struct_before, t2struct);

	return 0;
}

