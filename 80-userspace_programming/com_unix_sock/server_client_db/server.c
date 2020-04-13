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
typedef struct
{
	int client_fd;
	char client_id[4];
}client_id_to_fd;

//���û��ʺź�ռ�õ��ļ�������һһ��Ӧ������
//�������һ��һͨ��
client_id_to_fd id_to_fd[CLIENT_MAX];

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
void SendMsgToAll(char *msg)
{
	int i;
	for(i=0;i<CLIENT_MAX;i++){
		if(id_to_fd[i].client_fd != 0){
			printf("sendto%s\n",id_to_fd[i].client_id);
			printf("%s\n",msg);
			send(id_to_fd[i].client_fd,msg,strlen(msg),0);
		}
	}
}

/*
 * ���ܣ��ѷ��������յ���Ϣ����ָ������
 * ���룺Ŀ���ʺ����󶨵�fd��������������
 * �������
 */
void SendMsgToSb(int destfd,char *msg)
{
	int i;
	for(i=0;i<CLIENT_MAX;i++){
		if(id_to_fd[i].client_fd == destfd ){
			printf("sendto%s\n",id_to_fd[i].client_id);
			printf("%s\n",msg);
			send(destfd,msg,strlen(msg),0);
			break;
		}
	}
}

//���ݿ��ʼ������
//�������ݿ⣬�������
void hwyDataBase_init(void )
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
	hwy_people_t client_ID_info; //�ʺ���Ϣ�ṹ��ID_info
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
	if(-1 == ret){
		perror("recv error!");
		return -1;
	}

	//��ӡ���յ�����Ϣ
	for(i=0;i<17;i++){
		if(recv_ID_info[i] == '/')
			recv_ID_info[i] = '\0';
	}
	memcpy(client_ID_info.id,recv_ID_info+1,4);
	memcpy(client_ID_info.name,recv_ID_info+5,4);
	memcpy(client_ID_info.passwd,recv_ID_info+9,8);

	//��¼,��֤�����ID��passwd�Ƿ���ȷ
	if(recv_ID_info[0] == '1'){
		sprintf(sql,"select * from hwy_id_sheet where id = '%s' and passwd = '%s';",
				client_ID_info.id,client_ID_info.passwd);
		sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&errmsg);
		if(nrow == 0){
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
			for(i=0;i<CLIENT_MAX;i++){
				if(id_to_fd[i].client_fd == fd){
					memcpy(id_to_fd[i].client_id,client_ID_info.id,4);
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
		memcpy(client_ID_info.id,ack_ID_info,4);

		sprintf(sql,"insert into hwy_id_sheet values('%s','%s','%s'); ",client_ID_info.id,
				client_ID_info.name,client_ID_info.passwd);
		ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
		if(ret == SQLITE_OK){
			printf("ע��ɹ�\n");
			memset(status,0,16);
			strcpy(status,"sign up");
			send(fd,status,strlen(status),0);
			recv(fd,ack_ok,3,0);

			//�����û��ʺ���Ϣ
			send(fd,ack_ID_info,strlen(ack_ID_info),0);
			return 2;
		}
		else {
			printf("ע��ʧ��\n");
			memset(status,0,16);
			strcpy(status,"sign up error");
			send(fd,status,strlen(status),0);
			return -1;
		}
	}
}

//ÿ����һ���ͻ��˵����ӣ��㴴��һ���߳�
void * thread_func (void *arg)
{
	int fd = *(int *)arg;
	int ret;
	int i;
	hwy_send_msg_t hwy_C_SendMsg;
	printf("pthread = %d\n",fd);

	char recv_buffer[CHAT_STRUCT_SIZE];

	//��֤��¼/ע����Ϣ
	while(1){ 
		ret = check_recv_id(fd);
		printf("check_recv_id = %d\n",ret);
		if(ret == 1){
			//�ɹ���¼
			printf("��¼�ɹ�\n");
			break;
		}
		else if(ret == 2){
			//ע��ɹ�,��Ҫ���µ�¼
			continue;
		}
		else {
			//��֤ʧ��,���������˳�
			continue;
		}
	}

	//��¼�ɹ������������������Ϣ--������ת��
	while(1){
		memset(recv_buffer,0,CHAT_STRUCT_SIZE);
		ret = recv(fd, recv_buffer, CHAT_STRUCT_SIZE, 0);
		if(-1 == ret){
			perror("recv error!");
			return;
		}
		else if(ret>0){
			printf("���յ�������Ϊ��%s\n",recv_buffer);

			if(memcmp(recv_buffer+POSITION_DESTID,"999",3)== 0)
				SendMsgToAll(recv_buffer);
			else{
				for(i = 0;i< CLIENT_MAX;i++){
					if(memcmp(id_to_fd[i].client_id,recv_buffer+POSITION_DESTID,\
								3)== 0){
						SendMsgToSb(id_to_fd[i].client_fd,recv_buffer);
						break;
					}
				}

			}
		}

	}  
}

void service(int sock_fd)
{
	printf("����������...\n");
	listen(sock_fd,CLIENT_MAX);
	while(1){
		struct sockaddr_in clientaddr;
		int len = sizeof(clientaddr);
		int client_sock = accept(sock_fd,(struct sockaddr*)&clientaddr,&len);
		if(client_sock== -1)
		{
			printf("accept failed...\n");
			continue;
		}
		printf("accept OK!\n");
		int i;
		for(i=0;i<CLIENT_MAX;i++){
			if(id_to_fd[i].client_fd == 0){
				id_to_fd[i].client_fd = client_sock;
				printf("client fd = %d\n",client_sock);
				//�пͻ�������֮�������߳�Ϊ�˿ͻ��˷���
				pthread_t tid;
				pthread_create(&tid, 0,thread_func,&client_sock);
				break;
			}
		}
		if(i == CLIENT_MAX){
			char * str = "�Բ��������������ˣ�\n";
			send(client_sock,str,sizeof(str),0);
			close(client_sock);
		}

	}

}


int main(int argc,char *argv[])
{
	int sock_fd = sock_init();
	hwyDataBase_init();
	service(sock_fd);
	return 0;
}

