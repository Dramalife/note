#include "lib_dramalife.h"


#ifdef _DL_IPC_LIB_ENABLE_
/* 
 * FILE *popen(const char *command, const char *type);
 * int pclose(FILE *stream);
 * TODO : OUTDATED & UNSAFE FUNCTION !!
 */ 
#if 0
int dl_ipc_get_cmd_result(const char *cmd, const char *type, char *output)
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
#endif
int dl_ipc_get_cmd_n_result(const char *cmd, const char *type, char *output, int length)
{
	FILE *fp;
	char *ptr = output;
#define DL_POPEN_FGETS_ONE_MAX_SIZE	16

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
			pclose(fp);
			return -4;
		}
	}

	return pclose(fp);
}

int dl_ipc_get_pipe_max_size(int *ret_size)
{
#define BUFF_SIZE_	256
	char *pipsize_p = (char *)malloc(BUFF_SIZE_ * sizeof(char));
	int pipsize_i = 0;

	memset(pipsize_p, 0, BUFF_SIZE_);

	if( 0 == dl_ipc_get_cmd_n_result("cat /proc/sys/fs/pipe-max-size","r", pipsize_p, BUFF_SIZE_) )
	{
		pipsize_i = atoi(pipsize_p);
		dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING,"pipe-max-size(%d) \n",pipsize_i);
		if(ret_size)
			*ret_size = pipsize_i;
	}

	return pipsize_i;
}
#endif



#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(int argc, char **argv)
{
	MAKE_GCC_HAPPY(argc);
	MAKE_GCC_HAPPY(argv);

#define BUFF_SIZE_	64
	char *buff = (char *)malloc(BUFF_SIZE_*sizeof(char));
	memset(buff, 0, BUFF_SIZE_);

	dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING, "[%s,%d] \n",__func__,__LINE__);
	int ret = dl_ipc_get_cmd_n_result("uname -a", "r", buff, BUFF_SIZE_);
	dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING, "[%s,%d] buff(%s), ret(%d).\n",__func__,__LINE__,buff,ret);

	// dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING, "[%s,%d] \n",__func__,__LINE__);
	// dl_ipc_get_cmd_result("uname -a", "r", buff);

	dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING, "[%s,%d] \n",__func__,__LINE__);
	int psize = dl_ipc_get_pipe_max_size(NULL);
	dlprintf(DL_IPC_PIPE_DEBUG_LEVEL_WARNING, "psize(%d) \n",psize);

	return 0;
}
#endif
