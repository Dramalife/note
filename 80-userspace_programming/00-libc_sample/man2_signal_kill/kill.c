#include <sys/types.h>
#include <signal.h>

int main(int argc, char **argv)
{
	int pid = 0;
	int ret = 0;

	// top -d 1000 &
	// ps | grep top
	// ./a.out $(pidof top)
	if(argc == 2)
	{
		pid = atoi(argv[1]);
		ret = kill(pid, 9);
	}
	printf("pid(%d), ret(%d) \n",pid, ret);
	return 0;
}
