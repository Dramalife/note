/*
 * note "daemon" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu/Linaro 7.3.0-16ubuntu3) 7.3.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux Ubuntu18-BPI-R2 4.4.70-BPI-R2-Kernel #4 SMP Thu Mar 29 10:31:30 CST 2018 armv7l armv7l armv7l GNU/Linux
 * ;
 * 
 * Init : Thu Feb 13 23:07:40 CST 2020
 * 	COPY FROM TLPI/daemon/* ;
 * Update : Thu Feb 13 23:07:40 CST 2020
 * 	Add warning info, replace "tlpi_hdr.h";
 *  
 * Update
 *
 */
#ifdef	DL_REPLACE_TLPI_HDR_H
//lib/get_num.h
#define GN_GT_0         02      /* Value must be > 0 */
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#else
#endif



/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter 37 */

/* test_become_daemon.c

   Test our becomeDaemon() function.
*/
#include "become_daemon.h"
#ifndef DL_REPLACE_TLPI_HDR_H
#include "tlpi_hdr.h"
#endif

int
main(int argc, char *argv[])
{
    printf("ps -C test_become_daemon.out -o \"pid ppid pgid sid tty command\"  \n");

    becomeDaemon(0);
    printf("%s,%d become daemon done!\n",__func__,__LINE__);//will not print

    /* Normally a daemon would live forever; we just sleep for a while */

    //sleep((argc > 1) ? getInt(argv[1], GN_GT_0, "sleep-time") : 20);
    sleep(10);
    printf("%s,%d sleep finished!\n",__func__,__LINE__);//will not print

    exit(EXIT_SUCCESS);
}
