/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   Init	2019.08.11 Dramalife,ubuntu_64_lenovo.
   Update 2019.08.14 rc_ubuntu_vbox_32.
*/
#ifndef _DLPI_COMMON_H
#define _DLPI_COMMON_H

#define DLPI_UNIX_PROCESS_MAIN "/tmp/.dlpi_socket"

#define DLPI_SOCK_READ_BUF_LEN	10240 /* buffer length */

#define DLPI_BACKTRACE	0 /* USE : "make backtrace" */



#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>/*malloc*/
#include <limits.h>/*SSIZE_MAX*/
#if DLPI_BACKTRACE
#include <signal.h>
#endif

typedef unsigned char u8_dlpit;
typedef int (*func_cvi)(char *,void *,int *);

struct ctl_dlpi
{
	int cmd_type;
	char *data;
};

struct code2func
{
	int no;
	func_cvi func;
};

typedef struct dlpi_frame
{
#define DLPI_FRAME_MAX_SOCK_PATH_LEN	50
	char des_sock_path[DLPI_FRAME_MAX_SOCK_PATH_LEN];	//specific sock path
	u8_dlpit des_mechine_code[2];	// specific mechine, not useful yet.

	u8_dlpit forward_type[2];	//(toDES|to_others|)
#define DLPI_FRAME_FT_SELF	0x0001

	u8_dlpit data_type[2];//ex. strint,struct xxx ,
#define DLPI_FRAME_DT_STRING	0x8000

	int data_len;
	//void *buffer;		//(trans_to_datastruct|trans_to_DES_level)
}dlpi_frame;

typedef struct dlpi_sock_conn_option_st
{
	int socket_op[3];/* int socket(int domain, int type, int protocol); */
}dlpi_sock_op;


unsigned int dlpi_get_frame_type(const unsigned char *valarg);
void dlpi_set_frame_type(unsigned char *valarg, const unsigned int typearg);

int conn_sock_server(struct sockaddr_un *server_addr , dlpi_sock_op *op);
void set_sockaddr(struct sockaddr_un * serv_addr_p, const char *spath, sa_family_t sfamily);
void report_error(const char *func, int line, int arg_errno, const char *usr_str);

#endif
