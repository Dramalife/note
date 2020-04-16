/* establish --------- AS & Client
 * socket, listen
 * connect
 * send, recv
 */

/* random key -------- TGS & Client
 * srand, rand
 */

/* de/encrypy ----------- Key & DecMessage/Message
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


#define PORT_AS		8000
#define PORT_BOB	8001
#define PORT_TGS	8002
#define PORT_ALICE	8003

#define MESSAGE_SIZE	256

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
#if 0
struct packet_usr2as
{
int key_owner;//user
char tgt[];//key-TGS
char sk_tgs[];//key-usr
};
struct packet_usr2tgs
{
{//auth
//usr
//address
//start_time
//lifetime
};//key-SK_TGS <-
//TGT;//key-TGS// -> SK_TGS
};
struct packet_tgs2usr
{
SK_Service;//key:SK_TGS
SK_TGS;//
ST{usr,address,start_time,lifetime,SK_Service}K_Service;//key:service
};
#endif
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

enum
{
	K_MIN__,
	K_AS,
	K_TGS,
	K_ALICE,
	K_BOB,
	K_MAX__,
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
int trans_data_func(struct trans_data_s_st arg);
int send_message2sockserver(struct trans_data_c_st conn);
