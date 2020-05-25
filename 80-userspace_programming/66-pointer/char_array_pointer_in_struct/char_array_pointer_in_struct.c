/*
 * note "struct { array/pointer }" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-99-generic #100-Ubuntu SMP Wed Apr 22 20:32:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Mon May 25 17:47:22 CST 2020
 *  * ;
 * Update : Mon May 25 17:47:22 CST 2020
 *  
 * Update
 *
 */



struct char_pointer_st
{
	int id;
	char *name
};
struct char_array_st
{
	int id;
	char name[];
};


#define TEST_FUNC(ptr, tsize, i, n)	do{\
	memset(buff, 0, sizeof(buff));\
	ptr = buff;\
	ptr->id = i;\
	strncpy(ptr->name, n, sizeof(buff)- tsize);\
	printf("id:%d,name:%s\n",ptr->id,ptr->name);\
}while(0)


int main(void)
{
	char buff[64];
	struct char_array_st *ca;
	struct char_pointer_st *cp;

	printf("array of struct\n");
	TEST_FUNC(ca, sizeof(struct char_array_st), __LINE__, __func__);
	printf("pointer of struct (SIGSEGV)\n");
	TEST_FUNC(cp, sizeof(struct char_pointer_st), __LINE__, __func__);
}

