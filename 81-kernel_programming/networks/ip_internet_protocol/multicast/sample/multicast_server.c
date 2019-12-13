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
#include "lib_dramalife.h"	/* MAKE_GCC_HAPPY */


/* Infile MACROS */
#define BUFLEN 255			/* Buffer length of data of socket message */
#define DEFAULT_MC_GRP "224.0.1.2"	/* Default IP multicast address of group */


int main (int argc, char **argv)
{
	int n;
	int sockfd;
	unsigned int socklen;
	unsigned char loop;
	char recmsg[BUFLEN + 1];

	/* In-function MACROS */
	#define OPT_AUTO_CONFIG	0x0	/* Default - just demo */
	int opt = OPT_AUTO_CONFIG;	
	int ttl = 64;			/* TTL - Time To Live */

	struct ip_mreq mreq;		/* Request struct for multicast socket ops */
	struct sockaddr_in peeraddr,ia;	/* Structure describing an Internet (IP) socket address. */

	MAKE_GCC_HAPPY((void *)&argc);
	MAKE_GCC_HAPPY((void *)argv);

	/* Create SOCKET - UDP */
	sockfd = socket (AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf ("socket creating err in udptalk\n");
		exit (1);
	}

	bzero(&mreq, sizeof (struct ip_mreq));

	/* Setting
	 * IP multicast address of group
	 *
	 */
	switch(argc)
	{
		case 3:
			opt = atoi(*(argv + 2));
		case 2:
			inet_pton(AF_INET,*(argv + 1),&ia.sin_addr);
			break;
		case 1:
			inet_pton(AF_INET,DEFAULT_MC_GRP,&ia.sin_addr);
			printf("Using default mc_addr ! \n"  "ARG1:MC_ADDR, ARG2:OPT \n");
			break;
		default:
			break;
	}

	/* Setting Request struct for multicast socket ops */
	bcopy (&ia.sin_addr.s_addr, &mreq.imr_multiaddr.s_addr, sizeof (struct in_addr));	/* Dest(Multicast) addr */
	mreq.imr_interface.s_addr = htonl (INADDR_ANY);						/* Source addr */

	/* IGMP - report */
	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP , &mreq,sizeof (struct ip_mreq)) == -1)
	{
		perror ("setsockopt");
		exit (-1);
	}

	/* IGMP - leave */
//	if (setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP , &mreq,sizeof (struct ip_mreq)) == -1)
//	{
//		perror ("setsockopt");
//		exit (-1);
//	}

	loop = 0; 
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop,sizeof (loop)) == -1)
	{
		printf("IP_MULTICAST_LOOP set fail!\n");
	}

	/* Setting - TTL */
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) == -1)
	{
		perror ("set TTL");
	}

	socklen = sizeof (struct sockaddr_in);
	memset (&peeraddr, 0, socklen);
	peeraddr.sin_family = AF_INET;
	peeraddr.sin_port = htons (7838);

	if(argc < 2)
		inet_pton(AF_INET, DEFAULT_MC_GRP, &peeraddr.sin_addr); 
	else
		inet_pton(AF_INET,(char *)(argv + 1),&peeraddr.sin_addr); 

	/* 绑定自己的端口和IP信息到socket上 */
	if (bind(sockfd, (struct sockaddr *) &peeraddr,sizeof (struct sockaddr_in)) == -1)
	{
		printf ("Bind error\n");
		exit (0);
	}

	/* 循环接收网络上来的组播消息 */
	for (;;)
	{
		if( OPT_AUTO_CONFIG == opt )
		{
			printf("Please input:\n");
			bzero (recmsg, BUFLEN + 1);
			if (fgets (recmsg, BUFLEN, stdin) == (char *) EOF)
				exit (0);
		}
		else
		{
			sleep(opt);
			strncpy(recmsg, "1234", 4);
			printf("sending ... \n");
		}

		if (sendto(sockfd, recmsg, strlen (recmsg), 0, (struct sockaddr *) &peeraddr, sizeof ( peeraddr)) < 0)
		{
			printf ("sendto error!\n");
			exit (3);
		}

		if( OPT_AUTO_CONFIG == opt )
		{
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
}
