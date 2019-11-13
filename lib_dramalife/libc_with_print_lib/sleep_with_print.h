#ifndef DL_SLEEP_WITH_PRINT_H
#define DL_SLEEP_WITH_PRINT_H

#include <time.h>
#include "terminal_color_dramalife.h"

#define PRINT_sleep_f1	1
#define PRINT_time	1
#define sleep_func_line_file(time)		sleep_f1(__func__,__LINE__,__FILE__,time)
#define sleep_m2(mfunc,mline,mfile,mstr)	sleep_f2(__func__,__LINE__,__FILE__,mfunc,mline,mfile,mstr)

extern void sleep_f1(const char *func_m, int line_m, const char *file_m, unsigned int time);

#endif
