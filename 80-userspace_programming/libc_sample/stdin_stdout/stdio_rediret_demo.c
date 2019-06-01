#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;

	/* stdio rediret, start */
	fd = open("/dev/null", O_RDWR | O_NONBLOCK | O_NOCTTY);
	if (fd >= 0) { 
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	/* stdio rediret, end, Dramalife */

	printf("should not show");
}

