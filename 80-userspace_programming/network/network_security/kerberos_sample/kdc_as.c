#include "pub.h"

kerberos_stage mystagt = MSG_RETURNN_TGT;

int process_as(struct message_txrx_st data)
{
	//debug_out(__FILE__,__func__,__LINE__,"[RECV]:[%s] \n", data.recv.msg);
	//sprintf(data.send.msg, "----%s----",__FILE__);
	struct kerberos_message_st *pkmessage_recv = data.recv.msg;
	struct kerberos_message_st *pkmessage_send = data.send.msg;
	switch(mystagt)
	{
		case MSG_INIT__:////////////////
			break;
		case MSG_REQUEST_TGT:///////////
			break;
		case MSG_RETURNN_TGT:
			kerberos_print_all(pkmessage_recv);
			if( MSG_REQUEST_TGT == pkmessage_recv->type )
			{
				debug_out(__FILE__,__func__,__LINE__,"[RECV] TGT \n");
				struct kerberos_key_st *kc = get_key(K_C);
				struct kerberos_key_st *kc_tgs = get_key(K_C_TGS);//k_c_tgs
				struct kerberos_key_st e_kc_kc_tgs;
				struct kerberos_ticket_st *p_tgt = &(pkmessage_send->tgt_sgt);
				memcpy(&e_kc_kc_tgs, kc_tgs, sizeof(struct kerberos_key_st));//encode_usr(kc->key, (char *)kc_tgs->key, &(e_kc_kc_tgs.key));// e k_c_tgs
				memcpy(&(p_tgt->auth), &(pkmessage_recv->cs_info), sizeof(struct kerberos_cs_info_st));//tgt->auth
				memcpy(&(p_tgt->key), kc_tgs, sizeof(struct kerberos_key_st));//tgt->key
				memcpy(&pkmessage_send->key, &e_kc_kc_tgs, sizeof(struct kerberos_key_st));
				//e p_tgt
				pkmessage_send->type = MSG_RETURNN_TGT;
				debug_out(__FILE__,__func__,__LINE__,"[SEND] TGT key(%d) \n",pkmessage_send->key.key);
				kerberos_print_all(pkmessage_send);
				mystagt = MSG_RETURNN_SGT;
			}
			break;
		case MSG_REQUEST_SGT://///////
			break;
		case MSG_RETURNN_SGT:
			kerberos_print_all(pkmessage_recv);
			if( MSG_REQUEST_SGT== pkmessage_recv->type)
			{
				debug_out(__FILE__,__func__,__LINE__,"[RECV] SGT. \n");
				//a_c_tgs
				//tgt
				if( pkmessage_recv->cs_info.client_id == pkmessage_recv->tgt_sgt.auth.client_id )
				{
					debug_out(__FILE__,__func__,__LINE__,"Client ID check passed ! \n");
				}
				else
				{
					debug_out(__FILE__,__func__,__LINE__,"Client ID check failed ! \n");
					break;
				}
				/* Send */
				struct kerberos_key_st *k_c_s = get_key(K_C_S);
				struct kerberos_key_st *e_k_ctgs_kcs = &(pkmessage_send->key);
				struct kerberos_ticket_st *sgt = &(pkmessage_send->tgt_sgt);
				memcpy(e_k_ctgs_kcs, k_c_s, sizeof(struct kerberos_key_st));//encrypt k_c_s
				memcpy(&(sgt->auth),&(pkmessage_recv->tgt_sgt.auth), sizeof(struct kerberos_cs_info_st) );
				memcpy(&(sgt->key), k_c_s, sizeof(struct kerberos_key_st));
				pkmessage_send->type = MSG_RETURNN_SGT;
				debug_out(__FILE__,__func__,__LINE__,"[SEND] SGT key(%d) \n",pkmessage_send->key.key);
				kerberos_print_all(pkmessage_send);
				mystagt = MSG_FINISHED__;
			}
			break;
		case MSG_REQUEST_SERVICE:
			break;
		case MSG_RETURNN_SERVICE:
			break;
		default:
			debug_out(__FILE__,__func__,__LINE__,"KDC task finished! \n");
			while(1)
			{}
			break;

	}
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
