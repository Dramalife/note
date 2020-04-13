/*
 * note "socket/database" related file
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
 * Linux server 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Mon Apr 13 14:56:46 CST 2020
 * 	COPY FROM : https://blog.csdn.net/qq_36863664/article/details/100057153;
 * Update : Mon Apr 13 14:56:46 CST 2020
 *  
 * Update
 *
 */



#include "pub.h"


#define dlprint(func,line,x,...)	do{printf("[%s,%d] ",func,line);printf(x,##__VA_ARGS__);}while(0)


//登录者帐号信息
static struct account_st account_data;

/*
 * 功能：建立网络通信的初始化工作,包括创建套接字和绑定可用端口号
 * 输入参数：无
 * 输出参数：成功返回用于网络通信的套接字，失败返回-1
 */
int sock_init(void)
{
	int ret;
	int portnum;//端口号
	//创建套接字--设置通信为IPv4的TCP通信
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket failed");
		return -1;
	}

	//配置网络结构体
	/*从50001开始，查找主机中尚未被占用的端口号，然后绑定
	 */
	struct sockaddr_in myaddr;
	portnum = 50001;
	while(1)
	{
		if(portnum > 65535)
		{
			dlprint(__func__,__LINE__,"bind error because of no port number available!\n");
			return -1;
		}
		myaddr.sin_port = htons(portnum++);       //应用层端口号
		myaddr.sin_family = AF_INET;          //IPv4协议
		myaddr.sin_addr.s_addr = inet_addr("0.0.0.0");//通信对象的IP地址，0.0.0.0表示所有IP地址
		//绑定套接字和结构体----主机自检端口号是否重复，IP是否准确
		ret = bind(sockfd,(struct sockaddr *)&myaddr,sizeof(myaddr));
		if(ret == -1)
		{
			continue;
		}
		else{
			dlprint(__func__,__LINE__,"bind successfully!\n");
			break;
		}
	}
	return sockfd;
}

/*
 *功能：连接服务器
 *输入参数：套接字
 *输出参数：连接成功与否的标志，成功返回1，失败返回0
 * */
int sock_client(int sockfd)
{
	//连接服务器
	struct sockaddr_in srcaddr;
	srcaddr.sin_port = htons(50000);//服务器的应用层端口号
	srcaddr.sin_family = AF_INET;//服务器的IPv4协议
	srcaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器的IP地址-本地主机

	int ret = connect(sockfd,(struct sockaddr*)&srcaddr,sizeof(srcaddr));
	if(ret == -1)
	{
		perror("connect failed");
		return -1;
	}
	dlprint(__func__,__LINE__,"connect OK\n");
	return 0; 
}



/*
 *功能：验证登录或注册帐号信息
 *输入：客户端套接字，登录/注册选择
 *输出：登录成功1，注册成功2，任意失败-1
 * */
int check_id(int sockfd, int choice)
{
	char info_id[17];//存储帐号信息以及登录/注册选择
	int index;
	char status[16];//存储登录/注册状态
	int ret;

	dlprint(__func__,__LINE__,"checking id...\n");
	memset(info_id, 0, sizeof(info_id));
	//登录，携带ID 和密码
	if(1 == choice)
	{
		info_id[0]='1';
		memcpy(info_id+1,account_data.id,4);
		memcpy(info_id+9,account_data.passwd,8);
	}

	//注册，携带昵称和密码
	else {
		info_id[0]='2';
		memcpy(info_id+5,account_data.name,4);
		memcpy(info_id+9,account_data.passwd,8);
	}

	//发送帐号信息给服务器端进行验证
	for(index=0;index<16;index++)
	{
		if(info_id[index] == '\0')
		{
			info_id[index] = '/';
		}
	}
	info_id[index] = '\0';
	ret = send(sockfd, info_id, strlen(info_id), 0);
	if(-1 == ret)
	{
		perror("[Auth] : send error!");
		return -1;
	}

	//接收帐号验证信息
	memset(status,0,16);
	ret = recv(sockfd,status,16,0);
	if(-1 == ret)
	{
		perror("[Auth] : recv error!");
		return -1;
	}

	if(memcmp(status,"successfully!",13)==0)
	{
		//登录成功
		dlprint(__func__,__LINE__,"sign in successfully!\n");
		send(sockfd,"ok",3,0);
		ret = recv(sockfd,account_data.name,4,0);
		if(-1 == ret)
		{
			perror("recv ack_id_info error");
			return -1;
		}
		return 1;
	}
	else if(memcmp(status,"sign up",7)==0)
	{
		//注册成功
		dlprint(__func__,__LINE__,"sign up successfully!\n");
		send(sockfd,"ok",3,0);
		ret = recv(sockfd,account_data.id,4,0);
		if(-1 == ret)
		{
			perror("recv ack_id_info error");
			return -1;
		}
		return 2;
	}

	else 
	{
		dlprint(__func__,__LINE__,"login or sign up error!\n");
		return -1;
	}
}


/*
 *功能：登录界面
 *输入：客户端套接字
 *输出：成功0，失败-1
 *注意：登录失败可以重新登录，其他失败会退出
 */
int client_signin(int sockfd )
{
	int choice;//1--代表登录，2代表注册
	int login_status;//登录状态,-1代表失败，1代表成功
	int signup_status;//注册状态，-1代表失败，2代表成功

	while(1)
	{
		dlprint(__func__,__LINE__,"1------------sign in\n2------------sign up\n");
		scanf("%d",&choice);
		if(1 == choice)
		{
			//登录，输入ID和密码
			dlprint(__func__,__LINE__,"ID:");
			scanf("%s",account_data.id);  
			dlprint(__func__,__LINE__,"passwd:");
			scanf("%s",account_data.passwd);

			login_status=check_id(sockfd,choice);
			if(1 == login_status)
			{
				//登录成功,进入聊天室
				dlprint(__func__,__LINE__,"Welcom (%s) !\n",account_data.name);
				break;
			}
			else 
			{
				dlprint(__func__,__LINE__,"Sign in failed !\n");
				continue;
			}
		}
		else if(2 == choice)
		{
			//注册，输入昵称和密码
			dlprint(__func__,__LINE__,"name:");
			scanf("%s",account_data.name);
			dlprint(__func__,__LINE__,"passwd:");
			scanf("%s",account_data.passwd);
			signup_status = check_id(sockfd,choice);
			if(2 == signup_status)
			{
				//注册成功，返回登录界面
				dlprint(__func__,__LINE__,"Sing up Successfully!\n");
				dlprint(__func__,__LINE__,"Your ID is (%s)\nRe-sign-in please!\n",account_data.id);
				continue;
			}
			else {
				//注册失败
				dlprint(__func__,__LINE__,"Sing up Failed!\n");
				return -1;
			}
		}
		else {
			dlprint(__func__,__LINE__,"Unknwon type (%d).\n", choice);
			continue;
		}
	}
	return 0;
}


/*
 *功能：获取聊天具体内容
 *输入：保存聊天内容的指针
 *输出：无
 * */
//获取聊天具体内容
void get_send_content( struct message_st *message_ptr )
{
	int i;
	char dest[4];//目标帐号
	char time_buf[26];//时间
	time_t t;

	time(&t);

	memset(message_ptr, 0, sizeof(struct message_st));
	/* Sender */
	memcpy(message_ptr->sender.id,	account_data.id,	sizeof(message_ptr->sender.id	));
	memcpy(message_ptr->sender.name,account_data.name,	sizeof(message_ptr->sender.name ));
	/* Recver */
	dlprint(__func__,__LINE__,"To whom(id) :\n");
	scanf("%s", message_ptr->recver.id);
	/* Content */
	dlprint(__func__,__LINE__,"Content :\n");
	scanf("%s", message_ptr->content);
	/* Time */
	memcpy(message_ptr->time, ctime_r(&t,time_buf), sizeof(message_ptr->time));  
}


/*
 *功能：处理接收信息的子线程处理函数
 *
 * */
void *pthread_recv_func (void *arg)
{
	int index;
	int sockfd = *(int *)arg;
	struct message_st message_data;//谁发的，什么时候发，发了什么

	dlprint(__func__,__LINE__,"Recving...\n");
	while(1)
	{
		memset(&message_data, 0, sizeof(struct message_st));
		if( -1 == recv(sockfd, &message_data, sizeof(struct message_st), 0) )
		{
			dlprint(__func__,__LINE__,"client received error!\n");
			return;
		}
		else
		{
			show_message(&message_data);
		}
	}
}

void *pthread_send_func (void *arg)
{
	int sockfd = *(int *)arg;
	struct message_st message_tmp;

	while(1)
	{
		get_send_content(&message_tmp);

		/* Exit */
		if(memcmp(message_tmp.content,"bye",3)== 0 )
		{
			send(sockfd, &message_tmp, sizeof(struct message_st), 0);
			close(sockfd);
			exit(0);
		}

		send(sockfd, &message_tmp, sizeof(message_tmp), 0);
	}
}


int main(int argc,char *argv[])
{
	int sockfd = -1;
	pthread_t tid_send = 0;
	pthread_t tid_recv = 0;

	if( -1 == (sockfd= sock_init()) )
	{
		dlprint(__func__,__LINE__,"sock_init error!\n");
		return -1;
	}
	if( -1 == sock_client(sockfd) )
	{
		dlprint(__func__,__LINE__,"sock_client error!\n");
		return -1;
	}

	if( -1 == client_signin(sockfd) )
	{
		dlprint(__func__,__LINE__,"client_signin function error!");
		return -1;
	}

	pthread_create(&tid_recv,0,pthread_recv_func,&sockfd);
	pthread_create(&tid_send,0,pthread_send_func,&sockfd);
	while(1)
	{
		sleep(9);
	}

	close(sockfd);
	return 0;
}	

