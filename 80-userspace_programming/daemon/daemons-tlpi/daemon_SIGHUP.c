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
 * Update : Thu Feb 14 22:39:xx CST 2020
 *	Replace functions : errExit();
 * Update
 *
 */
#ifdef	DL_REPLACE_TLPI_HDR_H
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//sleep
//
#define errExit(x)	exit(1);
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

/* Listing 37-3 */

/* daemon_SIGHUP.c

   Demonstrate the use of SIGHUP as a mechanism to tell a daemon to
   reread its configuration file and reopen its log file.

   In the version of this code printed in the book, logOpen(), logClose(),
   logMessage(), and readConfigFile() were omitted for brevity. The version
   of the code in this file is complete, and can be compiled and run.
*/
#include <sys/stat.h>
#include <signal.h>
#include "become_daemon.h"

#ifndef	DL_REPLACE_TLPI_HDR_H
#include "tlpi_hdr.h"
#endif

static const char *LOG_FILE = "/tmp/ds.log";
static const char *CONFIG_FILE = "/tmp/ds.conf";

#include <time.h>
#include <stdarg.h>

static FILE *logfp;                 /* Log file stream */

/* Write a message to the log file. Handle variable length argument
   lists, with an initial format string (like printf(3), but without
   a trailing newline). Precede each message with a timestamp. */

static void
logMessage(const char *format, ...)
{
    va_list argList;
    const char *TIMESTAMP_FMT = "%F %X";        /* = YYYY-MM-DD HH:MM:SS */
#define TS_BUF_SIZE sizeof("YYYY-MM-DD HH:MM:SS")       /* Includes '\0' */
    char timestamp[TS_BUF_SIZE];
    time_t t;
    struct tm *loc;

    t = time(NULL);
    loc = localtime(&t);
    if (loc == NULL ||
           strftime(timestamp, TS_BUF_SIZE, TIMESTAMP_FMT, loc) == 0)
        fprintf(logfp, "???Unknown time????: ");
    else
        fprintf(logfp, "%s: ", timestamp);

    va_start(argList, format);
    vfprintf(logfp, format, argList);
    fprintf(logfp, "\n");
    va_end(argList);
}

/* Open the log file 'logFilename' */

static void
logOpen(const char *logFilename)
{
    mode_t m;

    m = umask(077);
    logfp = fopen(logFilename, "a");
    umask(m);

    /* If opening the log fails we can't display a message... */

    if (logfp == NULL)
        exit(EXIT_FAILURE);

    setbuf(logfp, NULL);                    /* Disable stdio buffering */

    logMessage("Opened log file");
}

/* Close the log file */

static void
logClose(void)
{
    logMessage("Closing log file");
    fclose(logfp);
}

/* (Re)initialize from configuration file. In a real application
   we would of course have some daemon initialization parameters in
   this file. In this dummy version, we simply read a single line
   from the file and write it to the log. */

static void
readConfigFile(const char *configFilename)
{
    FILE *configfp;
#define SBUF_SIZE 100
    char str[SBUF_SIZE];

    configfp = fopen(configFilename, "r");
    if (configfp != NULL) {                 /* Ignore nonexistent file */
        if (fgets(str, SBUF_SIZE, configfp) == NULL)
            str[0] = '\0';
        else
            str[strlen(str) - 1] = '\0';    /* Strip trailing '\n' */
        logMessage("Read config file: %s", str);
        fclose(configfp);
    }
}

static volatile sig_atomic_t hupReceived = 0;
                        /* Set nonzero on receipt of SIGHUP */

static void
sighupHandler(int sig)
{
    hupReceived = 1;
}

int
main(int argc, char *argv[])
{
	printf("ps -C daemon_SIGHUP.out -o \"pid ppid pgid sid tty command\"  \n");
	printf("Log file:%s  \nConfig file:%s \n" ,LOG_FILE ,CONFIG_FILE );
	printf("Kill all : kill -9 $(pidof daemon_SIGHUP.out) \n");

    const int SLEEP_TIME = 15;      /* Time to sleep between messages */
    int count = 0;                  /* Number of completed SLEEP_TIME intervals */
    int unslept;                    /* Time remaining in sleep interval */
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sighupHandler;
    if (sigaction(SIGHUP, &sa, NULL) == -1)
        errExit("sigaction");

    if (becomeDaemon(0) == -1)
        errExit("becomeDaemon");

    logOpen(LOG_FILE);
    readConfigFile(CONFIG_FILE);

    unslept = SLEEP_TIME;

    for (;;) {
        unslept = sleep(unslept);       /* Returns > 0 if interrupted */

        if (hupReceived) {              /* If we got SIGHUP... */
            hupReceived = 0;            /* Get ready for next SIGHUP */
            logClose();
            logOpen(LOG_FILE);
            readConfigFile(CONFIG_FILE);
        }

        if (unslept == 0) {             /* On completed interval */
            count++;
            logMessage("Main: %d", count);
            unslept = SLEEP_TIME;       /* Reset interval */
        }
    }
}
