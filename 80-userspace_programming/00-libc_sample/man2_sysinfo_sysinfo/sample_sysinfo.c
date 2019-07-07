/*
   note sysinfo.h sysinfo() related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

//   man 2 sysinfo:
//   --------------
//   Since Linux 2.3.23 (i386), 2.3.48 (all architectures) the structure is:
//
//   struct sysinfo {
//	   long uptime;             /* Seconds since boot */
//	   unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
//	   unsigned long totalram;  /* Total usable main memory size */
//	   unsigned long freeram;   /* Available memory size */
//	   unsigned long sharedram; /* Amount of shared memory */
//	   unsigned long bufferram; /* Memory used by buffers */
//	   unsigned long totalswap; /* Total swap space size */
//	   unsigned long freeswap;  /* swap space still available */
//	   unsigned short procs;    /* Number of current processes */
//	   unsigned long totalhigh; /* Total high memory size */
//	   unsigned long freehigh;  /* Available high memory size */
//	   unsigned int mem_unit;   /* Memory unit size in bytes */
//	   char _f[20-2*sizeof(long)-sizeof(int)]; /* Padding to 64 bytes */
//   };

/*
 *NOTE : sysinfo()
 *----------------
 *This function is Linux-specific, and should not be used in programs intended to  be  porta‐
 *ble.
 */

#include <stdlib.h> /* malloc,free */
#include <stdio.h> /* printf */
#include <sys/sysinfo.h>


int main(void)
{
	struct sysinfo *info = (struct sysinfo *)malloc(sizeof(struct sysinfo));

	if(0 == sysinfo(info))
	{
		printf("freeram:%ld  \n",info->freeram);
	}

	free(info);
	return 0;
}

