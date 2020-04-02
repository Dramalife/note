#include "lib_dramalife.h"



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
		dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING,"output(%s) \n",ptr);
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
	{
		memset(output, 'A', length);
		*(output + length - 1) = '\0';
		dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_ERROR,"Buffer too small to start, memset to \'A\' !\n");
		return -2;
	}

	fp = popen(cmd, type);

	while( NULL != fgets(ptr, DL_POPEN_FGETS_ONE_MAX_SIZE, fp) )
	{
		dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING,"output(%s),strlen(%d) \n",ptr, (int)strlen(ptr));
		length -= strlen(ptr);
		ptr += strlen(ptr);
		if(length < DL_POPEN_FGETS_ONE_MAX_SIZE)
		{
			dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_ERROR,"No enough buffer space!\n");
			break;
		}
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
	dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING,"int_pipsize(%d) \n",pipsize_i);

	return pipsize_i;
}


#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(int argc, char **argv)
{
	MAKE_GCC_HAPPY(argc);
	MAKE_GCC_HAPPY(argv);
	return 0;
}
#endif
