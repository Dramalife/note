/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   server
   Init	2019.08.11 COPY FROM /note/80-userspace_programming/com_unix_sock.
<<<<<<< HEAD
   Update 
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "dlpi_common.h"

int main()
{

    socklen_t clt_addr_len;
    int socket;
    int com_fd;
    int ret;
    int i;
    static char recv_buf[1024];
    int len;
    struct sockaddr_un clt_addr;
    struct sockaddr_un srv_addr;

    socket=socket(PF_UNIX,SOCK_STREAM,0);
    if(socket<0){
        perror("cannot create listening socket");
        return 1;
    }

    srv_addr.sun_family=AF_UNIX;
    strncpy(srv_addr.sun_path,DLPI_UNIX_PROCESS_MAIN,sizeof(srv_addr.sun_path)-1);

    ret=bind(socket,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    if(ret==-1){
        perror("cannot bind server socket");
        close(socket);
        unlink(DLPI_UNIX_PROCESS_MAIN);
        return 1;

    }

    ret=listen(socket,1);
    if(ret==-1){
        perror("cannot listen the client connect request");
        close(socket);
        unlink(DLPI_UNIX_PROCESS_MAIN);
        return 1;

    }

    len=sizeof(clt_addr);
    com_fd=accept(socket,(struct sockaddr*)&clt_addr,&len);
    if(com_fd<0){
        perror("cannot accept client connect request");
        close(socket);
        unlink(DLPI_UNIX_PROCESS_MAIN);

        return 1;
    }

    printf("\n=====info=====\n");
    for(i=0;i<4;i++){
        memset(recv_buf,0,1024);
        int num=read(com_fd,recv_buf,sizeof(recv_buf));
        printf("Message from client (%d)) :%s\n",num,recv_buf);
    }

    close(com_fd);
    close(socket);

    unlink(DLPI_UNIX_PROCESS_MAIN);

    return 0;
=======
   Update 2019.08.14 rc_ubuntu_vbox_32.
   Update 2019.08.17 rpi_omv, split code to dlpi_common.c
   Update 
 */
#include "dlpi_common.h"

#define DLPI_UNLINK_AT_START	1
#define DLPI_UMASK_MASK		0077

struct code2func c2f[] =
{
	[1] = {.no = 6, .func = NULL},
	[6] = {.no = 36, .func = NULL},
};

int main()
{
	int socket_fd;
	int com_fd;
	int ret;
	struct sockaddr_un serv_addr;
	mode_t old_mask;

	printf("%s:%ld, \n","SSIZE_MAX",SSIZE_MAX);

#if (1 == DLPI_UNLINK_AT_START  )
	/* Delete a name and possibly the file it refers to */
	unlink(DLPI_UNIX_PROCESS_MAIN);
#endif

	/* Set file mode creation mask */
	old_mask = umask(DLPI_UMASK_MASK);

	/* Create an endpoint for communication */
	socket_fd=socket(PF_UNIX,SOCK_STREAM,0);
	if(socket_fd<0){
		perror("cannot create listening socket_fd");
		return 1;
	}

	printf("%d,%d\n",c2f[1].no,c2f[6].no);

	memset(&serv_addr,0,sizeof(struct sockaddr_un));/* If it is necessary when using glibc ? */
	serv_addr.sun_family=AF_UNIX;
	strncpy(serv_addr.sun_path,DLPI_UNIX_PROCESS_MAIN,strlen(DLPI_UNIX_PROCESS_MAIN));

	ret=bind(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret==-1){
		perror("cannot bind server socket_fd");
		close(socket_fd);
#if (0 == DLPI_UNLINK_AT_START	)
		unlink(DLPI_UNIX_PROCESS_MAIN);
#endif
		return 1;

	}

	ret=listen(socket_fd,10);
	if(ret==-1){
		perror("cannot listen the client connect request");
		close(socket_fd);
#if (0 == DLPI_UNLINK_AT_START	)
		unlink(DLPI_UNIX_PROCESS_MAIN);
#endif
		return 1;

	}
	umask(old_mask);//^SOCKET

	struct sockaddr_un clnt_addr;
	memset(&clnt_addr,0,sizeof(struct sockaddr_un));/* If it is necessary when using glibc ? */

	socklen_t len;
	len = sizeof(clnt_addr);
	com_fd = accept(socket_fd, (struct sockaddr*)&clnt_addr, &len);
	if(com_fd < 0){
		perror("cannot accept client connect request");
		//close(socket_fd);
#if (0 == DLPI_UNLINK_AT_START	)
		unlink(DLPI_UNIX_PROCESS_MAIN);
#endif
		return 1;
	}//^ACCEPT

	printf("\n*****READ FROM CLIENT*****\n");

	static char recv_buf[DLPI_SOCK_READ_BUF_LEN];
	memset(recv_buf,0,DLPI_SOCK_READ_BUF_LEN );

	/*int num =*/ read(com_fd,recv_buf, DLPI_SOCK_READ_BUF_LEN);
	dlpi_frame *p_head = (dlpi_frame *)recv_buf;

	if(DLPI_FRAME_FT_SELF == dlpi_get_frame_type(p_head->forward_type))
	{
		printf("forward_t:%04X \n", dlpi_get_frame_type( p_head->forward_type ) );
		if(DLPI_FRAME_DT_STRING == dlpi_get_frame_type(p_head->data_type))
		{
			char *data2 = recv_buf + sizeof(dlpi_frame);
			printf("data_t:%04X,len:%d,data:[%s]\n", dlpi_get_frame_type(p_head->data_type), p_head->data_len, data2);
			dlpi_set_frame_type(p_head->data_type, 0x1234);
			printf("data_t:%04X,len:%d,data:[%s]\n", dlpi_get_frame_type(p_head->data_type), p_head->data_len, data2);
		}
		else
		{
			printf("data_t:%04X,len:%d.\n",dlpi_get_frame_type(p_head->data_type) ,p_head->data_len );

		}
		//TODO:wirte back.
	}
	else
	{
		printf("forward_t:%0x04X,TO FORWARD! \n", dlpi_get_frame_type( p_head->forward_type ) );
	}

	close(com_fd);
	close(socket_fd);

#if (0 == DLPI_UNLINK_AT_START	)
	unlink(DLPI_UNIX_PROCESS_MAIN);
#endif

	return 0;
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
}

