/*
 * github.com/dramalife/note.git
 * Author : Dramalife@live.com
 *
 * Learn about the O_APPEND flag of open().
 * Please write a program to append on file 
 * to another file with open() and lseek().
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{

	int fd_dest = -1;
	int fd_appd = -1;
	ssize_t n_read = -1;
	ssize_t n_write = -1;

	char buff[1024];
	memset(buff, 0, sizeof(buff));

	/* open src & des files */
	if( -1 == (fd_dest = open("./1.txt", O_RDWR  | O_APPEND)) || -1 == (fd_appd = open("./2.txt", O_RDWR )) )
	{
		perror("open");
		exit(1);
	}

	/* read src file */
	if( -1 == (n_read = read(fd_appd, buff, sizeof(buff))) )
	{
		perror("read");
		exit(1);
	}

	/* Offset "strlen(buff)" bytes */
	lseek(fd_dest, strlen(buff), SEEK_END);

	/* write des file */
	if( -1 == (n_write = write(fd_dest, buff, strlen(buff))) )
	{
		perror("write");
		exit(1);
	}

	return 0;
}

