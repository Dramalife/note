/*
 * note "network-ip-multicast" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 \
 *	UTC 2015 i686 i686 i686 GNU/Linux;
 * 
 * Init : 2019.11.28
 *	COPY FROM https://blog.csdn.net/qq_26600237/article/details/81036817 ;
 * Update : 2019.11.28
 *	Fix bug : comparison of unsigned expression < 0 is always false;
 * Update 
 *
 */



#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include "lib_dramalife.h"

#define BUFLEN 255

int main (int argc, char **argv)
{
	struct sockaddr_in peeraddr,ia;
	int sockfd;
	unsigned char loop;
	char recmsg[BUFLEN + 1];
	unsigned int socklen;
	int n;
	struct ip_mreq mreq;

	MAKE_GCC_HAPPY((void *)&argc);
	MAKE_GCC_HAPPY((void *)argv);

	/* 创建 socket 用于UDP通讯 */
	sockfd = socket (AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf ("socket creating err in udptalk\n");
		exit (1);
	}
	/* 设置要加入组播的地址 */
	bzero(&mreq, sizeof (struct ip_mreq));

	inet_pton(AF_INET,"224.0.1.2",&ia.sin_addr);
	/* 设置组地址 */
	bcopy (&ia.sin_addr.s_addr, &mreq.imr_multiaddr.s_addr, sizeof (struct in_addr));
	/* 设置发送组播消息的源主机的地址信息 */
	mreq.imr_interface.s_addr = htonl (INADDR_ANY);

	/* 把本机加入组播地址，即本机网卡作为组播成员，只有加入组才能收到组播消息 */

	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP , &mreq,sizeof (struct ip_mreq)) == -1)
	{
		perror ("setsockopt");
		exit (-1);
	}
	loop = 0; 
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop,sizeof (loop)) == -1)
	{
		printf("IP_MULTICAST_LOOP set fail!\n");
	}

	socklen = sizeof (struct sockaddr_in);
	memset (&peeraddr, 0, socklen);
	peeraddr.sin_family = AF_INET;
	peeraddr.sin_port = htons (7838);
	inet_pton(AF_INET, "224.0.1.2", &peeraddr.sin_addr); 

	/* 绑定自己的端口和IP信息到socket上 */
	if (bind(sockfd, (struct sockaddr *) &peeraddr,sizeof (struct sockaddr_in)) == -1)
	{
		printf ("Bind error\n");
		exit (0);
	}

	/* 循环接收网络上来的组播消息 */
	for (;;)
	{
		printf("Please input:\n");
		bzero (recmsg, BUFLEN + 1);
		if (fgets (recmsg, BUFLEN, stdin) == (char *) EOF)
			exit (0);

		if (sendto(sockfd, recmsg, strlen (recmsg), 0, (struct sockaddr *) &peeraddr, sizeof ( peeraddr)) < 0)
		{
			printf ("sendto error!\n");
			exit (3);
		}

		printf ("send ok\n");
		bzero (recmsg, BUFLEN + 1);
		n = recvfrom (sockfd, recmsg, BUFLEN, 0, (struct sockaddr *) &ia, &socklen);
		if (n < 0)
		{
			printf ("recvfrom err in udptalk!\n");
			exit (4);
		}
		else{
			/* 成功接收到数据报 */
			recmsg[n] = 0;
			printf ("recv:[%s]\n", recmsg);
		}
	}
}
