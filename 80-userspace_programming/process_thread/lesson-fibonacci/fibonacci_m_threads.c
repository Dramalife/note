#include <stdio.h>
#include <stdlib.h>

#include <pthread.h> /* pthread api */

int show_fibonacci(void *num_p)
{
	int index = 0;
	int fib[1024];
	int num = *((int *)num_p);	

	fib[0] = 0;
	fib[1] = 1;

	printf("No%-2d = %d\n", 0, fib[0]);
	printf("No%-2d = %d\n", 1, fib[1]);
	for(index = 2; index <=num; index++)
	{
		fib[index] = fib[index-1] + fib[index-2];
		printf("No%-2d = %d\n", index, fib[index]);
	}

	pthread_exit("66666");
}

int main(int argc, char **argv)
{
	int num = -1;
	void *child_status = NULL;

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

	pthread_t tid = -1;
	pthread_create(&tid, NULL, (void *)show_fibonacci, &num);

	printf("Waiting for thread... \n");
	pthread_join(tid, &child_status);
	printf("Thread done, status(%s)... \n", (char *)child_status);

	return 0;
}
