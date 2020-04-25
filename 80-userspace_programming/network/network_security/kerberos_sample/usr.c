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



#include "pub.h"

kerberos_stage mystage = MSG_INIT__;
struct kerberos_key_st k_c_tgs;
struct kerberos_key_st k_c_s;
struct kerberos_ticket_st tgt;
struct kerberos_ticket_st sgt;
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
				debug_out(__FILE__,__func__,__LINE__,"[SEND] TGT request, client(%d),service(%s) \n",
						pkmessage_send->cs_info.client_id,pkmessage_send->cs_info.service_name);
			}
			else if(MSG_REQUEST_SGT == mystage)
			{
				pkmessage_send->type = mystage;
				memcpy(&(pkmessage_send->cs_info), &my_info, sizeof(struct kerberos_cs_info_st));//a_c_tgs [cs_info]
				memcpy(&(pkmessage_send->tgt_sgt), &tgt, sizeof(struct kerberos_ticket_st));//tgt		[ticket_st]
				debug_out(__FILE__,__func__,__LINE__,"[SEND] SGT request, client(%d)\n", pkmessage_send->cs_info.client_id);
			}
			else if(MSG_REQUEST_SERVICE == mystage)
			{
#ifdef TEST_ERROR
				pkmessage_send->type = mystage + 1;
#else
				pkmessage_send->type = mystage;
#endif
				memcpy(&(pkmessage_send->cs_info), &my_info, sizeof(struct kerberos_cs_info_st));//A_C_S
				memcpy(&(pkmessage_send->tgt_sgt), &sgt, sizeof(struct kerberos_ticket_st));//SGT
				debug_out(__FILE__,__func__,__LINE__,"[SEND] Service request, client(%d)\n", pkmessage_send->cs_info.client_id);
			}
			else
			{
				debug_out(__FILE__,__func__,__LINE__,"Unknown type! \n");
			}
			kerberos_print_all(pkmessage_send);
			break;
		case TRANS_RECV:
			kerberos_print_all(pkmessage_recv);
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
				memcpy(&k_c_s, &(pkmessage_recv->key), sizeof(struct kerberos_key_st));//decrpyt  k_c_tgs
				memcpy(&sgt, &(pkmessage_recv->tgt_sgt), sizeof(struct kerberos_ticket_st));
				mystage = MSG_REQUEST_SERVICE;
			}
			else if(MSG_RETURNN_SERVICE == pkmessage_recv->type)
			{
				debug_out(__FILE__,__func__,__LINE__,"[RECV] SERVICE type(%d),k_c_tgs(%d) \n", pkmessage_recv->type, pkmessage_recv->key.key);
				debug_out(__FILE__,__func__,__LINE__,"The connection to the server is complete! \n");
				printf("##############END############\n");
			}
			else
			{
				debug_out(__FILE__,__func__,__LINE__,"Unknown type! \n");
			}
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
	//struct trans_data_c_st data_tgs = { "127.0.0.1", PORT_TGS, handler_tgs };
	//struct trans_data_c_st data_tgs = { "127.0.0.1", PORT_SERVICE, handler_tgs };
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
				send_message2sockserver(data_as);// TGS
				break;
			case MSG_RETURNN_SGT://////////////////////
				break;
			case MSG_REQUEST_SERVICE:
				send_message2sockserver(data_as);// Service
				while(1)
				{
				}
				break;
			case MSG_RETURNN_SERVICE://////////////////
				break;
		}

		sleep(1);
	}

	debug_out(__FILE__,__func__,__LINE__,"\n");

	return 0;
}
