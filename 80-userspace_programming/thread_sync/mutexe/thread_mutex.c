/*
 * note "thread sync" related file
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
 * KEY WORDS : [gettid] [MACRO] [mutex];
 *
 * A sample access critical section with/without mutex ;
 *
 * Init : 2019.12.23
 *	COPY FROM : tlpi/thread/thread_incr.c ;
 * Update : 2019.12.23
 *	Replaced tlpi lib functions with libc functions;
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

/* Listing 30-1 */

/* thread_incr.c

   This program employs two POSIX threads that increment the same global
   variable, without using any synchronization method. As a consequence,
   updates are sometimes lost.

   See also thread_incr_mutex.c.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>//gettid()
#include <unistd.h>//syscall()
#include <sys/syscall.h>   /* For SYS_xxx definitions */
//#include "tlpi_hdr.h"


/* Added by Dramalife */
#define errExitEN(i,s)	do{printf("%s-%d \n",s,i);exit(0);}while(0)
#define PRINT_VAR_NAME_VAULE_INT(x)	do{printf("%-10s(%10d) \n",#x,x);}while(0)
#define EXIT_SUCCESS	0
#define T_S_NO_MUTEXE	0
#define T_S_HAS_MUTEX	1
/* Using mutex or not */
#ifndef THREAD_SYNC_DL_CONTROL
#define THREAD_SYNC_DL_CONTROL	T_S_HAS_MUTEX
#endif
#if 0 /* old macro for mutex controlling */
#define PTHREAD_MUTEX_CTL(x)	do{			\
	int (*func)(pthread_mutex_t *) = x;		\
	if( 0 != (s = func(&mtx)) )	\
		errExitEN(s,#x);	\
}while(0)
#else /* new ;-) */
#define PTHREAD_MUTEX_CTL(x)	do{			\
	if( 0 != (s = (x)(&mtx)) )	\
		errExitEN(s,#x);	\
}while(0)
#endif
//extern int pthread_mutex_lock(pthread_mutex_t *mutex);
//extern int pthread_mutex_unlock(pthread_mutex_t *mutex);
/* Added by Dramalife END */


static volatile int glob = 0;   /* "volatile" prevents compiler optimizations
                                   of arithmetic operations on 'glob' */
#if THREAD_SYNC_DL_CONTROL == T_S_HAS_MUTEX
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
#endif

static void *                   /* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int loc, j;
#if THREAD_SYNC_DL_CONTROL == T_S_HAS_MUTEX
    int s;
#endif
    //printf("[%s,%d] thread(%d) \n",__func__,__LINE__, gettid());		/* see man 2 gettid */
    printf("[%s,%d] thread(%ld) \n",__func__,__LINE__, syscall(__NR_gettid));

    for (j = 0; j < loops; j++) {
#if THREAD_SYNC_DL_CONTROL == T_S_HAS_MUTEX
	PTHREAD_MUTEX_CTL(pthread_mutex_lock);
#endif
        loc = glob;
        loc++;
        glob = loc;
#if THREAD_SYNC_DL_CONTROL == T_S_HAS_MUTEX
	PTHREAD_MUTEX_CTL(pthread_mutex_unlock);
#endif
    }

    printf("[%s,%d] thread(%ld) \n",__func__,__LINE__, syscall(__NR_gettid));
    return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;

    //loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;
    loops = (argc > 1) ? atoi(argv[1]) : 10000000;
    PRINT_VAR_NAME_VAULE_INT(loops);

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");

    if (0 != (s=pthread_join(t1, NULL)) )
        errExitEN(s, "pthread_join");
    if (0 != (s=pthread_join(t2, NULL)) )
        errExitEN(s, "pthread_join");

    PRINT_VAR_NAME_VAULE_INT(glob   );
    PRINT_VAR_NAME_VAULE_INT(loops*2);
    exit(EXIT_SUCCESS);
}
