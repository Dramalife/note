/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   client
   Init	2019.08.11 COPY FROM /note/80-userspace_programming/com_unix_sock.
<<<<<<< HEAD
   Update 2019.08.14 rc_ubuntu_vbox_32.
   Update 2019.08.16 rc_ubuntu_vbox_32, supporting backtrace.
   Update
   
   errno is thread-local;
=======
<<<<<<< HEAD
   Update 
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
*/
#include "dlpi_common.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>/*malloc*/
#if DLPI_BACKTRACE
#include <signal.h>
#endif


#if DLPI_BACKTRACE
//#error 111
extern void signal_handler(int signo);
#endif


int conn_sock_server(struct sockaddr_un *server_addr , dlpi_sock_op *op);
void set_sockaddr(struct sockaddr_un * serv_addr_p, const char *spath, sa_family_t sfamily);
void report_error(const char *func, int line, int arg_errno, const char *usr_str);


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

int main(void)
{
#if DLPI_BACKTRACE
	signal(SIGSEGV, signal_handler);/* Segmentation fault. */
#endif

    int connect_fd = 0;
    char snd_buf[DLPI_SOCK_READ_BUF_LEN];
    memset(snd_buf,0,DLPI_SOCK_READ_BUF_LEN);

    /* Connect to socket server and return fd. */
    struct sockaddr_un serv_addr;
    set_sockaddr(&serv_addr, DLPI_UNIX_PROCESS_MAIN, AF_UNIX);
    connect_fd = conn_sock_server(&serv_addr , NULL);
    if(connect_fd <= 0)
    {
	    report_error(__func__,__LINE__,errno,"bad fd !");
    }

    /* Prepare data to be send. */
    dlpi_frame data_2send;
    memset(&data_2send,0,sizeof(dlpi_frame));
    data_2send.lll_type[0]=3;
    data_2send.data_len=8;
    memcpy(snd_buf,(const void *)&data_2send, DLPI_SOCK_READ_BUF_LEN);

    /* WRITE */
    write(connect_fd,snd_buf, DLPI_SOCK_READ_BUF_LEN);

<<<<<<< HEAD
    /* READ */
    while(1)
    {
    	int r_bytes = read(connect_fd,snd_buf, DLPI_SOCK_READ_BUF_LEN	);
=======
    for(i=0;i<4;i++)
        write(connect_fd,snd_buf,sizeof(snd_buf));
=======
   Update 2019.08.14 rc_ubuntu_vbox_32.
   Update 2019.08.16 rc_ubuntu_vbox_32, supporting backtrace.
   Update 2019.08.17 rpi_omv, split code to dlpi_common.c
   Update
   
   errno is thread-local;
*/
#include "dlpi_common.h"


#if DLPI_BACKTRACE
//#error 111
extern void signal_handler(int signo);
#endif


void set_dlpi_frame(dlpi_frame *framearg)
{

}

int main(void)
{
#if DLPI_BACKTRACE
	signal(SIGSEGV, signal_handler);/* Segmentation fault. */
#endif

    int connect_fd = 0;
    char send_buf[DLPI_SOCK_READ_BUF_LEN];
    memset(send_buf,0,DLPI_SOCK_READ_BUF_LEN);

    /* Connect to socket server and return fd. */
    struct sockaddr_un serv_addr;
    set_sockaddr(&serv_addr, DLPI_UNIX_PROCESS_MAIN, AF_UNIX);
    connect_fd = conn_sock_server(&serv_addr , NULL);
    if(connect_fd <= 0)
    {
	    report_error(__func__,__LINE__,errno,"bad fd !");
    }

    /* Prepare data to be send. */
    dlpi_frame data_2send;
    memset(&data_2send,0,sizeof(dlpi_frame));

    dlpi_set_frame_type((unsigned char *)&data_2send.forward_type, DLPI_FRAME_FT_SELF );
    dlpi_set_frame_type((unsigned char *)&data_2send.data_type, DLPI_FRAME_DT_STRING );

    char *cust = "188888889";

    data_2send.data_len = strlen(cust);

    memcpy(send_buf,(const void *)&data_2send, sizeof(data_2send));
    memcpy(send_buf + sizeof(data_2send) , cust, strlen(cust));

    /* WRITE */
    write(connect_fd,send_buf, DLPI_SOCK_READ_BUF_LEN);

    /* READ */
    while(1)
    {
    	int r_bytes = read(connect_fd,send_buf, DLPI_SOCK_READ_BUF_LEN	);
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
	if(r_bytes <= 0)
	{
		report_error(__func__,__LINE__,errno,"read fd !");
		break;
<<<<<<< HEAD
=======
		//continue;
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
	}
	else if(r_bytes <= sizeof(dlpi_frame))//TODO : ctl_struct_size
	{
		report_error(__func__,__LINE__,errno,"bytes read too short! ");
		break;
<<<<<<< HEAD
=======
		//continue;
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
	}
	else//DATA
	{
		if(0)//cmd err
		{
			report_error(__func__,__LINE__,errno,"CMD not respected!");
<<<<<<< HEAD
			break;
		}
	}
    }
=======
		}
		break;
	}
    }
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3

    close(connect_fd);
    return 0;
}

