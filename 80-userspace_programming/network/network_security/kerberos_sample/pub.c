/*
 * note "kerberos" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu/Linaro 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.;
 * 
 * $ uname -a
 * Linux Ubuntu18-BPI-R2 4.4.70-BPI-R2-Kernel #4 SMP Thu Mar 29 10:31:30 CST 2018 armv7l armv7l armv7l GNU/Linux
 * ;
 * 
 * Init : Sat Apr 16 01:12:50 CST 2020
 * 	Socket communication;
 * Update : Sat Apr 18 01:00:50 CST 2020
 *	Data struct of kerberos protocol;
 *  
 * Update
 *
 */



#include "pub.h"

int key_m[K_MAX__]={0};

/*
 * socket
 * bind
 * listen
 */
int init_socket_server(int port_num)
{
	int fd_sock_s = -1;
	struct sockaddr_in addr_self_s; 

	if( -1 == (fd_sock_s = socket(AF_INET,SOCK_STREAM,0)) )
	{
		debug_out(__FILE__,__func__,__LINE__,"socket create failed! (%s) \n", strerror(errno));
		return -1;
	}

	memset(&addr_self_s, 0, sizeof(struct sockaddr_in));
	addr_self_s.sin_family = AF_INET;	//IPv4
	addr_self_s.sin_addr.s_addr = inet_addr("0.0.0.0");// peer all
	addr_self_s.sin_port = htons(port_num);	// PORT

	if( -1 == bind(fd_sock_s,(struct sockaddr *)&addr_self_s,sizeof(addr_self_s)) )
	{
		debug_out(__FILE__,__func__,__LINE__,"bind error! (%s) \n", strerror(errno));
		return -1;
	}

	if( -1 == listen(fd_sock_s, 10))
	{
		debug_out(__FILE__,__func__,__LINE__,"listen error! (%s) \n", strerror(errno));
		return -1;
	}

	return fd_sock_s;
}

int trans_data_func(struct trans_data_s_st arg)
{
	int accept_fd = -1;
	struct sockaddr addr_client;
	socklen_t accept_len = 0;
	char recv_msg[MESSAGE_SIZE];
	char send_msg[MESSAGE_SIZE];
	struct message_txrx_st msg_s={ {sizeof(send_msg), send_msg}, {sizeof(recv_msg), recv_msg} };

	memset(&addr_client, 0, sizeof(struct sockaddr));
	memset(recv_msg, 0, sizeof(recv_msg));
	memset(send_msg, 0, sizeof(send_msg));

	if( -1 == (accept_fd = accept(arg.sockfd, (struct sockaddr*)&addr_client, &accept_len)) )
	{
		debug_out(__FILE__,__func__,__LINE__,"accept error! (%s)\n", strerror(errno));
		sleep(1);
		return -1;
	}

	if( -1 == recv(accept_fd, msg_s.recv.msg, msg_s.recv.len, 0))
	{
		debug_out(__FILE__,__func__,__LINE__,"recv error! (%s)\n", strerror(errno));
	}

	if( NULL != arg.process_data )
		arg.process_data(msg_s);

	if( -1 == send(accept_fd, msg_s.send.msg, msg_s.send.len, 0) )
	{
		debug_out(__FILE__,__func__,__LINE__,"send error! (%s)\n", strerror(errno));
	}
	return 0;
}


/*
 * socket
 * connect
 */
int init_socket_client(struct sockaddr_in *addr_server)
{
	int sock_fd = -1;

	if( -1 == (sock_fd = socket(AF_INET,SOCK_STREAM,0)) )
	{
		//debug_out(__FILE__,__func__,__LINE__,"socket create failed! (%s) \n", strerror(errno));
		return -1;
	}

	while( -1 == connect(sock_fd,(struct sockaddr*)addr_server,sizeof(struct sockaddr_in)) )
	{
		//debug_out(__FILE__,__func__,__LINE__,"connect error! (%s) \n", strerror(errno));
		return -1;
	}
	return sock_fd; 
}
int send_message2sockserver(struct trans_data_c_st conn)
{
	int sock_fd = -1;
	struct sockaddr_in addr_server;

	struct message_t msg_space;
	struct message_txrx_st msg_txrx = { {sizeof(msg_space.send_msg),msg_space.send_msg},{sizeof(msg_space.recv_msg),msg_space.recv_msg}, -1 };

	memset(&msg_space, 0, sizeof(msg_space));
	memset(&addr_server, 0, sizeof(struct sockaddr_in));

	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(conn.port);// PORT-Server
	addr_server.sin_addr.s_addr = inet_addr(conn.addr);// IP-Server

	if(conn.process_data)
	{
		msg_txrx.trans_type = TRANS_SEND;
		conn.process_data(msg_txrx);
	}

	while(-1 == (sock_fd = init_socket_client(&addr_server)) )
	{
		//debug_out(__FILE__,__func__,__LINE__,"Init client socket failed! (%s) \n", strerr(errno));
		return -1;
	}

	if( -1 == send(sock_fd, msg_txrx.send.msg, MESSAGE_SIZE, 0) )
		debug_out(__FILE__,__func__,__LINE__,"Send error! (%s) \n", strerror(errno));

	if( -1 == recv(sock_fd, msg_txrx.recv.msg, MESSAGE_SIZE, 0) )
		debug_out(__FILE__,__func__,__LINE__,"Recv error! (%s) \n", strerror(errno));

	if(conn.process_data)
	{
		msg_txrx.trans_type = TRANS_RECV;
		conn.process_data(msg_txrx);
	}

	close(sock_fd);
	return 0;
}

int isalpha_usr(char arg)
{
	return ( ((arg >= 'A')&&(arg <= 'Z')) || ((arg >= 'a')&&(arg <= 'z')) ) ? 1 : 0 ;
}
int isdigit_usr(char arg)
{
	return ((arg >= '0')&&(arg <= '0')) ? 1 : 0 ;
}
int isalpha_lower(char arg)
{
	return ((arg >= 'a')&&(arg <= 'z')) ? 1 : 0 ;
}
int isalpha_upper(char arg)
{
	return ((arg >= 'A')&&(arg <= 'Z')) ? 1 : 0 ;
}


char *encode_usr(int key, char *plain, char *cipher)
{
	int index = 0;
	int offset = key % 26;

	for(index = 0; index < strlen(plain); index++)
	{
		char c = plain[index];
		if(isalpha_lower(c))
		{
			c = 'a' + ((c - 'a' + offset) % 26);
		}
		else if(isalpha_upper(c))
		{
			c = 'A' + ((c - 'A' + offset) % 26);
		}
		else if(isdigit_usr(c))
		{
			c = '0' + ((c - '0' + offset) % 10);
		}

		strcat(cipher, &c);
	}
	return cipher;
}


char *decode_usr(int key, char *cipher, char *plain)
{
	int index = 0;
	int offset = key % 26;

	for(index = 0; index < strlen(plain); index++)
	{
		char c = plain[index];
		if(isalpha_lower(c))
		{
			c = 'z' - (('z' - c + offset) % 26);
		}
		else if(isalpha_upper(c))
		{
			c = 'Z' - (('Z' - c + offset) % 26);
		}
		else if(isdigit_usr(c))
		{
			c = '9' - (('9' - c + offset) % 10);
		}

		strcat(cipher, &c);
	}
	return plain;
}

int gen_key()
{
	srand((unsigned)time(NULL));
	return (rand()%9000+1000);
}

int get_as_key(int index)
{
	return key_m[index];
}
