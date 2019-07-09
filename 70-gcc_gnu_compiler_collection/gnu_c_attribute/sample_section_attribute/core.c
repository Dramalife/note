/*
   FILE : core.c

   note gcc attribute-section related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   COPY & MODIFY FROM:
   https://mp.weixin.qq.com/s?__biz=MzAwMDUwNDgxOA==&mid=2652663356&
   idx=1&sn=779762953029c0e0946c22ef2bb0b754&chksm=810f28a1b678a1b74
   7520ba3ee47c9ed2e8ccb89ac27075e2d069237c13974aa43537bff4fba&
   mpshare=1&scene=1&srcid=0111Ys4k5rkBto22dLokVT5A&pass_ticket=
   bGNWMdGEbb0307Tm%2Ba%2FzAKZjWKsImCYqUlDUYPZYkLgU061qPsHFESXlJj%
   2Fyx3VM#rd
*/


#include<stdio.h>
#include <terminal_color_dramalife.h>/* Installed from "note/lib_dramalife" */

#define AC_NONE         CNONE
#define AC_LRED         CLRED
#define AC_LGREEN       CLGREEN
#define AC_YELLOW       CYELLOW

typedef void (*INIT_CALL)(void);

/*
 * These two variables are defined in link script.
 */
extern INIT_CALL _init_start;
extern INIT_CALL _init_end;

void modules_init(void)
{
	INIT_CALL *init_ptr = &_init_start;
	for (; init_ptr < &_init_end; init_ptr++)
	{
#if  __WORDSIZE ==  64
		printf("[%4d],"AC_LGREEN"addr"AC_NONE":(0x%016llX)\n" ,
				__LINE__,(long long unsigned int)init_ptr);
#elif  __WORDSIZE ==  32
		printf("[%4d],"AC_LGREEN"addr"AC_NONE":(0x%08X)   \n" ,
				__LINE__,(unsigned int)init_ptr);
#endif
		(*init_ptr)();
	}
}

int main(void)
{
	modules_init();
	return 0;
}

