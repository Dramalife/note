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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define SERV_PORT   8000

int main()
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr_serv;
	int len;
	memset(&addr_serv, 0, sizeof(struct sockaddr_in));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_port = htons(SERV_PORT);
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(addr_serv);

	if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
	{
		perror("bind error:");
		exit(1);
	}

	int recv_num;
	int send_num;
	char send_buf[20] = "i am server!";
	char recv_buf[20];
	struct sockaddr_in addr_client;

	while(1)
	{
		printf("server wait:\n");

		recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);

		if(recv_num < 0)
		{
			perror("recvfrom error:");
			exit(1);
		}

		recv_buf[recv_num] = '\0';
		printf("server receive %d bytes: %s\n", recv_num, recv_buf);

		send_num = sendto(sock_fd, send_buf, recv_num, 0, (struct sockaddr *)&addr_client, len);

		if(send_num < 0)
		{
			perror("sendto error:");
			exit(1);
		}
	}

	close(sock_fd);

	return 0;
}

