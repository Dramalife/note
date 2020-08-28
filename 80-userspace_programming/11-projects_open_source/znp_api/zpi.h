/*
 * note "Zigbee - CC2530 ZNP API" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-99-generic #100-Ubuntu SMP Wed Apr 22 20:32:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Tue Aug 25 17:00:25 CST 2020
 *  * ;
 * Update : Tue Aug 25 17:00:25 CST 2020
 *  
 * Update
 *
 */



#ifndef _ZPI_H_
#define _ZPI_H_


#include <stdint.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <signal.h>

#include "librs232.h"

#include "uart_zpi.h"
#include "znp_api.h"

#define ZPI_SOCKET_PATH	"/tmp/.znp_api"

enum zpi_cmd_type{
	CMD_TYPE_POLL = 0,
	CMD_TYPE_SREQ,
	CMD_TYPE_AREQ,
	CMD_TYPE_SRSP,
	CMD_TYPE_MAX__,
};
enum zpi_cmd_sub{
	CMD_SUB_RPC_ERR = 0,
	CMD_SUB_SYS_IF,


	CMD_SUB_AF_IF = 4,
	CMD_SUB_ZDO_IF,
	CMD_SUB_SIMPLE,
	CMD_SUB_UTIL_IF,
	CMD_SUB_MAX__,
};
struct zpi_frame_general
{
	uint8_t len;
	uint8_t cmd[2];
	uint8_t data[0];
};
struct zpi_transport_uart
{
#define ZPI_FRAME_UART_SOF	0xfe
	uint8_t sof;
	struct zpi_frame_general gen;
	//uint8_t fcs;
};
struct zpi_frame_st
{
	struct zpi_transport_uart *fix;
	uint8_t fcs;
};



#endif

