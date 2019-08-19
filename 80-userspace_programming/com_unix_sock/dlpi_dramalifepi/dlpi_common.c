/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  Init : 2019.08.17
  Update
*/

#include <stdio.h>
#include "dlpi_common.h"


/*
FUNC : translate char val[2] to unsigned int, for debug print.
*/
unsigned int dlpi_get_frame_type(const unsigned char *valarg)
{
	if (NULL == valarg)
	{
		return 0;
	}
	else
	{
		return  valarg[0] | valarg[1]<<8;
	}
}
void dlpi_set_frame_type(unsigned char *valarg, const unsigned int typearg)
{
	if(NULL == valarg)
		return ;
	valarg[0] = typearg & 0xff;
	valarg[1] = (typearg>>8) & 0xff;
	return;
}


/**********************************************************
 * NAME:conn_sock_server;
 * FUNC:connect to socket server as a client;
 * INIT:2019.08.15;
 * UPDATE:
 * TODO : Support more connection options, by using ARG1(dlpi_sock_op *op);
 **********************************************************/
int conn_sock_server(struct sockaddr_un *server_addr , dlpi_sock_op *op)
{
	int connect_fd;
	int ret;

	struct stat stat_buf;

	printf("sockfile:%s, \n", server_addr->sun_path);

	ret = stat(server_addr->sun_path, &stat_buf);

	if(ret < 0)
	{
		report_error(__func__,__LINE__,errno,"get file type err");
	}

	if( !S_ISSOCK(stat_buf.st_mode)
			|| 0
	  )
	{
		report_error(__func__,__LINE__,errno,"file is not in sock type");
	}

	connect_fd = socket(PF_UNIX,SOCK_STREAM,0);
	if(connect_fd<0){
		report_error(__func__,__LINE__,errno,"get sock fd err");
		return -1;
	}

	ret = connect(connect_fd, (struct sockaddr*)server_addr, sizeof(*server_addr));
	if(ret==-1){
		report_error(__func__,__LINE__,errno,"connect to server failed! ");
		close(connect_fd);

		return -1;
	}//^FD
	return connect_fd;
}

void report_error(const char *func, int line, int arg_errno, const char *usr_str)
{
	if(arg_errno > 0)
		printf("[%s+%d] err(%4d):%s;%s. \n",func?func:"FUNC", line, arg_errno, strerror(arg_errno) ? strerror(arg_errno) : "NULL" ,
				usr_str?usr_str:"USR_STR_NULL");
	else
		printf("[%s+%d] noerr(%4d):%s;%s. \n",func?func:"FUNC", line, arg_errno, strerror(arg_errno) ? strerror(arg_errno) : "NULL" ,
				usr_str?usr_str:"USR_STR_NULL");

	return;
}

void set_sockaddr(struct sockaddr_un * serv_addr_p, const char *spath, sa_family_t sfamily)
{
//    struct sockaddr_un *serv_addr_p = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
    if(NULL == serv_addr_p)
    {
	report_error(__func__,__LINE__,errno,"null pointer");
    	return ;
    }
    memset(serv_addr_p, 0, sizeof(struct sockaddr_un));
    serv_addr_p->sun_family = sfamily;
    strcpy(serv_addr_p->sun_path, spath);
    return ;
}
