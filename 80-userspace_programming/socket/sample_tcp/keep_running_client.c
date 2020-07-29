/*
 * note "socket - TCP" related file
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
 * Init : Mon Jul 13 17:11:20 CST 2020
 * 	Add;
 *  
 * Update
 *
 */



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define MAXLINE 4096

/*****
 * Signal 
 * typedef void (*sighandler_t)(int);
 * sighandler_t signal(int signum, sighandler_t handler);
 */
#include <signal.h>
#define RESTART(f,x)    do{\
	dprintf(2, "(re)start socket!\n");\
	if( f != -1)\
	{\
		if( -1 == close(f) )\
		{\
			perror("close!");\
		}\
	}\
	sleep(x);\
	goto start_sock;\
}while(0)

void handler_sigpipe(int signo)
{
	dprintf(2, "Receive signal (%d), Ignore! \n", signo);
	return;
}


int main(int argc, char** argv){
	int   sockfd, n;
	char  recvline[4096], sendline[4096];
	struct sockaddr_in  servaddr;

	if( argc != 3 && argc != 4){
		printf("usage: ./client <ipaddress> <port> [message]\n");
		return 0;
	}

	if( SIG_ERR == signal(SIGPIPE, handler_sigpipe) )
	{
		perror("signal!!");
		return(2);
	}

start_sock:
	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
		RESTART(sockfd, 2);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		printf("inet_pton error for %s\n",argv[1]);
		return 0;
	}

	if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
		RESTART(sockfd, 2);
	}

	int already_run = 0;
	while(1)
	{
		if(argc == 3)
		{
			printf("send msg to server: \n");
			fgets(sendline, 4096, stdin);
		}
		else
		{
			sleep(1);
			if(!already_run)
			{
				already_run++;
				strncpy(sendline, argv[3], sizeof(sendline));
			}
		}

		if( send(sockfd, sendline, strlen(sendline), 0) < 0){
			printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
			RESTART(sockfd, 2);
		}
	}

	close(sockfd);
	return 0;
}
