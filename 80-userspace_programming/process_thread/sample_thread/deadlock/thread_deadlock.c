/*
 * note "thread" related file
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
 * Linux server 4.15.0-66-generic #75-Ubuntu SMP Tue Oct 1 05:24:09 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 *
 * Init : 2019.11.13
 * 	COPY FROM : 21cnbao/training/thread/deadlock.c
 * 	Author: Barry Song <21cnbao@gmail.com>
 * ;
 * Update 
 *
 */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "libc_with_print_lib/sleep_with_print.h"

pthread_mutex_t mutex_1;
pthread_mutex_t mutex_2;

void *child1(void *arg)
{
	while(1){
		pthread_mutex_lock(&mutex_1);
		sleep_func_line_file(3);
		pthread_mutex_lock(&mutex_2);
		printf("%s get running \n",__func__);
		pthread_mutex_unlock(&mutex_2);
		pthread_mutex_unlock(&mutex_1);
		sleep_func_line_file(5);
	}
}

void *child2(void *arg)
{
	while(1){
		pthread_mutex_lock(&mutex_2);
		sleep_func_line_file(3);
		pthread_mutex_lock(&mutex_1);
		printf("%s get running \n",__func__);
		pthread_mutex_unlock(&mutex_1);
		pthread_mutex_unlock(&mutex_2);
		sleep_func_line_file(5);
	}
}

int main(void)
{
	int tid1,tid2;
	pthread_mutex_init(&mutex_1,NULL);
	pthread_mutex_init(&mutex_2,NULL);
	pthread_create(&tid1,NULL,child1,NULL);
	pthread_create(&tid2,NULL,child2,NULL);
	do{
		sleep_func_line_file(2);
	}while(1);
	pthread_exit(0);
}

