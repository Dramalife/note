/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   server
   Init	2019.08.11 COPY FROM /note/80-userspace_programming/com_unix_sock.
   Update 
 */
#include <stdio.h>
#include <sys/types.h>//umask,
#include <sys/stat.h>//umask
#include <sys/socket.h>
#include <sys/un.h>
#include "dlpi_common.h"

#define DLPI_SOCK_READ_BUF_LEN	10240

#define DLPI_UNLINK_AT_START	1
#define DLPI_UMASK_MASK		0077

struct code2func c2f[] =
{
	[1] = {.no = 6, .func = NULL},
	[6] = {.no = 36, .func = NULL},
};

int main()
{
	socklen_t clnt_addr_len;
	int socket_fd;
	int com_fd;
	int ret;
	int i;
	static char recv_buf[DLPI_SOCK_READ_BUF_LEN];
	int len;
	struct sockaddr_un clnt_addr;
	struct sockaddr_un serv_addr;
	mode_t old_mask;

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

	memset(&clnt_addr,0,sizeof(struct sockaddr_un));/* If it is necessary when using glibc ? */
	len=sizeof(clnt_addr);
	com_fd=accept(socket_fd,(struct sockaddr*)&clnt_addr,&len);
	if(com_fd<0){
		perror("cannot accept client connect request");
		//close(socket_fd);
#if (0 == DLPI_UNLINK_AT_START	)
		unlink(DLPI_UNIX_PROCESS_MAIN);
#endif
		return 1;
	}//^ACCEPT

	printf("\n*****READ FROM CLIENT*****\n");
	//for(i=0;i<4;i++){
	memset(recv_buf,0,DLPI_SOCK_READ_BUF_LEN );
	int num=read(com_fd,recv_buf, DLPI_SOCK_READ_BUF_LEN);
	//TODO:handler.
	//TODO:wirte back to.
	printf("LEN:%-4d,MSG:%s\n",num,recv_buf);
	//}
	//^READ

	close(com_fd);
	close(socket_fd);

#if (0 == DLPI_UNLINK_AT_START	)
	unlink(DLPI_UNIX_PROCESS_MAIN);
#endif

	return 0;
}

