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



#include <sys/types.h>     
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "pub.h"
#include <stdlib.h>


//id--fd�ṹ������
struct client_info
{
	int client_fd;
	char client_id[4];
};

//���û��ʺź�ռ�õ��ļ�������һһ��Ӧ������
//�������һ��һͨ��
struct client_info client[CLIENT_MAX];

//���ݿ������ָ��
static sqlite3 *db = NULL;

/*
 *���ܣ���������ͨ�ŵĳ�ʼ������,���������׽��ֺͰ󶨿��ö˿ں�
 *���룺��
 *������ɹ������׽��֣�ʧ�ܷ���-1
 * */
int sock_init(void )
{
	int ret;
	//�����׽���--����ͨ��ΪIPv4��TCPͨ��
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket failed");
		return -1;
	}

	//��������ṹ��
	struct sockaddr_in myaddr; 
	myaddr.sin_port = htons(50000);	//Ӧ�ò�˿ں�
	myaddr.sin_family = AF_INET;		//IPv4Э��
	myaddr.sin_addr.s_addr = inet_addr("0.0.0.0");//ͨ�Ŷ����IP��ַ��0.0.0.0��ʾ����IP��ַ

	//���׽��ֺͽṹ��----�����Լ�˿ں��Ƿ��ظ���IP�Ƿ�׼ȷ
	ret = bind(sockfd,(struct sockaddr *)&myaddr,sizeof(myaddr));
	if(ret == -1)
	{
		perror("bind failed");
		return -1;
	}

	return sockfd;
}

/*
 *���ܣ��ѷ��������յ���Ϣ����������
 *���룺������Ϣ��������
 *�������
 * */
void send_to_all(char *msg)
{
	int i;
	for(i=0;i<CLIENT_MAX;i++)
	{
		if(client[i].client_fd != 0)
		{
			printf("sendto%s\n",client[i].client_id);
			printf("%s\n",msg);
			send(client[i].client_fd,msg,strlen(msg),0);
		}
	}
}

/*
 * ���ܣ��ѷ��������յ���Ϣ����ָ������
 * ���룺Ŀ���ʺ����󶨵�fd��������������
 * �������
 */
void send_to_one(int destfd,char *msg)
{
	int i;
	for(i=0;i<CLIENT_MAX;i++)
	{
		if(client[i].client_fd == destfd )
		{
			printf("sendto%s\n",client[i].client_id);
			printf("%s\n",msg);
			send(destfd,msg,strlen(msg),0);
			break;
		}
	}
}

//���ݿ��ʼ������
//�������ݿ⣬�������
void init_database_sqlite3(void )
{
	// ��hwyhwy.db�����ݿ⣬������ݿⲻ���ڣ��򴴽�����
	sqlite3_open_v2(DB_NAME,&db,
			SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,//�ɶ���д�ɴ���
			NULL);
	if(db==NULL)
	{
		perror("sqlite3_open_v2 faield\n");
		exit(-1);
	}

	//�����ݿ��д������
	//ID �ǳ� ���룬IDΪ����
	char *errmsg = NULL;
	char *sql = "CREATE TABLE if not exists hwy_id_sheet(id text primary key,\
		     name text not null,passwd text not null);";
	sqlite3_exec(db, sql, NULL, NULL, &errmsg);
}


/*
 *���ܣ���֤�ͻ��˴�����ID��Ϣ
 *���룺������accept��������׽���
 *�������֤״̬��1��¼�ɹ���2ע��ɹ�������ʧ��
 * */
int check_recv_id(int fd )
{

	int ret;
	int i;
	struct account_st account_data; //�ʺ���Ϣ�ṹ��ID_info
	char recv_ID_info[17];//�ͻ��˴������ʺ���Ϣ���¼/ע��ѡ��
	char ack_ID_info[4];
	char ack_ok[3];
	char *errmsg = NULL;
	char sql[128];

	int nrow=0;
	int ncolumn=0;
	char **azResult=NULL;
	char status[16];

	//����ID_info
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

	//��ӡ���յ�����Ϣ
	for(i=0;i<17;i++)
	{
		if(recv_ID_info[i] == '/')
			recv_ID_info[i] = '\0';
	}
	memcpy(account_data.id,recv_ID_info+1,4);
	memcpy(account_data.name,recv_ID_info+5,4);
	memcpy(account_data.passwd,recv_ID_info+9,8);

	//��¼,��֤�����ID��passwd�Ƿ���ȷ
	if(recv_ID_info[0] == '1')
	{
		sprintf(sql,"select * from hwy_id_sheet where id = '%s' and passwd = '%s';",
				account_data.id,account_data.passwd);
		sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&errmsg);
		if(nrow == 0)
		{
			//û��ƥ�����¼��֤ʧ��
			strcpy(status,"login failed!");
			send(fd,status,strlen(status),0);
			return -1;
		}
		else {
			//��¼��֤�ɹ�
			memset(status,0,16);
			strcpy(status,"successfully!");
			send(fd,status,strlen(status),0);
			recv(fd,ack_ok,3,0);

			//�������client_fd---client_id
			for(i=0;i<CLIENT_MAX;i++)
			{
				if(client[i].client_fd == fd)
				{
					memcpy(client[i].client_id,account_data.id,4);
					break;
				}
			}

			//�����û��ǳ�
			strcpy(ack_ID_info,azResult[4]);
			send(fd,ack_ID_info,strlen(ack_ID_info),0);
			return 1;
		}
	}

	//ע�ᣬ�����ǳƺ�����ע�ᡢ��¼�ʺ���Ϣ���������ʺ�
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

			//�����û��ʺ���Ϣ
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

//ÿ����һ���ͻ��˵����ӣ��㴴��һ���߳�
void *service_thread (void *arg)
{
	int fd = *((int *)arg);
	int ret;
	int i;
	char recv_buffer[CHAT_STRUCT_SIZE];
	//hwy_send_msg_t hwy_C_SendMsg;
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

	//��¼�ɹ������������������Ϣ--������ת��
	while(1)
	{
		memset(recv_buffer,0,CHAT_STRUCT_SIZE);
		ret = recv(fd, recv_buffer, CHAT_STRUCT_SIZE, 0);
		if(-1 == ret)
		{
			perror("recv error!");
			return NULL;
		}
		else if(ret>0)
		{
			printf("RECV[%s]\n",recv_buffer);

			if(memcmp(recv_buffer+POSITION_DESTID,"999",3)== 0)
				send_to_all(recv_buffer);
			else{
				for(i = 0;i< CLIENT_MAX;i++)
				{
					if(memcmp(client[i].client_id,recv_buffer+POSITION_DESTID,\
								3)== 0)
					{
						send_to_one(client[i].client_fd,recv_buffer);
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
	listen(sock_fd,CLIENT_MAX);
	while(1)
	{
		int index;
		struct sockaddr_in clientaddr;
		int len = sizeof(clientaddr);
		int fd_accept = -1;

		if( -1 == (fd_accept = accept(sock_fd,(struct sockaddr*)&clientaddr,&len)) )
		{
			perror("accept failed...\n");
			continue;
		}
		printf("accept OK!\n");

		for(index=0; index < CLIENT_MAX; index++)
		{
			if(client[index].client_fd == 0)
			{
				client[index].client_fd = fd_accept;
				printf("client fd = %d\n", client[index].client_fd);
				//�пͻ�������֮�������߳�Ϊ�˿ͻ��˷���
				pthread_t tid;
				pthread_create(&tid, 0, service_thread, &(client[index].client_fd));
				break;
			}
		}

		if(index == CLIENT_MAX)
		{
			char * str = "�Բ��������������ˣ�\n";
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

