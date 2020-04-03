#ifndef DRAMALIFE_NOTE_IPC_LIB_PIPE_H
#define DRAMALIFE_NOTE_IPC_LIB_PIPE_H


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****************************************
 **		CONFIGURATIONS		**
 *****************************************/
/* Debug print core */
#ifndef DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_FUNC
#define DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_FUNC printf
#endif
/* Debug print function */
#define DL_IPC_PIPE_DEBUG_LEVEL_WARNING	0x2
#define DL_IPC_PIPE_DEBUG_LEVEL_ERROR	0x4
#define DL_IPC_PIPE_DEBUG_LEVEL_FATAL	0x8
//
#ifdef _DLIPC_DEBUG_ENABLED_
#define dlprintf(level,fmt,...)	do{						\
	if(level >= _DLIPC_DEBUG_ENABLED_)			\
	{									\
		DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_FUNC(			\
				"[DL_LIB_IPC_PIPE-%d] ",level);			\
		DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_FUNC(fmt,##__VA_ARGS__);	\
	}									\
}while(0)
#else
#define dlprintf(level,fmt,...)
#endif


/*****************************************
 **		FUNCTIONS		**
 *****************************************/
/* Extern functions */
extern int dl_ipc_get_pipe_max_size(int *ret_size);
//extern int dl_ipc_get_cmd_result   (const char *cmd, const char *type, char *output);
extern int dl_ipc_get_cmd_n_result (const char *cmd, const char *type, char *output, int length);
#define dramalife_get_pipe_max_size	dl_ipc_get_pipe_max_size
//#define dramalife_get_cmd_result   	dl_ipc_get_cmd_result   
#define dramalife_get_cmd_n_result 	dl_ipc_get_cmd_n_result 
/* Set pipe size */
#define dl_ipc_macro_set_pipe_size(f, s)	do{	\
	if(s <= dl_ipc_get_pipe_max_size())		\
		fcntl(f, F_SETPIPE_SZ, s);		\
}while(0)//TODO : CAP_SYS_RESOURCE
/* Get pipe size */
#define dl_ipc_macro_get_pipe_size(f)	do{	\
	fcntl(f, F_GETPIPE_SZ);				\
}while(0)


#endif//End Of File
