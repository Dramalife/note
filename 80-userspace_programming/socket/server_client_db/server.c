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


//id--fd结构体类型
struct client_info
{
	int client_fd;
	char client_id[4];
};

//将用户帐号和占用的文件描述符一一对应起来，
//方便后续一对一通信
struct client_info client[CLIENT_MAX];

//数据库的连接指针
static sqlite3 *db = NULL;



/*
 *功能：建立网络通信的初始化工作,包括创建套接字和绑定可用端口号
 *输入：无
 *输出：成功返回套接字，失败返回-1
 * */
int sock_init(void )
{
	int ret;
	//创建套接字--设置通信为IPv4的TCP通信
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket failed");
		return -1;
	}

	//配置网络结构体
	struct sockaddr_in myaddr; 
	myaddr.sin_port = htons(50000);	//应用层端口号
	myaddr.sin_family = AF_INET;		//IPv4协议
	myaddr.sin_addr.s_addr = inet_addr("0.0.0.0");//通信对象的IP地址，0.0.0.0表示所有IP地址

	//绑定套接字和结构体----主机自检端口号是否重复，IP是否准确
	ret = bind(sockfd,(struct sockaddr *)&myaddr,sizeof(myaddr));
	if(ret == -1)
	{
		perror("bind failed");
		return -1;
	}

	return sockfd;
}

/*
 *功能：把服务器接收的信息发给所有人
 *输入：聊天信息具体内容
 *输出：无
 * */
void send_to_all(struct message_st *message_ptr)
{
	int i;
	for(i=0;i<CLIENT_MAX;i++)
	{
		if(client[i].client_fd != 0)
		{
#if 0
			printf("sendto(%s) \n",client[i].client_id);
			printf("content(%s) \n", message_ptr->content);
#else
			show_message(message_ptr);
#endif
			send(client[i].client_fd, message_ptr, sizeof(struct message_st), 0);
		}
	}
}

/*
 * 功能：把服务器接收的消息发给指定的人
 * 输入：目标帐号所绑定的fd，具体聊天内容
 * 输出：无
 */
void send_to_one(int destfd, struct message_st *message_ptr)
{
	int i;
	for(i=0;i<CLIENT_MAX;i++)
	{
		if(client[i].client_fd == destfd )
		{
#if 0
			printf("sendto(%d) \n",client[i].client_id);
			printf("content[%s] \n", message_ptr->content);
#else
			show_message(message_ptr);
#endif
			send(destfd, message_ptr, sizeof(struct message_st), 0);
			break;
		}
	}
}

//数据库初始化工作
//连接数据库，创建表格
void init_database_sqlite3(void )
{
	// 打开hwyhwy.db的数据库，如果数据库不存在，则创建并打开
	sqlite3_open_v2(DB_NAME,&db,
			SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,//可读可写可创建
			NULL);
	if(db==NULL)
	{
		perror("sqlite3_open_v2 faield\n");
		exit(-1);
	}

	//在数据库中创建表格
	//ID 昵称 密码，ID为主键
	char *errmsg = NULL;
	char *sql = "CREATE TABLE if not exists hwy_id_sheet(id text primary key,\
		     name text not null,passwd text not null);";
	sqlite3_exec(db, sql, NULL, NULL, &errmsg);
}


/*
 *功能：验证客户端传来的ID信息
 *输入：服务器accept后产生的套接字
 *输出：验证状态，1登录成功，2注册成功，其他失败
 * */
int check_recv_id(int fd )
{

	int ret;
	int i;
	struct account_st account_data; //帐号信息结构体ID_info
	char recv_ID_info[17];//客户端传来的帐号信息其登录/注册选择
	char ack_ID_info[4];
	char ack_ok[3];
	char *errmsg = NULL;
	char sql[128];

	int nrow=0;
	int ncolumn=0;
	char **azResult=NULL;
	char status[16];

	//接收ID_info
	memset(recv_ID_info,0,17);
	memset(ack_ID_info,0,4);
	memset(sql,0,128);
	memset(status,0,16);

	ret = recv(fd, recv_ID_info, 17, 0);
	if(-1 == ret)
	{
		perror("recv error!");
		return -1;
	}

	//打印接收到的信息
	for(i=0;i<17;i++)
	{
		if(recv_ID_info[i] == '/')
			recv_ID_info[i] = '\0';
	}
	memcpy(account_data.id,recv_ID_info+1,4);
	memcpy(account_data.name,recv_ID_info+5,4);
	memcpy(account_data.passwd,recv_ID_info+9,8);

	//登录,验证输入的ID和passwd是否正确
	if(recv_ID_info[0] == '1')
	{
		sprintf(sql,"select * from hwy_id_sheet where id = '%s' and passwd = '%s';",
				account_data.id,account_data.passwd);
		sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&errmsg);
		if(nrow == 0)
		{
			//没有匹配项，登录验证失败
			strcpy(status,"login failed!");
			send(fd,status,strlen(status),0);
			return -1;
		}
		else {
			//登录验证成功
			memset(status,0,16);
			strcpy(status,"successfully!");
			send(fd,status,strlen(status),0);
			recv(fd,ack_ok,3,0);

			//在这里绑定client_fd---client_id
			for(i=0;i<CLIENT_MAX;i++)
			{
				if(client[i].client_fd == fd)
				{
					memcpy(client[i].client_id,account_data.id,4);
					break;
				}
			}

			//发送用户昵称
			strcpy(ack_ID_info,azResult[4]);
			send(fd,ack_ID_info,strlen(ack_ID_info),0);
			return 1;
		}
	}

	//注册，根据昵称和密码注册、记录帐号信息，并返回帐号
	else {
		int j = 100;
		char *sql1 = "select * from hwy_id_sheet;";
		sqlite3_get_table(db,sql1,&azResult,&nrow,&ncolumn,&errmsg);
		j = j+ nrow;
		memset(ack_ID_info,0,4);
		sprintf(ack_ID_info,"%d",j);//---itoa
		memcpy(account_data.id,ack_ID_info,4);

		sprintf(sql,"insert into hwy_id_sheet values('%s','%s','%s'); ",account_data.id,
				account_data.name,account_data.passwd);
		ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
		if(ret == SQLITE_OK)
		{
			printf("Sign up successfully!\n");
			memset(status,0,16);
			strcpy(status,"sign up");
			send(fd,status,strlen(status),0);
			recv(fd,ack_ok,3,0);

			//发送用户帐号信息
			send(fd,ack_ID_info,strlen(ack_ID_info),0);
			return 2;
		}
		else {
			printf("Sign up Failed\n");
			memset(status,0,16);
			strcpy(status,"sign up error");
			send(fd,status,strlen(status),0);
			return -1;
		}
	}
}

//每接收一个客户端的连接，便创建一个线程
void *service_thread (void *arg)
{
	int fd = *((int *)arg);
	int ret;
	int i;
	struct message_st message_data;

	printf("fd(pthread) = %d\n",fd);

	/* Authenticate sing-in/sign-up info */
#if 1
	while(1)
	{ 
		ret = check_recv_id(fd);
		printf("check_recv_id = %d\n",ret);
		if(ret == 1)
		{
			printf("Sign in successfully! \n");
			break;
		}
		else if(ret == 2)
		{
			printf("Sign up successfully! \nRe-sign-in recommand!\n");
			continue;
		}
		else {
			printf("Authenticated Failed!");
			continue;
		}
	}
#else
	ret = check_recv_id(fd);
	printf("check_recv_id = %d\n",ret);
	switch(ret){
		case 1:
			printf("Sign in successfully! \n");
			break;
		case 2:
			printf("Sign up successfully! \nRe-sign-in recommand!\n");
			break;
		default:
			printf("Authenticated Failed!");
			break;

	}
#endif

	//登录成功，处理正常聊天的信息--接收与转发
	while(1)
	{
		memset(&message_data, 0, sizeof(message_data));
		ret = recv(fd, &message_data, CHAT_STRUCT_SIZE, 0);
		if(-1 == ret)
		{
			perror("recv error!");
			return NULL;
		}
		else if(ret>0)
		{
			show_message(&message_data);

			if(memcmp(message_data.recver.id,"999",3)== 0)
				send_to_all(&message_data);
			else{
				for(i = 0;i< CLIENT_MAX;i++)
				{
					if(memcmp(client[i].client_id, message_data.recver.id, 3)== 0)
					{
						send_to_one(client[i].client_fd, &message_data);
						break;
					}
				}

			}
		}

	}  
}

void init_server(int sock_fd)
{
	printf("Starting server...\n");
	while( 0 != listen(sock_fd,CLIENT_MAX))
	{
		perror("listen");
		sleep(1);
	}
	while(1)
	{
		int index;
		struct sockaddr_in clientaddr;
		int len = sizeof(clientaddr);
		int fd_accept = -1;

		if( -1 == (fd_accept = accept(sock_fd, (struct sockaddr*)&clientaddr, &len)) )
		{
			perror("accept failed");
			sleep(1);
			continue;
		}
		printf("accept OK!\n");

		for(index=0; index < CLIENT_MAX; index++)
		{
			if(client[index].client_fd == 0)
			{
				client[index].client_fd = fd_accept;
				printf("client fd = %d\n", client[index].client_fd);

				/* Creating thread for client */
				pthread_t tid;
				pthread_create(&tid, 0, service_thread, &(client[index].client_fd));
				break;
			}
		}

		if(index == CLIENT_MAX)
		{
			char * str = "Client num max!\n";
			send(fd_accept,str,sizeof(str),0);
			close(fd_accept);
		}

	}

}


int main(int argc,char *argv[])
{
	int sock_fd = sock_init();
	init_database_sqlite3();
	init_server(sock_fd);
	return 0;
}

