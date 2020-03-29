#include "lib_dramalife.h"


void main(void)
{

pid_t pid = fork();

if(pid == 0)
{
	char *buff=(char *)malloc(1024*sizeof(char));
	memset(buff, 0, 1024);
	printf("************\n");
	dramalife_get_cmd_n_result("`gcc -print-prog-name=cc1` -v 2>&1","r",buff,1024);
	printf("%s \n",buff);
	printf("************\n");
	_exit(0);
}
else
{
wait(pid);
}

}
