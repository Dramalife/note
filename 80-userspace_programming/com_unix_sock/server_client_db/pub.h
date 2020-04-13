#ifndef __HWY_NETWORK_CHAT_H__
#define __HWY_NETWORK_CHAT_H__

#include "lib_dramalife.h"

//����������ע���½�������Ա����
#define  PEOPLE_NUM_MAX   10
//������Ϣ�����ͽṹ�壩����
#define  CHAT_STRUCT_SIZE (POSITION_CONTENT+128)
//�ͻ��������������
#define  CLIENT_MAX       3

#define  POSITION_SELFID  0
#define  POSITION_NAME    (4+POSITION_SELFID)
#define  POSITION_DESTID  (4+POSITION_NAME)
#define  POSITION_TIME    (4+POSITION_DESTID)
#define  POSITION_CONTENT (26+POSITION_TIME)

#define DB_NAME	"chat.db"

//����������Ա�����Ϣ
typedef struct 
{
	char id[4];	 //��½�ʺ�
	char name[4];	 //�ǳ�
	char passwd[8];//��½����
}hwy_people_t;

//������Ϣ֮���͵ĸ�ʽ
typedef struct
{
	char self_id[4];	//����ID
	char name[4];		//�����ǳ�
	char dest_id[4];	//Ŀ��ID
	char time[26];	//����ʱ��
	char content[128];	//��������
}hwy_send_msg_t;

//������Ϣ֮���յĸ�ʽ
typedef struct
{
	char who[4];		//������
	char time[26];	//����ʱ��
	char content[128];	//��������
}hwy_recv_msg_t;



#endif
