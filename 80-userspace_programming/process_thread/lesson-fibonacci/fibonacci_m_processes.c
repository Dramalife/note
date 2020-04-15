#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>	/* fork */
#include <sys/wait.h>	/* wait */

int show_fibonacci(int num)
{
	int index = 0;
	int fib[1024];
	fib[0] = 0;
	fib[1] = 1;

	printf("No%-2d = %d\n", 0, fib[0]);
	printf("No%-2d = %d\n", 1, fib[1]);
	for(index = 2; index <=num; index++)
	{
		fib[index] = fib[index-1] + fib[index-2];
		printf("No%-2d = %d\n", index, fib[index]);
	}


	return 0;
}

int main(int argc, char **argv)
{
	int num = -1;
	int pid = -1;
	int child_status = -1;

	/* Check the number of parameters */
	if(argc != 2)
	{
		printf("Please input! \n");
		exit(1);
	}

	num = atoi(argv[1]);
	/* Check parameter validity */
	if(num < 0)
	{
		printf("Negative numbers are not allowed !\n");
		exit(2);
	}

	pid = fork();
	switch(pid)
	{
		case 0:
			printf("Now the child process starts to execute! \n");
			show_fibonacci(num-1);
			return 0;
			break;
		case -1:
			break;
		default:
			wait(&child_status);
			printf("The child process is finished, status(%d), now father process exit.\n", child_status);
			break;
	}

	return 0;
}
