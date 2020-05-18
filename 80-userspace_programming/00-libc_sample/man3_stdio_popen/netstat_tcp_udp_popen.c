/*
 * note "pipe(2)/popen(3) & netstat(8)" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-99-generic #100-Ubuntu SMP Wed Apr 22 20:32:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Mon May 18 17:07:11 CST 2020
 *  	FORK FROM : note/80-userspace_programming/00-libc_sample/man3_stdio_popen/popen.c,
 * 		commit(0003f11bca078399607deb806669a6efbbbd8252);
 * Update : Mon May 18 17:07:11 CST 2020
 * 	popen("netstat -ant", "r"); 
 *  
 * Update
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***
 * Data struct
 */
struct netstat_context_port_st
{
#define PNST_SIZE_64 64
	char proto[PNST_SIZE_64];
	int recv;
	int send;
	char local[PNST_SIZE_64];
	char foreign[PNST_SIZE_64];
	char state[PNST_SIZE_64];
};

/***
 * Global variables
 */
#define NETSTAT_PORT_NUM_MAX	1024
int netstat_port_tcp_arr[NETSTAT_PORT_NUM_MAX] = {0};
int netstat_port_udp_arr[NETSTAT_PORT_NUM_MAX] = {0};

static void netstat_port_record_add(int arr_arg[], int port)
{
	int index = 0;
	for(index = 0; index < NETSTAT_PORT_NUM_MAX; index++)
	{
		if( port == arr_arg[index] )
		{
			return;
		}
	}
	for(index = 0; index < NETSTAT_PORT_NUM_MAX; index++)
	{
		if( 0 == arr_arg[index] )
		{
			arr_arg[index] = port;
			break;
		}
	}
}
static void netstat_port_record_debug_all(int arr_arg[])
{
	int index = 0;
	printf("%s,%d\n******port list******\n",__func__,__LINE__);
	for(index = 0; index < NETSTAT_PORT_NUM_MAX; index++)
	{
		if( 0 != arr_arg[index] )
			printf("%d\n",arr_arg[index]);
	}
}

static void debug_print_popen(struct netstat_context_port_st *data_p)
{
	printf("%s %d %d %s %s %s \n", \
			data_p->proto,\
			data_p->recv,\
			data_p->send,\
			data_p->local,\
			data_p->foreign,\
			data_p->state\
	      );
}
static int pipe_get_netstat_data(char *buff, struct netstat_context_port_st *data_p)
{
	return sscanf(buff,"%s %d %d %s %s %s", 
			data_p->proto,
			&data_p->recv,
			&data_p->send,
			data_p->local,
			data_p->foreign,
			data_p->state
		     );
}
static void get_net_port_pipe(const char *cmd, const char *keyw, int where_arr[])
{
#define SIZE_BUFF_POPEN	1024
	int cnt_sscanf = 0;
	char *buff = NULL;
	struct netstat_context_port_st data={0};
	FILE *fp = NULL;

	fp = popen(cmd,"r");
	if( NULL == (buff = (char *)malloc( SIZE_BUFF_POPEN * sizeof(char))) )
	{
		perror("malloc");
		exit(1);
	}
	memset(buff, 0, SIZE_BUFF_POPEN);

	while ( NULL != fgets(buff, SIZE_BUFF_POPEN, fp) )
	{
		if( NULL != strstr(buff, keyw) )
		{
			//printf("+++++++(%s)\n",buff);
			if( (cnt_sscanf = pipe_get_netstat_data(buff, &data)) > 0 )
			{
				//debug_print_popen(&data);
				char *tmp_ptr = NULL;
				tmp_ptr = strrchr(data.local, ':');
				//printf("%s \n", data.local);
				if(tmp_ptr)
				{
					tmp_ptr++;
					//printf("%s\n",tmp_ptr);
					netstat_port_record_add(where_arr, atoi(tmp_ptr));
				}
			}
		}
		memset(buff, 0, SIZE_BUFF_POPEN);
	}
	free(buff);
	pclose(fp);
}

int main(int argc, char **argv)
{
	get_net_port_pipe("netstat -ant", "tcp", netstat_port_tcp_arr);	
	get_net_port_pipe("netstat -anu", "udp", netstat_port_udp_arr);	

	netstat_port_record_debug_all(netstat_port_tcp_arr);
	netstat_port_record_debug_all(netstat_port_udp_arr);

	return 0;
}
