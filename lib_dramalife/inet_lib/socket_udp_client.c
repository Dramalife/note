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



#include "lib_dramalife.h"

/* Lib code */
#if _DL_INET_LIB_ENABLE_

#define DL_UDP_CLIENT_DO_NOT_CLOSE_SOCKET	1
void ld_udp_client_destory_sock(int fd)
{
#if 0 == DL_UDP_CLIENT_DO_NOT_CLOSE_SOCKET
	close(fd);
#endif
}
int dl_udp_client_init_sock(void)
{
	static int sock_fd;
#if DL_UDP_CLIENT_DO_NOT_CLOSE_SOCKET
	static int flag_once = 0;
	if( 0 == flag_once )
	{
		flag_once++;
#endif
		sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if(sock_fd < 0)
		{
			perror("socket");
			exit(1);
		}
#if DL_UDP_CLIENT_DO_NOT_CLOSE_SOCKET
	}
#endif
	return sock_fd;
}
int dl_udp_client_send_msg(struct sockaddr_in *des_addrin, char *buff, int buff_len)
{
	int len = sizeof(struct sockaddr_in);

	int sockfd = dl_udp_client_init_sock();

	int send_num = sendto(sockfd, buff, buff_len, 0, (struct sockaddr *)des_addrin, len);

	if(send_num < 0)
	{
		perror("sendto error:");
		exit(1);
	}

	ld_udp_client_destory_sock(sockfd);
}
int dl_udp_client_recv_msg(struct sockaddr_in *des_addrin, char *buff, int buff_len)
{
	int len = sizeof(struct sockaddr_in);

	int sockfd = dl_udp_client_init_sock();

	//int recv_num = recvfrom(sockfd, buff, buff_len, 0, (struct sockaddr *)des_addrin, (socklen_t *)&len);
	int recv_num = recvfrom(sockfd, buff, buff_len, 0, NULL, &len);

	if(recv_num < 0)
	{
		perror("recvfrom error:");
		exit(1);
	}

	ld_udp_client_destory_sock(sockfd);

	return recv_num;
}
#endif /* _DL_INET_LIB_ENABLE_ */


/* Main - demo */
#if _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main()
{
#define DEST_PORT 6666
#define DEST_IP_ADDRESS  "127.0.3.1"
	int recv_num;
	int send_num;
	char send_buf[20] = "hey, who are you?";
	char recv_buf[20];

	struct sockaddr_in addr_serv;
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDRESS);
	addr_serv.sin_port = htons(DEST_PORT);

	while(1)
	{
		sleep(1);

		send_num = dl_udp_client_send_msg(&addr_serv, send_buf, strlen(send_buf));
		printf("client send %d bytes: %s\n", send_num, send_buf);

		recv_num = dl_udp_client_recv_msg(&addr_serv, recv_buf, sizeof(recv_buf));
		printf("client recv %d bytes: %s\n", recv_num, recv_buf);
	}

	return 0;
}
#endif /* _DRAMALIFE_LIB_HAS_FUNC_MAIN_ */

