/*
 * note "NULL" related file
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
 * Init : Mon Jul 13 11:16:45 CST 2020
 * 	COPY FROM : tlpi/mmap/anon_mmap.c;
 * Update : Mon Jul 13 11:16:45 CST 2020
 * 	Remove dependence on "libtlpi.a";
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

/* Listing 49-3 */

/* anon_mmap.c

   Demonstrate how to share a region of mapped memory between a parent and
   child process without having to create a mapped file, either through the
   creation of an anonymous memory mapping or through the mapping of /dev/zero.
 */
//#define _BSD_SOURCE             /* Get MAP_ANONYMOUS definition */
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define errExit(x)	do{printf(x);exit(1);}while(0)

int main(int argc, char *argv[])
{
	int *addr;                  /* Pointer to shared memory region */

	/* Parent creates mapped region prior to calling fork() */

	/* Use MAP_ANONYMOUS */
	addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (addr == MAP_FAILED)
		errExit("mmap");


	*addr = 1;                  /* Initialize integer in mapped region */

	switch (fork()) {           /* Parent and child share mapping */
		case -1:
			errExit("fork");

		case 0:                     /* Child: increment shared integer and exit */
			printf("Child started, value = %d\n", *addr);
			(*addr)++;
			if (munmap(addr, sizeof(int)) == -1)
				errExit("munmap");
			exit(0);

		default:                    /* Parent: wait for child to terminate */
			if (wait(NULL) == -1)
				errExit("wait");
			printf("In parent, value = %d\n", *addr);
			if (munmap(addr, sizeof(int)) == -1)
				errExit("munmap");
			exit(0);
	}
}

