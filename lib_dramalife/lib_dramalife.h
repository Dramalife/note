/*
 * note "lib_dramalife" related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 *
 * $ uname -a
 * Linux server 4.15.0-66-generic #75-Ubuntu SMP Tue Oct 1 05:24:09 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : 2019.11.14;
 * Update : 2019.12.07
 *	Add "ipc_lib.h" ;
 * Update 
 *
 */
#ifndef LIB_DRAMALIFE_H
#define LIB_DRAMALIFE_H

#include <stdint.h>


/* Plat */
#if 	defined(__x86_64__)
#define	_DL_PLAT_X86_64_
#elif	defined(__ARM_ARCH_7A__)
#define	_DL_PLAT_ARM_V7A_
#elif	defined(__ARM_ARCH_8A)
#define	_DL_PLAT_ARM_V8A_
#else
#error NO PLAT INFO !
#endif

/*******************************************************************************
 * 			Configuration
 ******************************************************************************/
#include "config_lib_dramalife.h"


/*******************************************************************************
 * 			Library Functions
 ******************************************************************************/
#include "terminal_lib/terminal_lib.h"

#include "gcc_related_lib/gcc_related_show.h"

#include "libc_with_print_lib/libc_with_print_lib.h"

#include "link_list_lib/link_list.h"

#include "string_related_lib/string_related_lib.h"

#include "ipc_lib/ipc_lib.h"

#include "option_config_lib/option_config_lib.h"

#include "system_lib/system_lib.h"

#include "backtrace_lib/backtrace_lib.h"

#include "db_lib/db_lib.h"

#include "inet_lib/inet_lib.h"

#include "data_struct_lib/data_struct_lib.h"

#endif
