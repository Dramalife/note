#ifndef _DL_LIB_TERMINAL_LIB_H_
#define _DL_LIB_TERMINAL_LIB_H_

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "dramalife_terminal_color.h"

char *dl_terminal_get_password(char *buff);

#endif
