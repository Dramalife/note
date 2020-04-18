#include "pub.h"

kerberos_stage mystage = MSG_INIT__;
struct kerberos_key_st k_c_tgs;
struct kerberos_ticket_st tgt;
struct kerberos_cs_info_st my_info={CLIENT_ID, {0}, SERVICE_NAME, 0, 0};

int handler_as(struct message_txrx_st data)
{

	struct kerberos_message_st *pkmessage_send = data.send.msg;
	struct kerberos_message_st *pkmessage_recv = data.recv.msg;
	switch(data.trans_type)
	{
		case TRANS_SEND:
			if( MSG_REQUEST_TGT ==  mystage )
			{
				pkmessage_send->type = mystage;
				pkmessage_send->cs_info.client_id = my_info.client_id;
				strncpy(pkmessage_send->cs_info.service_name, my_info.service_name, SIZE_SERVICE_NAME);
				//memcpy(data.send.msg, &kmessage, MESSAGE_SIZE);
				debug_out(__FILE__,__func__,__LINE__,"[SEND] TGT client(%d),service(%s) \n",
						pkmessage_send->cs_info.client_id,pkmessage_send->cs_info.service_name);
			}
			else if(MSG_REQUEST_SGT == mystage)
			{
				pkmessage_send->type = mystage;
				memcpy(&(pkmessage_send->cs_info), &my_info, sizeof(struct kerberos_cs_info_st));//a_c_tgs [cs_info]
				memcpy(&(pkmessage_send->tgt_sgt), &tgt, sizeof(struct kerberos_ticket_st));//tgt		[ticket_st]
				debug_out(__FILE__,__func__,__LINE__,"[SEND] SGT client(%d)\n", pkmessage_send->cs_info.client_id);
			}
			else
			{
				debug_out(__FILE__,__func__,__LINE__,"Unknown type! \n");
			}
			kerberos_print_all(pkmessage_send);
			break;
		case TRANS_RECV:
			if( MSG_RETURNN_TGT == pkmessage_recv->type)
			{
				debug_out(__FILE__,__func__,__LINE__,"[RECV] TGT type(%d),k_c_tgs(%d) \n", pkmessage_recv->type, pkmessage_recv->key.key);
				debug_out(__FILE__,__func__,__LINE__,"Parsing TGT! KC_TGS\n");
				memcpy(&k_c_tgs, &(pkmessage_recv->key), sizeof(struct kerberos_key_st));//decrpyt  k_c_tgs
				memcpy(&tgt, &(pkmessage_recv->tgt_sgt), sizeof(struct kerberos_ticket_st));
				mystage = MSG_REQUEST_SGT;
			}
			else if(MSG_RETURNN_SGT == pkmessage_recv->type)
			{
				debug_out(__FILE__,__func__,__LINE__,"[RECV] TGS type(%d),k_c_tgs(%d) \n", pkmessage_recv->type, pkmessage_recv->key.key);
				mystage = MSG_REQUEST_SERVICE;
			}
			else
			{
				debug_out(__FILE__,__func__,__LINE__,"Unknown type! \n");
			}
			kerberos_print_all(pkmessage_recv);
			printf("\n\n");
			break;
		default:
			while(1)
			{}
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
		switch(mystage)
		{
			case MSG_INIT__:
				mystage = MSG_REQUEST_TGT;
				break;
			case MSG_REQUEST_TGT:
				send_message2sockserver(data_as);
				break;
			case MSG_RETURNN_TGT://////////////////////
				break;
			case MSG_REQUEST_SGT:
				send_message2sockserver(data_as);
				break;
			case MSG_RETURNN_SGT://////////////////////
				break;
			case MSG_REQUEST_SERVICE:
				while(1)
				{}
				break;
			case MSG_RETURNN_SERVICE://////////////////
				break;
		}

		sleep(1);
	}

	debug_out(__FILE__,__func__,__LINE__,"\n");

	return 0;
}
