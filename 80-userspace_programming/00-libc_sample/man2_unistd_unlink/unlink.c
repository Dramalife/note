#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	creat("./1.txt", S_IRWXU);
	sleep(5);
	remove("./1.txt");
	return 0;
}
