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
//#include <ctype.h>

#include "lib_dramalife.h"

enum{
	PORT_AS=8000,
	PORT_TGS,
	PORT_SERVICE,
	PORT_BOB,
	PORT_ALICE,
};

#define MESSAGE_SIZE	4096//TODO !!!!!

#define debug_out(file,f,l,x,...)	do{printf("[%s,%s,%d]",file,f,l);printf(x,##__VA_ARGS__);}while(0)

struct message_t
{
	char send_msg[MESSAGE_SIZE];
	char recv_msg[MESSAGE_SIZE];
};

struct message_p
{
	int len;
	char *msg;
};
struct message_txrx_st
{
	struct message_p send;
	struct message_p recv;
#define TRANS_SEND	99
#define TRANS_RECV	88
	int trans_type;//1-tx
};
struct message_key
{
	int type;

};
struct trans_data_s_st
{
	int sockfd;
	int (*process_data)(struct message_txrx_st);
};
struct trans_data_c_st
{
	char *addr;
	int port;
	int (*process_data)(struct message_txrx_st);
};

#if 0
enum
{
	K_MIN__,
	K_AS,
	K_TGS,
	K_ALICE,
	K_BOB,
	K_MAX__,
};
#endif


/* kerberos protocol */
struct kerberos_cs_info_st
{
#define CLIENT_ID	33
#define SERVICE_NAME	"service-33"
#define CHAR_ARRAY_SIZE	64
#define SIZE_CLIENT_ADDR	CHAR_ARRAY_SIZE
#define SIZE_SERVICE_NAME	CHAR_ARRAY_SIZE
	pid_t client_id;//pid
	char client_address[SIZE_CLIENT_ADDR];
	char service_name[SIZE_SERVICE_NAME];//local port
	int time_stamp;
	int lisftime;
};
enum kerberos_key_type
{
	K_C	,
	K_S	,
	K_C_TGS	,
	K_C_S	,
	K_MAX__,
};
struct kerberos_key_st
{
	//	int type;
	enum kerberos_key_type type;
	int key;
};
typedef enum kerberos_message_type
{
	MSG_INIT__,
	MSG_REQUEST_TGT,// client -> as
	MSG_RETURNN_TGT,// as -> client
	MSG_REQUEST_SGT,// client -> sgt
	MSG_RETURNN_SGT,// sgt -> client
	MSG_REQUEST_SERVICE,//client -> service
	MSG_RETURNN_SERVICE,//service -> client
	MSG_FINISHED__,
}kerberos_stage;
struct kerberos_ticket_st
{
	struct kerberos_cs_info_st auth;
	struct kerberos_key_st key;
};
struct kerberos_message_st
{
	enum kerberos_message_type type;
	struct kerberos_key_st		key;
	struct kerberos_key_st		key2;
	struct kerberos_cs_info_st	cs_info;
	struct kerberos_ticket_st tgt_sgt;//tgt or sgt
};


int init_socket_server(int port_num);
int init_socket_client(struct sockaddr_in *addr_server);
int gen_key();
int isalpha_usr(char arg);
int isdigit_usr(char arg);
int isalpha_lower(char arg);
int isalpha_upper(char arg);
char *encode_usr(int key, char *plain, char *cipher);
char *decode_usr(int key, char *cipher, char *plain);
struct kerberos_key_st *get_key(enum kerberos_key_type type);
int trans_data_func(struct trans_data_s_st arg);
int send_message2sockserver(struct trans_data_c_st conn);
void kerberos_print_all(struct kerberos_message_st *msg);
