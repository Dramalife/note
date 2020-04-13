#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "pub.h"
#include <stdlib.h>

//��¼���ʺ���Ϣ
static hwy_people_t client_id;

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
	while(1){
		if(portnum > 65535){
			printf("bind error because of no port number available!\n");
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
			printf("bind successfully!\n");
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
	printf("connect OK\n");
	return 0; 
}



/*
 *���ܣ���֤��¼��ע���ʺ���Ϣ
 *���룺�ͻ����׽��֣���¼/ע��ѡ��
 *�������¼�ɹ�1��ע��ɹ�2������ʧ��-1
 * */
int check_id(int sockfd,int choice)
{
	char ID_info[17];//�洢�ʺ���Ϣ�Լ���¼/ע��ѡ��
	int i;
	char status[16];//�洢��¼/ע��״̬
	int ret;

	printf("check ID information!\n");
	memset(ID_info,0,17);
	//��¼��Я��ID ������
	if(1 == choice){
		ID_info[0]='1';
		memcpy(ID_info+1,client_id.id,4);
		memcpy(ID_info+9,client_id.passwd,8);
	}

	//ע�ᣬЯ���ǳƺ�����
	else {
		ID_info[0]='2';
		memcpy(ID_info+5,client_id.name,4);
		memcpy(ID_info+9,client_id.passwd,8);
	}

	//�����ʺ���Ϣ���������˽�����֤
	for(i=0;i<16;i++){
		if(ID_info[i] == '\0'){
			ID_info[i] = '/';
		}
	}
	ID_info[i] = '\0';
	ret = send(sockfd, ID_info, strlen(ID_info), 0);
	if(-1 == ret){
		perror("send id_info error!");
		return -1;
	}

	//�����ʺ���֤��Ϣ
	memset(status,0,16);
	ret = recv(sockfd,status,16,0);
	if(-1 == ret){
		perror("recv id_info error!");
		return -1;
	}

	if(memcmp(status,"successfully!",13)==0){
		//��¼�ɹ�
		//printf("login successfully!\n");
		send(sockfd,"ok",3,0);
		ret = recv(sockfd,client_id.name,4,0);
		if(-1 == ret){
			perror("recv ack_id_info error");
			return -1;
		}
		return 1;
	}
	else if(memcmp(status,"sign up",7)==0){
		//ע��ɹ�
		//printf("sign up successfully!\n");
		send(sockfd,"ok",3,0);
		ret = recv(sockfd,client_id.id,4,0);
		if(-1 == ret){
			perror("recv ack_id_info error");
			return -1;
		}
		return 2;
	}

	else 
	{
		printf("login or sign up error!\n");
		return -1;
	}
}


/*
 *���ܣ���¼����
 *���룺�ͻ����׽���
 *������ɹ�0��ʧ��-1
 *ע�⣺��¼ʧ�ܿ������µ�¼������ʧ�ܻ��˳�
 */
int hwy_login(int sockfd )
{
	int choice;//1--�����¼��2����ע��
	int login_status;//��¼״̬,-1����ʧ�ܣ�1����ɹ�
	int signup_status;//ע��״̬��-1����ʧ�ܣ�2����ɹ�

	while(1){
		printf("1------------login\n2------------sign up\n");
		scanf("%d",&choice);
		if(1 == choice){
			//��¼������ID������
			printf("ID:");
			scanf("%s",client_id.id);  
			printf("passwd:");
			scanf("%s",client_id.passwd);

			login_status=check_id(sockfd,choice);
			if(1 == login_status){
				//��¼�ɹ�,����������
				printf("��ӭ��¼�����ҡ�%s\n",client_id.name);
				break;
			}
			else 
				continue;
		}
		else if(2 == choice){
			//ע�ᣬ�����ǳƺ�����
			printf("name:");
			scanf("%s",client_id.name);
			printf("passwd:");
			scanf("%s",client_id.passwd);
			signup_status = check_id(sockfd,choice);
			if(2 == signup_status){
				//ע��ɹ������ص�¼����
				printf("ע��ɹ�\n");
				printf("����ʺ�Ϊ��%s\n�����µ�¼\n",client_id.id);
				continue;
			}
			else {
				//ע��ʧ��
				return -1;
			}
		}
		else {
			printf("������������ȷ��ֵ��\n");
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
void get_send_content(char get_send_buffer[CHAT_STRUCT_SIZE])
{
	int i;
	char dest[4];//Ŀ���ʺ�
	char time_buf[26];//ʱ��
	time_t t;
	time(&t);
	memset(get_send_buffer,0,CHAT_STRUCT_SIZE);
	//������
	memcpy(get_send_buffer+POSITION_SELFID,client_id.id,4);
	memcpy(get_send_buffer+POSITION_NAME,client_id.name,4);
	//������
	//printf("��Ҫ����˭��\n");
	scanf("%s",get_send_buffer+POSITION_DESTID);
	//��������
	//printf("��Ҫ��ʲô��\n");
	scanf("%s",get_send_buffer+POSITION_CONTENT);
	//����ʱ��
	memcpy(get_send_buffer+POSITION_TIME,ctime_r(&t,time_buf),26);  
	for(i=0;i<POSITION_CONTENT;i++){
		if(get_send_buffer[i] == '\0')
			get_send_buffer[i] = '/';
	}
}


/*
 *���ܣ����������Ϣ�����̴߳�����
 *
 * */
void *pthread_recv_func (void *arg)
{
	int sockfd = *(int *)arg;
	int ret;
	int i;
	hwy_recv_msg_t hwy_msg;//˭���ģ�ʲôʱ�򷢣�����ʲô
	char recv_buffer[CHAT_STRUCT_SIZE];//�������ݻ�����
	printf("���ڿ��������ˡ�\n");
	while(1){
		memset(recv_buffer,0,CHAT_STRUCT_SIZE);
		ret=recv(sockfd, recv_buffer,CHAT_STRUCT_SIZE, 0);
		if(ret == -1){
			printf("client received error!\n");
			return;
		}
		else {
			for(i=0;i<POSITION_CONTENT;i++){
				if(recv_buffer[i]== '/')
					recv_buffer[i]= '\0';
			}
			memcpy(hwy_msg.who,recv_buffer+POSITION_NAME,4);
			memcpy(hwy_msg.time,recv_buffer+POSITION_TIME,26);
			memcpy(hwy_msg.content,recv_buffer+POSITION_CONTENT,128);
			printf("%s:%s\n%s",hwy_msg.who,hwy_msg.content,hwy_msg.time);
		}
	}
}

void *pthread_send_func (void *arg)
{
	int sockfd = *(int *)arg;
	char send_buffer[CHAT_STRUCT_SIZE];//�������ݻ�����

	while(1){
		get_send_content(send_buffer);
		//����bye�˳�������
		if(memcmp(send_buffer,"bye",3)== 0 ){
			send(sockfd,"byebye~", strlen(send_buffer), 0);
			close(sockfd);
			exit(0);
		}

		send(sockfd, send_buffer, strlen(send_buffer), 0);
	}
}


int main(int argc,char *argv[])
{
	int sockfd = sock_init();
	if(sockfd == -1){
		printf("sock_init error!\n");
		return -1;
	}
	int ret = sock_client(sockfd);
	if(-1 == ret){
		printf("sock_client error!\n");
		return -1;
	}

	ret = hwy_login(sockfd);
	if(ret == -1){
		perror("hwy_login function error!");
		return -1;
	}
	//һ���̸߳��������Ϣ��һ���̸߳�������Ϣ
	pthread_t tid1,tid2;
	pthread_create(&tid2,0,pthread_recv_func,&sockfd);
	pthread_create(&tid1,0,pthread_send_func,&sockfd);
	while(1){
		sleep(9);
	}

	close(sockfd);
	return 0;
}	

