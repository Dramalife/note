#include "pub.h"

int send_to_as(char *arg_addr, int arg_port, struct message_t *msg_ptr)
{
	int sock_fd = -1;
	struct sockaddr_in addr_server;

	memset(&addr_server, 0, sizeof(struct sockaddr_in));

	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(arg_port);// PORT-Server
	addr_server.sin_addr.s_addr = inet_addr(arg_addr);// IP-Server

	while(-1 == (sock_fd = init_socket_client(&addr_server)) )
	{
		//perror("Connect to server failed!");
		return -1;
	}

	if( -1 == send(sock_fd, msg_ptr->send_msg, MESSAGE_SIZE, 0) )
		perror("send");

	if( -1 == recv(sock_fd, msg_ptr->recv_msg, MESSAGE_SIZE, 0) )
		perror("recv");

	close(sock_fd);
	return 0;
}

int main(int argc, char **argv)
{
	struct message_t msg;

	while(1)
	{
		memset(&msg, 0, sizeof(msg));
		sprintf(msg.send_msg, "P1:%s", "alice");
		if( 0 == send_to_as("127.0.0.1", PORT_AS, &msg) )
		{
			debug_out(__FILE__,__func__,__LINE__,"[RECV]:[%s] \n", msg.recv_msg);
		}

		memset(&msg, 0, sizeof(msg));
		sprintf(msg.send_msg, "P2:%s", "alice");
		if( 0 == send_to_as("127.0.0.1", PORT_TGS, &msg) )
		{
			debug_out(__FILE__,__func__,__LINE__,"[RECV]:[%s] \n", msg.recv_msg);
		}
		//printf("key(%d)\n",gen_key());

		sleep(1);
	}

	debug_out(__FILE__,__func__,__LINE__,"\n");

	return 0;
}
