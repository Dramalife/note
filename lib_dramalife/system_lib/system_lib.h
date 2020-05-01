#ifndef DRAMALIFE_LIB_SYSTEM_H
#define DRAMALIFE_LIB_SYSTEM_H

/* Headers */
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


/* System resources */
extern int dl_set_coredump_unlimit(void);

/* Program singleton run */
#define DL_SYS_SINGLETON_RUN_PID_PATH "/tmp"
#define dl_sys_check_singleton_ha(x)	dl_sys_check_singleton(__LINE__,x)
extern int dl_sys_check_singleton(int id_numa, int id_numb);


#endif
