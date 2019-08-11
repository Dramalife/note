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
}

