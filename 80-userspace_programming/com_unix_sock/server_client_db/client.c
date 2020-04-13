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


//��¼���ʺ���Ϣ
static struct account_st account_data;

/*
 * ���ܣ���������ͨ�ŵĳ�ʼ������,���������׽��ֺͰ󶨿��ö˿ں�
 * �����������
 * ����������ɹ�������������ͨ�ŵ��׽��֣�ʧ�ܷ���-1
 */
int sock_init(void)
{
	int ret;
	int portnum;//�˿ں�
	//�����׽���--����ͨ��ΪIPv4��TCPͨ��
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket failed");
		return -1;
	}

	//��������ṹ��
	/*��50001��ʼ��������������δ��ռ�õĶ˿ںţ�Ȼ���
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
		myaddr.sin_port = htons(portnum++);       //Ӧ�ò�˿ں�
		myaddr.sin_family = AF_INET;          //IPv4Э��
		myaddr.sin_addr.s_addr = inet_addr("0.0.0.0");//ͨ�Ŷ����IP��ַ��0.0.0.0��ʾ����IP��ַ
		//���׽��ֺͽṹ��----�����Լ�˿ں��Ƿ��ظ���IP�Ƿ�׼ȷ
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
 *���ܣ����ӷ�����
 *����������׽���
 *������������ӳɹ����ı�־���ɹ�����1��ʧ�ܷ���0
 * */
int sock_client(int sockfd)
{
	//���ӷ�����
	struct sockaddr_in srcaddr;
	srcaddr.sin_port = htons(50000);//��������Ӧ�ò�˿ں�
	srcaddr.sin_family = AF_INET;//��������IPv4Э��
	srcaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//��������IP��ַ-��������

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
 *���ܣ���֤��¼��ע���ʺ���Ϣ
 *���룺�ͻ����׽��֣���¼/ע��ѡ��
 *�������¼�ɹ�1��ע��ɹ�2������ʧ��-1
 * */
int check_id(int sockfd, int choice)
{
	char info_id[17];//�洢�ʺ���Ϣ�Լ���¼/ע��ѡ��
	int index;
	char status[16];//�洢��¼/ע��״̬
	int ret;

	dlprint(__func__,__LINE__,"checking id...\n");
	memset(info_id, 0, sizeof(info_id));
	//��¼��Я��ID ������
	if(1 == choice)
	{
		info_id[0]='1';
		memcpy(info_id+1,account_data.id,4);
		memcpy(info_id+9,account_data.passwd,8);
	}

	//ע�ᣬЯ���ǳƺ�����
	else {
		info_id[0]='2';
		memcpy(info_id+5,account_data.name,4);
		memcpy(info_id+9,account_data.passwd,8);
	}

	//�����ʺ���Ϣ���������˽�����֤
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

	//�����ʺ���֤��Ϣ
	memset(status,0,16);
	ret = recv(sockfd,status,16,0);
	if(-1 == ret)
	{
		perror("[Auth] : recv error!");
		return -1;
	}

	if(memcmp(status,"successfully!",13)==0)
	{
		//��¼�ɹ�
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
		//ע��ɹ�
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
 *���ܣ���¼����
 *���룺�ͻ����׽���
 *������ɹ�0��ʧ��-1
 *ע�⣺��¼ʧ�ܿ������µ�¼������ʧ�ܻ��˳�
 */
int client_signin(int sockfd )
{
	int choice;//1--�����¼��2����ע��
	int login_status;//��¼״̬,-1����ʧ�ܣ�1����ɹ�
	int signup_status;//ע��״̬��-1����ʧ�ܣ�2����ɹ�

	while(1)
	{
		dlprint(__func__,__LINE__,"1------------sign in\n2------------sign up\n");
		scanf("%d",&choice);
		if(1 == choice)
		{
			//��¼������ID������
			dlprint(__func__,__LINE__,"ID:");
			scanf("%s",account_data.id);  
			dlprint(__func__,__LINE__,"passwd:");
			scanf("%s",account_data.passwd);

			login_status=check_id(sockfd,choice);
			if(1 == login_status)
			{
				//��¼�ɹ�,����������
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
			//ע�ᣬ�����ǳƺ�����
			dlprint(__func__,__LINE__,"name:");
			scanf("%s",account_data.name);
			dlprint(__func__,__LINE__,"passwd:");
			scanf("%s",account_data.passwd);
			signup_status = check_id(sockfd,choice);
			if(2 == signup_status)
			{
				//ע��ɹ������ص�¼����
				dlprint(__func__,__LINE__,"Sing up Successfully!\n");
				dlprint(__func__,__LINE__,"Your ID is (%s)\nRe-sign-in please!\n",account_data.id);
				continue;
			}
			else {
				//ע��ʧ��
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
 *���ܣ���ȡ�����������
 *���룺�����������ݵ�ָ��
 *�������
 * */
//��ȡ�����������
void get_send_content( struct message_st *message_ptr )
{
	int i;
	char dest[4];//Ŀ���ʺ�
	char time_buf[26];//ʱ��
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
 *���ܣ����������Ϣ�����̴߳�����
 *
 * */
void *pthread_recv_func (void *arg)
{
	int index;
	int sockfd = *(int *)arg;
	struct message_st message_data;//˭���ģ�ʲôʱ�򷢣�����ʲô

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

