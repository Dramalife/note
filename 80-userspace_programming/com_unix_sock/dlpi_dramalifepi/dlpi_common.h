/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   Init	2019.08.11 Dramalife,ubuntu_64_lenovo.
<<<<<<< HEAD
   Update 2019.08.14 rc_ubuntu_vbox_32.
=======
<<<<<<< HEAD
   Update 
=======
   Update 2019.08.14 rc_ubuntu_vbox_32.
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
*/
#ifndef _DLPI_COMMON_H
#define _DLPI_COMMON_H

#define DLPI_UNIX_PROCESS_MAIN "/tmp/.dlpi_socket"

<<<<<<< HEAD
#define DLPI_SOCK_READ_BUF_LEN	10240 /* buffer length */

#define DLPI_BACKTRACE	0 /* USE : "make backtrace" */

typedef unsigned char u8_t;
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

=======
<<<<<<< HEAD
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
typedef struct dlpi_frame
{
#define DLPI_FRAME_MAX_SOCK_PATH_LEN	50
	char des_sock_path[DLPI_FRAME_MAX_SOCK_PATH_LEN];	//specific sock path
	u8_t mechine_specific_code[2];	// specific mechine, not useful yet.
	u8_t lll_type[2];	//(toDES|to_others|)
	u8_t data_struct_type[2];//16 bit.
	int data_len;
	//void *buffer;		//(trans_to_datastruct|trans_to_DES_level)
}dlpi_frame;

typedef struct dlpi_sock_conn_option_st
{
	int socket_op[3];/* int socket(int domain, int type, int protocol); */
}dlpi_sock_op;

#endif

=======
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
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
