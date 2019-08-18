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
   Update 
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "dlpi_common.h"

int main(void)
{
    int connect_fd;
    int ret;
    char snd_buf[1024];
    int i;

    static struct sockaddr_un srv_addr;

    connect_fd=socket(PF_UNIX,SOCK_STREAM,0);
    if(connect_fd<0){
        perror("cannot create communication socket");
        return 1;
    }

    srv_addr.sun_family=AF_UNIX;
    strcpy(srv_addr.sun_path,DLPI_UNIX_PROCESS_MAIN);

    ret=connect(connect_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    if(ret==-1){
        perror("cannot connect to the server");
        close(connect_fd);

        return 1;
    }


    memset(snd_buf,0,1024);
    strcpy(snd_buf,"message from client");

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
	if(r_bytes <= 0)
	{
		report_error(__func__,__LINE__,errno,"read fd !");
		break;
		//continue;
	}
	else if(r_bytes <= sizeof(dlpi_frame))//TODO : ctl_struct_size
	{
		report_error(__func__,__LINE__,errno,"bytes read too short! ");
		break;
		//continue;
	}
	else//DATA
	{
		if(0)//cmd err
		{
			report_error(__func__,__LINE__,errno,"CMD not respected!");
		}
		break;
	}
    }
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277

    close(connect_fd);
    return 0;
}

