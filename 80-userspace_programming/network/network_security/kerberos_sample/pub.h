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
struct message_server_st
{
	struct message_p send;
	struct message_p recv;
};
struct trans_data_st
{
	int sockfd;
	//struct sockaddr *addr_c;
	//socklen_t *accept_l;
	//struct message_p send;
	//struct message_p recv;
	int (*process_data)(struct message_server_st);
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
int trans_data_func(struct trans_data_st arg);
