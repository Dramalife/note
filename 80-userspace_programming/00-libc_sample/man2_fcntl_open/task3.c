/*
 * github.com/dramalife/note.git
 * Author : Dramalife@live.com
 *
 * When using O_APPEND to open a file for 
 * reading and writing, can we read the file
 * from any location using lseek()? Can we 
 * update the data in any part of the file 
 * using lseek()? Please write a program to
 * verify your answer.
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

	int fd = -1;
	ssize_t n_write = -1;

	/* open file */
	if( -1 == (fd = open("./3.txt", O_RDWR ))  )
	{
		perror("open");
		exit(1);
	}

	/* Write from start , offset = 0 */
	lseek(fd, 0, SEEK_SET);
	if( -1 == (n_write = write(fd, "SET", strlen("SET"))) )
	{
		perror("write");
		exit(1);
	}
	/* Write from current , offset = 3 */
	lseek(fd, 3, SEEK_CUR);
	if( -1 == (n_write = write(fd, "CUR", strlen("CUR"))) )
	{
		perror("write");
		exit(1);
	}
	/* Write from end , offset = -1 */
	lseek(fd, -1, SEEK_END);
	if( -1 == (n_write = write(fd, "END", strlen("END"))) )
	{
		perror("write");
		exit(1);
	}

	return 0;
}

