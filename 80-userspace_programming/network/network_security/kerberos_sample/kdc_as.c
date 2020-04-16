#include "pub.h"

int process_as(struct message_txrx_st data)
{
	debug_out(__FILE__,__func__,__LINE__,"[RECV]:[%s] \n", data.recv.msg);
	sprintf(data.send.msg, "----%s----",__FILE__);
	return 0;
}

int main(int argc, char **argv)
{
	int sock_fd = -1;

	/* Socket.Create(8000); //PORT_AS == 8000 */
	while( -1 == (sock_fd = init_socket_server(PORT_AS)) )
	{
		debug_out(__FILE__,__func__,__LINE__,"Init socket failed! (%s)\n", strerror(errno));
		sleep(2);
	}

	struct trans_data_s_st data = {sock_fd, process_as};
	while(1)
	{
		trans_data_func(data);
	}

	close(sock_fd);

	return 0;
}
