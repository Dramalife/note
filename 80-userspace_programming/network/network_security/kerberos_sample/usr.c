#include "pub.h"

int handler_as(struct message_txrx_st data)
{
	switch(data.trans_type)
	{
		case TRANS_SEND:
			snprintf(data.send.msg, data.send.len, "P1:alice");
			break;
		case TRANS_RECV:
			debug_out(__FILE__,__func__,__LINE__,"[RECV]:[%s] \n", data.recv.msg);
			break;
		default:
			break;
	}
	return 0;
}
int handler_tgs(struct message_txrx_st data)
{
	switch(data.trans_type)
	{
		case TRANS_SEND:
			snprintf(data.send.msg, data.send.len, "P2:alice");
			break;
		case TRANS_RECV:
			debug_out(__FILE__,__func__,__LINE__,"[RECV]:[%s] \n", data.recv.msg);
			break;
		default:
			break;
	}
	return 0;
}

int main(int argc, char **argv)
{
	struct trans_data_c_st data_as = { "127.0.0.1", PORT_AS, handler_as};
	struct trans_data_c_st data_tgs = { "127.0.0.1", PORT_TGS, handler_tgs };
	while(1)
	{
		// stage as
		send_message2sockserver(data_as);
		// stage tgs
		send_message2sockserver(data_tgs);
		//printf("key(%d)\n",gen_key());

		sleep(1);
	}

	debug_out(__FILE__,__func__,__LINE__,"\n");

	return 0;
}
