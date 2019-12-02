/*
 * note "80 - singleton run" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 \
 * 	UTC 2015 i686 i686 i686 GNU/Linux;
 * 
 * REF-SRC : 
 * 	//来源：公众号【编程珠玑】
 * 	//博客：https://www.yanbinghu.com
 * 
 * REF : 
 *	man 2 fcntl - Advisory locking
 * 
 * Init : 2019.11.29
 *	COPY FROM "【编程珠玑】" ;
 * Update : 2019.11.29
 * Update :
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#define PROC_NAME "single_instance"
#define PID_FILE_PATH "/var/run/"


static int dl_set_lock(int fd, short type);
static int isRunning(const char *procname);


/*
 * RETURN VALUE (man 2 fcntl)
 * 	For a successful call, the return value depends on the operation:
 * 	
 * 	F_DUPFD  The new descriptor.
 * 	
 * 	F_GETFD  Value of file descriptor flags.
 * 	
 * 	F_GETFL  Value of file status flags.
 * 	
 * 	F_GETLEASE
 * 		 Type of lease held on file descriptor.
 * 	
 * 	F_GETOWN Value of descriptor owner.
 * 	
 * 	F_GETSIG Value of signal sent when read or write becomes possible, or zero for traditional SIGIO behavior.
 * 	
 * 	F_GETPIPE_SZ
 * 		 The pipe capacity.
 * 	
 * 	All other commands
 * 		 Zero.
 * 	
 * 	On error, -1 is returned, and errno is set appropriately.
 */
// #define DL_FCNTL_RET_VAULE_SUCCESS	0x1
// #define DL_FCNTL_RET_VAULE_ERROR	0x2
// int dl_fcntl_ret_value(int cmd, unsigned short ok_err)
// {
// #define	DL_FCNTL_RET_VAULE_SUPPORT_ALL_localused	0
// 	if(DL_FCNTL_RET_VAULE_ERROR == ok_err )
// 	{
// 		return -1;
// 	}
// #if (0 == DL_FCNTL_RET_VAULE_SUPPORT_ALL_localused)
// 	else if(0/****THE_FOLLOWING_IS_NOT_CURRENTLY_SUPPORTED****/
// 			|| cmd == F_DUPFD
// 			|| cmd == F_GETFD
// 			|| cmd == F_GETFL
// 			|| cmd == F_GETLEASE
// 			|| cmd == F_GETOWN
// 			|| cmd == F_GETSIG
// 			|| cmd == F_GETPIPE_SZ
// 	  )
// 	{
// 		return -1;
// 	}
// #endif
// 	else
// 	{
// 		switch (cmd)
// 		{
// #if (1 == DL_FCNTL_RET_VAULE_SUPPORT_ALL_localused) // The following is not currently supported ;-(
// 			case F_DUPFD :
// 				break;
// 			case F_GETFD :
// 				break;
// 			case F_GETFL :
// 				break;
// 			case F_GETLEASE :
// 				break;
// 			case F_GETOWN :
// 				break;
// 			case F_GETSIG :
// 				break;
// 			case F_GETPIPE_SZ :
// 				break;
// #endif
// 			default:
// 				return 0;
// 				break;
// 		}
// 	}
// }


/*锁文件还可以使用flock，目的是类似的。不过是它是BSD系统调用，并且某些版本不支持NFS，出于移植性考虑，使用fcntl*/
#if 0
struct flock
  {
    short int l_type;	/* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.	*/
    short int l_whence;	/* Where `l_start' is relative to (like `lseek').  */
#ifndef __USE_FILE_OFFSET64
    __off_t l_start;	/* Offset where the lock begins.  */
    __off_t l_len;	/* Size of the locked area; zero means until EOF.  */
#else
    __off64_t l_start;	/* Offset where the lock begins.  */
    __off64_t l_len;	/* Size of the locked area; zero means until EOF.  */
#endif
    __pid_t l_pid;	/* Process holding the lock.  */
  };
#endif
static int dl_set_lock(int fd, short type)
{
	if(/**************/type != F_RDLCK
			&& type != F_WRLCK
			&& type != F_UNLCK
	  )
	return -1;

	struct flock fl;
	fl.l_type   = type;	/* Type of lock: F_RDLCK,
				   F_WRLCK, F_UNLCK */
	fl.l_whence = SEEK_SET;	/* How to interpret l_start:
	     			   SEEK_SET, SEEK_CUR, SEEK_END */
	fl.l_start  = 0;	/* Starting offset for lock */
	fl.l_len    = 0;        /* Number of bytes to lock */
	fl.l_pid = -1;		/* PID of process blocking our lock
                                   (F_GETLK only) */

	return(fcntl(fd, F_SETLK, &fl));
}

int dl_simpleton_open_file(const char *path, const char *name)
{
	char filename[128] = {0};
	sprintf(filename, "%s%s.pid", path, name);

	return open(filename, O_CREAT|O_RDWR );
}
//#define dl_simpleton_open_file(p, n) do{char filename[128] = {0}; sprintf(filename, "%s%s.pid", path, name); return open(filename, O_CREAT|O_RDWR );}while(0)

static int isRunning(const char *procname)
{
	int fd;
	char buf[16] = {0};
	
	fd = dl_simpleton_open_file(PID_FILE_PATH, procname);

	if (fd < 0) {
		printf("open file failed!\n");
		return 1;
	}
	if (-1 == dl_set_lock(fd, F_WRLCK)) /*尝试加锁*/
	{                                                  
		printf("%s is already running\n", procname);
		close(fd);
		return 1;
	} 
	else 
	{
		ftruncate(fd, 0);/*截断文件，重新写入pid*/
		sprintf(buf, "%ld", (long)getpid());
		write(fd, buf, strlen(buf) + 1);
		close(fd);
		return 0;
	}
}

int main(void)
{
	/*判断是否已经有实例在运行*/
	if(isRunning(PROC_NAME))
	{
		exit(-1);
	}
	printf("run ok\n");
	//sleep(5);

	//dl_set_lock( dl_simpleton_open_file(PID_FILE_PATH, PROC_NAME), F_ULOCK );

	sleep(20);
	return 0;
}
