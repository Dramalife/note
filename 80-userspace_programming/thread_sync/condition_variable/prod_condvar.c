/*
 * note "thread - condition variable" related file
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
 * Init : 2019.12.24
 *	COPY FROM : tlpi/threads/prod_condvar.c ;
 * Update : 2019.12.24
 *	Replace some functions with libc functions ;
 *	Replace some with macros;
 * Update 
 *
 */

/*************************************************************************\
 *                  Copyright (C) Michael Kerrisk, 2019.                   *
 *                                                                         *
 * This program is free software. You may use, modify, and redistribute it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation, either version 3 or (at your option) any      *
 * later version. This program is distributed without any warranty.  See   *
 * the file COPYING.gpl-v3 for details.                                    *
 \*************************************************************************/

/* Supplementary program for Chapter 30 */

/* prod_condvar.c

   A simple POSIX threads producer-consumer example using a condition variable.
 */
#include <time.h>
#include <pthread.h>
#include <stdlib.h>//exit()
#include <stdio.h>//printf()
#include <unistd.h>//sleep()
//#include "tlpi_hdr.h"

/* Added by Dramalife */
#define EXIT_SUCCESS	0
typedef enum 
{
	FALSE = 0,
	TRUE = 1,
}Boolean ;
#define errExitEN(i,s)	do{printf("%s \n",s);exit(i);}while(0)
#define CALL_FUNC_SAFELY(t,v,f)	do{	\
	t = (f)(&v);			\
	if (t != 0)			\
	errExitEN(t, #f);		\
}while(0)
#define USAGE()	do{						\
	printf(                                                 \
			"USAGE : \n"                            \
			"./a.out NUM1 NUM2 NUM3 ...\n"          \
			"NUM1 : Produce num of thread 1\n"     \
			"NUM2 : Produce num of thread 2\n"     \
			"NUM3 : Produce num of thread 3\n"     \
			);                                                \
}while(0)
/* Added by Dramalife END*/

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int avail = 0;

	static void *
threadFunc(void *arg)
{
	int cnt = atoi((char *) arg);
	int s, j;

	for (j = 0; j < cnt; j++)
	{
		sleep(1);

		/* Code to produce a unit omitted */

		CALL_FUNC_SAFELY(s, mtx, pthread_mutex_lock);

		avail++;        /* Let consumer know another unit is available */

		CALL_FUNC_SAFELY(s, mtx, pthread_mutex_unlock);

		CALL_FUNC_SAFELY(s, cond, pthread_cond_signal);
	}

	return NULL;
}

	int
main(int argc, char *argv[])
{
	pthread_t tid;
	int s, j;
	int totRequired;            /* Total number of units that all threads
				       will produce */
	int numConsumed;            /* Total units so far consumed */
	Boolean done;
	time_t t;

	t = time(NULL);
	USAGE();

	/* Create all threads */

	totRequired = 0;
	for (j = 1; j < argc; j++)
	{
		totRequired += atoi(argv[j]);

		s = pthread_create(&tid, NULL, threadFunc, argv[j]);
		if (s != 0)
			errExitEN(s, "pthread_create");
	}

	/* Loop to consume available units */

	numConsumed = 0;
	done = FALSE;

	for (;;) 
	{
		CALL_FUNC_SAFELY(s, mtx, pthread_mutex_lock);

		/* Wait for something to consume */
		while (avail == 0) 
		{
			s = pthread_cond_wait(&cond, &mtx);
			if (s != 0)
				errExitEN(s, "pthread_cond_wait");
		}
		printf("[%s,%d] \n",__func__,__LINE__);

		/* At this point, 'mtx' is locked... */

		/* Consume all available units */
		while (avail > 0) 
		{

			/* Do something with produced unit */

			numConsumed ++;
			avail--;
			printf("T=%ld: numConsumed=%d\n", (long) (time(NULL) - t),
					numConsumed);

			done = numConsumed >= totRequired;
		}

		CALL_FUNC_SAFELY(s, mtx, pthread_mutex_unlock);

		if (done)
			break;

		/* Perhaps do other work here that does not require mutex lock */
	}

	exit(EXIT_SUCCESS);
}
