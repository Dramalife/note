#include "pub.h"

void show_account(struct account_st *account_ptr)
{
	printf("Id(%s),Name(%s),Passwd(%s)\n"
			,account_ptr->id
			,account_ptr->name
			,"***"//,account_ptr->passwd
	      );
}
void show_message(struct message_st *message_ptr)
{
	printf("*****************start******************\n");
	printf("SENDER:\n");
	show_account( &(message_ptr->sender) );
	printf("RECVER:\n");
	show_account( &(message_ptr->recver) );
	printf("Time(%s)\nContent(%s)\n"
			,message_ptr->time
			,message_ptr->content
	      );
	printf("******************end*******************\n");

	return;
}

