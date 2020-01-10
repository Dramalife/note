#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memset
#include "ipc_lib_pipe.h"



/* 
 * FILE *popen(const char *command, const char *type);
 * int pclose(FILE *stream);
 */ 
int dramalife_get_cmd_result(const char *cmd, const char *type, char *output)
{
	FILE *fp;
	char *ptr = output;

	if(NULL == output)
		return -3;

	fp = popen(cmd, type);

	while( NULL != fgets(ptr, 32, fp) )
	{
		dlprintf("output(%s) \n",ptr);
		ptr += strlen(ptr);
	}

	return pclose(fp);
}
int dramalife_get_cmd_n_result(const char *cmd, const char *type, char *output, int length)
{
	FILE *fp;
	char *ptr = output;
#define DL_POPEN_FGETS_ONE_MAX_SIZE	64

	if(NULL == output)
		return -3;
	if(length < DL_POPEN_FGETS_ONE_MAX_SIZE)
		return -2;

	fp = popen(cmd, type);

	while( NULL != fgets(ptr, DL_POPEN_FGETS_ONE_MAX_SIZE, fp) )
	{
		dlprintf("output(%s) \n",ptr);
		ptr += strlen(ptr);
		length -= strlen(ptr);
		if(length < DL_POPEN_FGETS_ONE_MAX_SIZE)
			break;
	}

	return pclose(fp);
}

int dramalife_get_pipe_max_size(void)
{
	char *pipsize_p = (char *)malloc(256 * sizeof(char));
	int pipsize_i = 0;

	memset(pipsize_p, 0, 256);

	dramalife_get_cmd_result("cat /proc/sys/fs/pipe-max-size","r", pipsize_p);
	pipsize_i = atoi(pipsize_p);
	dlprintf("int_pipsize(%d) \n",pipsize_i);

	return pipsize_i;
}
