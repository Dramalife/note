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

int trans_data_func(struct trans_data_st arg)
{
	int accept_fd = -1;
	////////
	struct sockaddr addr_client;
	socklen_t accept_len = 0;
	memset(&addr_client, 0, sizeof(struct sockaddr));
	//
	char recv_msg[MESSAGE_SIZE];
	char send_msg[MESSAGE_SIZE];
	memset(recv_msg, 0, sizeof(recv_msg));
	memset(send_msg, 0, sizeof(send_msg));
	//////
	struct message_server_st msg_s={ {sizeof(send_msg), send_msg}, {sizeof(recv_msg), recv_msg} };

	if( -1 == (accept_fd = accept(arg.sockfd, \
					(struct sockaddr*)&addr_client, &accept_len)) )
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

int gen_key()
{
	srand((unsigned)time(NULL));
	return (rand()%9000+1000);
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

int get_as_key(int index)
{
	return (index > K_MIN__)&&(index <K_MAX__) ? 
		key_m[index] : 0 ;
}
