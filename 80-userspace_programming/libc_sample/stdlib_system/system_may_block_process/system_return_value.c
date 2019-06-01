#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"terminal_color_dramalife.h"

	int
main(int argc, char *argv[])
{
#ifdef CMD_MAX_LEN	
#error redef
#endif
#define CMD_MAX_LEN	100
	char *cmd = (char *)malloc( CMD_MAX_LEN * sizeof(char) );
	memset(cmd, 0, CMD_MAX_LEN);

	/*
	 * ret = WEXITSTATUS(0), success
	 * ret = WEXITSTATUS(1), failure
	 */
	sprintf(cmd,"busybox ping -I %s %s -c 1",argv[1], argv[2]);

	printf(CYAN"%s,%d "CNONE"\n",__func__, __LINE__);
	//strcpy(cmd, "./sla/a.out");

	int ret = system(cmd);
	printf("WEXITSTATUS(%X)\n", WEXITSTATUS(ret));
	free(cmd);

	printf(CYAN"done\n"CNONE);
	return 0;
}
