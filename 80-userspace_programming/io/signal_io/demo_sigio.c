/*
 * note "signal I/O" related file
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
 * Init : 2020.01.09 19:30
 *	COPY FROM : tlpi/altio/demo_sigio.c;
 * Update : 2020.01.09
 *	Add macro "DL_DO_NOT_USING_TLPI_LIB" for no lib_tlpi compiling ;
 * Update 
 *
 */
#define DL_DO_NOT_USING_TLPI_LIB	1
/* For compiling without using lib_tlpi, 2020.01.05 */
#ifdef DL_DO_NOT_USING_TLPI_LIB
#if (1 == DL_DO_NOT_USING_TLPI_LIB)
#define DO_NOT_USING_TLPI_LIB
#else
#undef	DO_NOT_USING_TLPI_LIB
#endif
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

/* Listing 63-3 */

/* demo_sigio.c

   A trivial example of the use of signal-driven I/O.
*/
#include <signal.h>
#include <ctype.h>
#include <fcntl.h>
#include <termios.h>

#ifdef DO_NOT_USING_TLPI_LIB
#include <stdlib.h>//for NULL
#else
#include "tty_functions.h"      /* Declaration of ttySetCbreak() */
#include "tlpi_hdr.h"
#endif

static volatile sig_atomic_t gotSigio = 0;
                                /* Set nonzero on receipt of SIGIO */

#ifdef DO_NOT_USING_TLPI_LIB
#define EXIT_SUCCESS 	0
#define EXIT_FAILURE 	1
#define errExit(x)	do{printf("%s \n",x);exit(EXIT_FAILURE);}while(0)
#define STDIN_FILENO	0
typedef enum { FALSE, TRUE } Boolean;
int ttySetCbreak(int fd, struct termios *prevTermios)
{
	struct termios t;

	if (tcgetattr(fd, &t) == -1)
		return -1;

	if (prevTermios != NULL)
		*prevTermios = t;

	t.c_lflag &= ~(ICANON | ECHO);
	t.c_lflag |= ISIG;

	t.c_iflag &= ~ICRNL;

	t.c_cc[VMIN] = 1;                   /* Character-at-a-time input */
	t.c_cc[VTIME] = 0;                  /* with blocking */

	if (tcsetattr(fd, TCSAFLUSH, &t) == -1)
		return -1;

	return 0;
}

#endif

static void
sigioHandler(int sig)
{
    gotSigio = 1;
}

int
main(int argc, char *argv[])
{
    int flags, j, cnt;
    struct termios origTermios;
    char ch;
    struct sigaction sa;
    Boolean done;

    /* Establish handler for "I/O possible" signal */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sigioHandler;
    if (sigaction(SIGIO, &sa, NULL) == -1)
        errExit("sigaction");

    /* Set owner process that is to receive "I/O possible" signal */

    if (fcntl(STDIN_FILENO, F_SETOWN, getpid()) == -1)
        errExit("fcntl(F_SETOWN)");

    /* Enable "I/O possible" signaling and make I/O nonblocking
       for file descriptor */

    flags = fcntl(STDIN_FILENO, F_GETFL);
    if (fcntl(STDIN_FILENO, F_SETFL, flags | O_ASYNC | O_NONBLOCK) == -1)
        errExit("fcntl(F_SETFL)");

    /* Place terminal in cbreak mode */

    if (ttySetCbreak(STDIN_FILENO, &origTermios) == -1)
        errExit("ttySetCbreak");

    for (done = FALSE, cnt = 0; !done ; cnt++) {
        for (j = 0; j < 100000000; j++)
            continue;                   /* Slow main loop down a little */

        if (gotSigio) {                 /* Is input available? */
            gotSigio = 0;

            /* Read all available input until error (probably EAGAIN)
               or EOF (not actually possible in cbreak mode) or a
               hash (#) character is read */

            while (read(STDIN_FILENO, &ch, 1) > 0 && !done) {
                printf("cnt=%d; read %c\n", cnt, ch);
                done = ch == '#';
            }
        }
    }

    /* Restore original terminal settings */

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermios) == -1)
        errExit("tcsetattr");
    exit(EXIT_SUCCESS);
}
