#include<stdio.h>
#include<stdlib.h>

//stop if reached BLOCK or LR
	void
main(void)
{
#define FILE_PATH "./test.txt"
	int fd;
	if( (fd = fopen(FILE_PATH, "r")) < 0 )
	{
		perror("haha");
		while(1)
		{
		}
	}

	lseek(fd, 0, SEEK_SET);

	int tmp=0;
	while ( fscanf(fd, "!!!%d", &tmp) )
	{
		printf("tmp:%d\n", tmp);
	}

	return;
}




/* fscanf
   RETURN VALUE
   These functions return the number of input items successfully matched and assigned, which can be fewer than provided for, or even zero in the event of an early match‐
   ing failure.
   The  value  E-O-F is returned if the end of input is reached before either the first successful conversion or a matching failure occurs.  E-O-F is also returned if a read
   error occurs, in which case the error indicator for the stream (see ferror(3)) is set, and errno is set indicate the error.
 */



