#ifndef __HWY_NETWORK_CHAT_H__
#define __HWY_NETWORK_CHAT_H__

#include "lib_dramalife.h"
#include <sys/types.h>     
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

//#define  PEOPLE_NUM_MAX   10
//聊天信息（发送结构体）长度
#define  CHAT_STRUCT_SIZE (POSITION_CONTENT+128)
//客户端最大连接数量
#define  CLIENT_MAX       3

#define  POSITION_SELFID  0
#define  POSITION_NAME    (4+POSITION_SELFID)
#define  POSITION_DESTID  (4+POSITION_NAME)
#define  POSITION_TIME    (4+POSITION_DESTID)
#define  POSITION_CONTENT (26+POSITION_TIME)

#define DB_NAME	"chat.db"

struct account_st
{
	char id[4];
	char name[4];
	char passwd[8];
};

struct message_st
{
	struct account_st sender;
	struct account_st recver;
	char time[26];
	char content[128];
};

extern void show_account(struct account_st *account_ptr);
extern void show_message(struct message_st *message_ptr);

#endif
