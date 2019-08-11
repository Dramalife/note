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
#if 0	/* Format transfer */
	int n = 9;
	test_chg_num((struct st_one_item *)&n);
	printf("n=(%d) \n", n);/* n=(10) */

#else	/* Normal way */
	struct st_one_item stn = {9};
	test_chg_num( &stn );
	printf("n=(%d) \n", stn.num );/* n=(10) */
#endif

	return 0;
}

