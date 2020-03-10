// Get prog_path & prog_name : https://blog.csdn.net/hzhsan/article/details/9293961

#include <sys/types.h>
#include <unistd.h>//readlink

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>

#define errExit(x)	do{printf(x);perror("");exit(1);}while(0)
#define DEFAULT_PROGRAM_NAME	"a.out"

int main(int argc, char *argv[])
{
	int istack = 222;
	printf("%s,%d \n",__func__,__LINE__);
	sleep(3);

	char buff_prog_path[256];
	char *ptr_prog_name;

	/* Default vaule */
	ptr_prog_name = DEFAULT_PROGRAM_NAME;

	/* Get prog_path
	 * Sample : exe:/home/dramalife/note/80-userspace_programming/00-libc_sample/man3_unistd_execlp/build/restart_process_fork_system.out
	 */
	readlink("/proc/self/exe", buff_prog_path, sizeof(buff_prog_path));

#if 1	// TODO : Another way getting prog_name ?
	/* Get prog_name
	 * Sample : /restart_process_fork_system.out
	 */
	if( NULL != (ptr_prog_name = strrchr(buff_prog_path, '/')) )
		ptr_prog_name++;
#endif

	printf("exe:%s \nname:%s \n",buff_prog_path, ptr_prog_name);

#if 1 // 1: vfork+execlp; 0: system;
	switch (vfork()) {
		case -1:
			errExit("vfork");

		case 0:             /* Child executes first, in parent's memory space */
			sleep(3);                   /* Even if we sleep for a while,
						       parent still is not scheduled */
			write(STDOUT_FILENO, "Child executing\n", 16);
			istack *= 3;                /* This change will be seen by parent */

#if 1 // 1: exec child process;  0: child process exit;
			if( -1 == execlp(buff_prog_path, ptr_prog_name, NULL))
			{
				printf("exec %s \n",strerror(errno));
				_exit(1);
			}
#else
			_exit(0);
#endif

		default:            /* Parent is blocked until child exits */
			write(STDOUT_FILENO, "Parent executing\n", 17);
			printf("istack=%d\n", istack);
			exit(0);
	}
#else
	system("./a.out &");
	exit(0);
#endif

}

