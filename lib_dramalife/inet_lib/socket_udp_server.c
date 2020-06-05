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


#ifdef _DL_INET_LIB_ENABLE_

#define DO_NOT_CLOSE_UDP_SOCKET	1
int dl_destory_udp_socket(int sockfd)
{
#if 0 == DO_NOT_CLOSE_UDP_SOCKET
	close(sockfd);
#endif
}
int dl_init_udp_socket(char *bind_ip, int bind_port)
{
#if DO_NOT_CLOSE_UDP_SOCKET
	static int sockfd_static=0;
	static int func_run_once=0;
	if(func_run_once == 0)
	{
		func_run_once++;
#endif
		int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if(sock_fd < 0)
		{
			perror("socket");
			exit(1);
		}

		struct sockaddr_in addr_serv;
		memset(&addr_serv, 0, sizeof(struct sockaddr_in));
		addr_serv.sin_family = AF_INET;
		addr_serv.sin_port = htons(bind_port);
		//addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
		addr_serv.sin_addr.s_addr = inet_addr(bind_ip);

		if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
		{
			perror("bind error:");
			exit(1);
		}
		printf("family:%x(AF_INET=%x)\n", addr_serv.sin_family,AF_INET);
		sockfd_static = sock_fd;
		return sock_fd;
#if DO_NOT_CLOSE_UDP_SOCKET
	}
	else
	{
		return sockfd_static;
	}
#endif
}

int dl_udp_server_recv_msg(char *bind_ip, int bind_port, char *buff, int buff_len,  
		struct sockaddr_in *client_addr, int *addr_len)
{
	int recv_num;
	int sock_fd = dl_init_udp_socket(bind_ip, bind_port);

	/***
	 * If  src_addr  is  not  NULL, and the underlying protocol provides the source address of the message, that source
	 * address is placed in the buffer pointed to by src_addr.  In this  case,  addrlen  is  a  value-result  argument.
	 * Before  the  call,  it  should  be initialized to the size of the buffer associated with src_addr.  Upon return,
	 * addrlen is updated to contain the actual size of the source address.  The returned address is truncated  if  the
	 * buffer provided is too small; in this case, addrlen will return a value greater than was supplied to the call.
	 */
	*addr_len = sizeof(struct sockaddr);


	if( (recv_num = recvfrom(sock_fd, buff, buff_len, 0, 
					(struct sockaddr *)client_addr, (socklen_t *)addr_len)) < 0)
	{
		perror("recvfrom error:");
		exit(1);
	}
	//printf("[%s,%d] family:%x(AF_INET=%x),port:%d,addr:%s\n", __func__,__LINE__,
	//		client_addr->sin_family,AF_INET,
	//		client_addr->sin_port,
	//		inet_ntoa(client_addr->sin_addr.s_addr)?"11":"00"
	//      );

dl_destory_udp_socket(sock_fd);
	return recv_num;
}
int dl_udp_server_send_msg(char *bind_ip, int bind_port, char *buff, int buff_len,  
		struct sockaddr_in *client_addr, int *addr_len)
	//char *target_ip, int target_port, int *addr_len)
{
	int send_num;
	int sock_fd = dl_init_udp_socket(bind_ip, bind_port);

	*addr_len = sizeof(struct sockaddr);

	printf("[%s,%d] family:%x(AF_INET=%x)\n", __func__,__LINE__,client_addr->sin_family,AF_INET);
	send_num = sendto(sock_fd, buff, buff_len, 0, (struct sockaddr *)client_addr, (int)*addr_len);

	if(send_num < 0)
	{
		perror("sendto error:");
		exit(1);
	}

dl_destory_udp_socket(sock_fd);
	return send_num;
}
#endif /* _DL_INET_LIB_ENABLE_ */


#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main()
{
	int addr_len;
	char send_buf[20] = "i am server!";
	char recv_buf[20];
	struct sockaddr_in addr_client;
	int trans_cnt = 0;

	printf("server wait:\n");

	while(1)
	{
		trans_cnt = dl_udp_server_recv_msg("127.0.3.1", 6666, recv_buf, sizeof(recv_buf), &addr_client, &addr_len);
		recv_buf[trans_cnt] = '\0';
		printf("server recv %d bytes: %s\n", trans_cnt, recv_buf);

		sleep(1);
		trans_cnt = dl_udp_server_send_msg("127.0.3.1", 6666, send_buf, strlen(send_buf), &addr_client, &addr_len);
		printf("server send %d bytes: %s\n", trans_cnt, send_buf);
	}

	return 0;
}
#endif /* _DRAMALIFE_LIB_HAS_FUNC_MAIN_ */

