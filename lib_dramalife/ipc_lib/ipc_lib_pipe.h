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
/* Debug print switch */
#ifndef DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_SW
#define DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_SW	0
#endif
/* Debug print core */
#ifndef DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_FUNC
#define DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_FUNC printf
#endif
/* Debug print function */
#define DL_IPC_PIPE_DEBUG_LEVEL_WARNING	1
#define DL_IPC_PIPE_DEBUG_LEVEL_ERROR	5
#define DL_IPC_PIPE_DEBUG_LEVEL_FATAL	8
#if (0 != DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_SW)
#define dlprintf(level,fmt,...)	do{						\
	if(level >= DRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_SW)			\
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
extern int dramalife_get_pipe_max_size(void);
extern int dramalife_get_cmd_result(const char *cmd, const char *type, char *output);
extern int dramalife_get_cmd_n_result(const char *cmd, const char *type, char *output, int length);
/* Set pipe size */
#define dramalife_macro_set_pipe_size(f, s)	do{	\
	if(s <= dramalife_get_pipe_max_size())		\
		fcntl(f, F_SETPIPE_SZ, s);		\
}while(0)//TODO : CAP_SYS_RESOURCE
/* Get pipe size */
#define dramalife_macro_get_pipe_size(f)	do{	\
	fcntl(f, F_GETPIPE_SZ);				\
}while(0)


#endif//End Of File
