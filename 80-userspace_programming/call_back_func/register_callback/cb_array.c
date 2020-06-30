/*
 * note "callback function" related file
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
 * Init : Tue Jun 30 15:33:56 CST 2020
 * 	Init ;
 * Update : Tue Jun 30 15:33:56 CST 2020
 *  
 * Update
 *
 */



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int my_func1(void *arg);
int my_func2(void *arg);

struct callback_st
{
	int flag; // 没有用到;
	int type; // 类型，收到什么类型的通知，调用什么类型的函数;
	int (*handle)(void*); // 函数指针的类型，返回值为int型，入参为void *;
};

/****
 * 自定义通知类型
 * 注册函数时指定类型，
 * 从上收到通知后，向下只调用对应类型的函数
 */
enum {
	NOTIFY_TYPE_SAMPLE = 6,
	NOTIFY_TYPE_SAMPLE_NEVER,
	NOTIFY_TYPE_MAX__,
};

struct callback_st callbk[]={
	// Add your func below
	{0, NOTIFY_TYPE_SAMPLE, my_func1},	// 示例1
	{0, NOTIFY_TYPE_SAMPLE_NEVER, my_func2}, // 示例2
	{0, NOTIFY_TYPE_SAMPLE, NULL},
};

void notify_callback(int type, struct callback_st sta[])
{
	int ret = -1;
	int index;
	for(index=0; ;index++)
	{
		if( NULL == sta[index].handle )
			break;
		if( type != sta[index].type )
			continue;

		ret = sta[index].handle(&index);
		printf("Call (%p), ret (%d)! \n", sta[index].handle, ret);
	}
}

// 其他人定义的函数1
int my_func1(void *arg)
{
	sleep(1);
	printf("Arg (%d)\n", *(int *)arg);
	return random()%9;
}
// 其他人定义的函数2
int my_func2(void *arg)
{
	sleep(1);
	printf("Arg (%d)\n", *(int *)arg);
	return random()%9;
}

int main(void)
{
	while(1)
	{
		/* 收到了通知，需要调用已经注册的函数 */
		if(1)
		{
			notify_callback(NOTIFY_TYPE_SAMPLE, callbk);
		}
	}

	return 0;
}

