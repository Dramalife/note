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
 * Init : 2019.11.14
 * 	COPY FROM : 21cnbao/training/thread/deadlock.c
 * 	Author: Barry Song <21cnbao@gmail.com>
 * ;
 * Update : 2019.11.14
 *
 *
 */



#include<stdio.h>
#include<pthread.h>

#include "lib_dramalife.h"


#define DO_NOT_JOIN	1


void *run(void *arg) 
{
	MAKE_GCC_HAPPY(arg);
	pthread_exit(0);
}

int main (void) 
{
	pthread_t thread;
	int rc;
	long count = 0;
	while(1) {
		if( (rc = pthread_create(&thread, 0, run, 0)) ) {
			printf("ERROR, rc is %d, so far %ld threads created\n", rc, count);
			perror("Fail:");
			while(1)
				;
			return -1;
		}
		count++;

#if (0 == DO_NOT_JOIN)
		pthread_join(thread,NULL);
#endif

	}
	return 0;
}

