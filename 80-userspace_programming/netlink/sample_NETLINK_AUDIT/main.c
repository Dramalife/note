/*
 * note "audit" related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-66-generic #75-Ubuntu SMP Tue Oct 1 05:24:09 UTC 2019 
 * x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : 2019.11.02
 *	redefine function "audit_msg"
 * ;
 *
 * Update 
 *
 */



#include <stdio.h>
#include "log.h"


/* 
 * netlink core functions
 * 	Lib	: libaudit.so
 * 	Source	: src/netlink.c
 * 	Header	: none
 */
extern int audit_open(void);
extern void audit_close(int fd);
extern int audit_get_reply(int fd, struct audit_reply *rep, reply_t block, int peek);
extern static int adjust_reply(struct audit_reply *rep, int len);
extern int audit_send(int fd, int type, const void *data, unsigned int size);
extern static int check_ack(int fd);


/*
 * Replaced functions
 */
//audit_msg() > printf()


static int fd = -1;


int main(void)
{
	audit_msg(NULL,0,"%s,%d \n",__func__,__LINE__);

	//singal

	if ( (fd = audit_open()) < 0 )
	{
		audit_msg(NULL,0,"%s,%d can not open netlink \n",__func__,__LINE__);
	}
	
	//bind?

	while(1)
	{

	}

	audit_close(fd);

	return 0;
}
