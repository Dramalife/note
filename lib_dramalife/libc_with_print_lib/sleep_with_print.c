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

#include <time.h>
#include "sleep_with_print.h"

void sleep_f2(const char *func, int line,const char *file, const char *fn, int ln, const char *fl, const char *usr_str)
{
	printf(
			"[%12d]"//time
			CRED"%s"CNONE":"CGREEN"%d"CNONE":"CLRED"%s"CNONE
#if (1 == PRINT_sleep_f1)
			" call "
			CRED"%s"CNONE":"CGREEN"%d"CNONE":"CLRED"%s"CNONE
			" info(%s). \n"
#endif
			,(int)time(NULL)
			,fl,ln,fn
#if (1 == PRINT_sleep_f1)
			,file,line,func
			,usr_str
#endif
	      );
}
void sleep_f1(const char *func_m, int line_m, const char *file_m, unsigned int time)
{
	sleep_m2(func_m,line_m,file_m,"start");
	sleep(time);
	sleep_m2(func_m,line_m,file_m,"end");
}

