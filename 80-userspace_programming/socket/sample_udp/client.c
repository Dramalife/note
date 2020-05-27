/*
 * note "socket - UDP" related file
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
 * Init : Wed May 27 11:07:20 CST 2020
 * 	COPY FROM : https://www.cnblogs.com/zkfopen/p/9382705.html;
 * Update : Wed May 27 11:07:20 CST 2020
 *  
 * Update
 *
 */



#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define DEST_PORT 8000
#define DSET_IP_ADDRESS  "127.0.0.1"


int main()
{
	int sock_fd;

	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr_serv;
	int len;
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);
	addr_serv.sin_port = htons(DEST_PORT);
	len = sizeof(addr_serv);


	int send_num;
	int recv_num;
	char send_buf[20] = "hey, who are you?";
	char recv_buf[20];

	printf("client send: %s\n", send_buf);

	send_num = sendto(sock_fd, send_buf, strlen(send_buf), 0, (struct sockaddr *)&addr_serv, len);

	if(send_num < 0)
	{
		perror("sendto error:");
		exit(1);
	}

	recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_serv, (socklen_t *)&len);

	if(recv_num < 0)
	{
		perror("recvfrom error:");
		exit(1);
	}

	recv_buf[recv_num] = '\0';
	printf("client receive %d bytes: %s\n", recv_num, recv_buf);

	close(sock_fd);

	return 0;
}

