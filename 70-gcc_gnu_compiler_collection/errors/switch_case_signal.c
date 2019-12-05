/*
 * note "error - switch_case && signal" related file
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
 * Init : 2019.12.05;
 * Update 
 *
 */

#include <signal.h>

int main(void)
{
	int signum;
	int j=0,k=0;
	int *cnt;

	/* $ gcc switch_case_signal.c
	 * switch_case_signal.c: In function ‘main’:
	 * switch_case_signal.c:44:4: error: case label does not reduce to an integer constant
	 *     case SIGRTMIN :
	 *     ^~~~
	 */
	 switch(signum)
	 {
	 	case SIGUSR1	:
	 		cnt = &j;
	 		break;
	 	case SIGRTMIN	:
	 		cnt = &k;
	 		break;
	 	default:
	 		break;
	 }
}
