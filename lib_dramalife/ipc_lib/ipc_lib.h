#ifndef DRAMALIFE_NOTE_LIB_IPC_LIB_H
#define DRAMALIFE_NOTE_LIB_IPC_LIB_H


/* PIPE */
#include "ipc_lib_pipe.h"

int dl_ipc_get_cmd_n_result(const char *cmd, const char *type, char *output, int length);

#endif
