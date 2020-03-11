/*
 * note "syslog" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu/Linaro 7.3.0-16ubuntu3) 7.3.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux Ubuntu18-BPI-R2 4.4.70-BPI-R2-Kernel #4 SMP Thu Mar 29 10:31:30 CST 2018 armv7l armv7l armv7l GNU/Linux
 * ;
 * 
 * Init : Wed Mar 11 14:42:54 CST 2020
 * 	Init;
 * Update
 *
 */



/* syslog header (syslog需要的头文件) */
#include <syslog.h>

#include <stdlib.h>// optional(可选，被exit函数需要)


/* Init variable - syslog 
 * (定义并初始化syslog需要用到的变量)
 */
int level = LOG_INFO;
int options = 0;

/* general print function - syslog 
 * (这是一个宏，使用方法和printf一样，为了提供一种方便的记录日志的方式)
 */
#define iec104_debug_out(f,...)	do{\
	syslog(LOG_USER | level, f, ##__VA_ARGS__);\
}while(0)

int main(int argc, char **argv)
{
	/* STEP-1
	 * Setting option & level - syslog 
	 * (options保持默认即可（这样会把进程的PID也记录到日志中）。)
	 * (level是日志等级，目前是DEBUG，可能需要调高（因为有时等级太低的日志不会被记录）。)
	 */
	options |= LOG_PID;
	//level = LOG_ALERT;  
	//level = LOG_CRIT;   
	//level = LOG_ERR;    
	//level = LOG_WARNING;
	//level = LOG_NOTICE; 
	//level = LOG_INFO;   
	level = LOG_DEBUG;  


	/* STEP-2
	 * Open log - syslog
	 * ARG0: Process name(第一个参数一般都是进程名，不需要修改)
	 */
	openlog(argv[0], options, LOG_USER);


	/* STEP-3
	 * Generates a log message - syslog
	 * Result:
	 * # cat /var/log/syslog | grep single_syslog.out
	 * Mar 11 14:48:48 Ubuntu18-BPI-R2 ./single_syslog.out[2125]: This is an example message. , level=0x7,options=0x1.
	 * Mar 11 14:48:48 Ubuntu18-BPI-R2 ./single_syslog.out[2125]: This is an example message. From MACRO! , level=0x7,options=0x1.
	 *
	 * (下面的两个函数syslog和iec104_debug_out的效果是一样的，iec104_debug_out的用法和printf函数一样，可以直接替换。)
	 */
	syslog(LOG_USER | level, "%s, level=0x%x,options=0x%x. ", "This is an example message. ",level, options);
	/* printf like function - syslog */
	iec104_debug_out("%s, level=0x%x,options=0x%x. ", "This is an example message. From MACRO! ",level, options);


	/* STEP-4
	 * Close log - syslog */
	closelog();
	exit(0);
}
