/*
 * note "Zigbee - CC2530 ZNP API" related file
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
 * Init : Tue Aug 25 17:00:25 CST 2020
 *  * ;
 * Update : Tue Aug 25 17:00:25 CST 2020
 *  
 * Update
 *
 */



#include "zpi.h"


struct zpi_buff_st
{
	char *ptr;
	uint32_t offset;
};
struct targ_rx_st
{
	DEV_RS232 *dev;
	pthread_mutex_t *mutex;
	struct zpi_buff_st buff;
};


/*****
 * Init : 2020.08.25
 * 	COPY FROM : librs232.c - librs232_read;
 */
int uart_rx(struct targ_rx_st *arg)
{
	int size = SIZE_RX_BUFF;
	char *data = arg->buff.ptr;
	int *offset = &arg->buff.offset;
	DEV_RS232* dev = arg->dev;

	fd_set fds;
	struct timeval timeout;
	int count=0;
	int ret;
	int n;
	do {    
		FD_ZERO(&fds);
		FD_SET(dev->fd, &fds);
		timeout.tv_sec = 0;  
		timeout.tv_usec = dev->timeout;
		ret = select (dev->fd + 1, &fds, NULL, NULL, &timeout);
		if (ret > 0) {
			pthread_mutex_lock(arg->mutex);
			n = read (dev->fd, (data + count), size-count);
			count += n;
			data[count] = 0;
			*offset = count;
			pthread_mutex_unlock(arg->mutex);
		}
	} while ((count < size) && (ret == 1));

	return(count);
}

void *thread_serial_rx(void *argin)
{
	struct targ_rx_st *arg = (struct targ_rx_st *)argin;

	dprintf(1, "[%s,%d] INFO : Create RX Thread finished! \n", __func__,__LINE__);

	while(1)
	{
		uart_rx(arg);
		dprintf(1, "[%s,%d] INFO : rx thread... \n", __func__,__LINE__);
		sleep(2);
	}

	return NULL;
}

#if 1
struct oam_data_st
{
	int mod_id;
	unsigned short cmd_code;
	unsigned short datalen;
	char flags;
	char magic[7];
	char data[0];
};
enum{
	ZPI_CMD_TEST = 0,
	ZPI_CMD_SET_CONFIG,
	ZPI_CMD_GET_STATUS,
	ZPI_CMD_GET_SLAVES,
};
struct zigbee_config_st
{
	uint8_t		zc_switch;
	uint8_t		zc_panid;
	uint8_t		zc_channel;
};
#endif

void *thread_sock_server(void *argin)
{
#define LEN_SOCK_BUFF 	1024
	int sock_fd = 0;
	int len = 0;
	struct sockaddr_un srv_addr;
	struct sockaddr_un clt_addr;
	char *recv_buff = NULL, *send_buff=NULL;
	int acpt_fd = 0;
	int cnt_read = 0;

	struct oam_data_st *r_head = NULL;
	struct oam_data_st *s_head = NULL;

	dprintf(2, "[%s,%d] INFO : Thread (%s) start ...\n",__func__,__LINE__,__func__);

	if( NULL == (recv_buff = (char *)malloc( LEN_SOCK_BUFF * sizeof(char) )) )
	{
		dprintf(2, "[%s,%d] ERROR : malloc, (%s)\n ",__func__,__LINE__,strerror(errno));
		goto exit;
	}
	if( NULL == (send_buff = (char *)malloc( LEN_SOCK_BUFF * sizeof(char) )) )
	{
		dprintf(2, "[%s,%d] ERROR : malloc, (%s)\n ",__func__,__LINE__,strerror(errno));
		goto exit;
	}

start:
	unlink(ZPI_SOCKET_PATH);
	if( (sock_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0 )
	{
		dprintf(2, "[%s,%d] ERROR : socket, (%s)\n ",__func__,__LINE__,strerror(errno));
		goto exit;
	}
	srv_addr.sun_family=AF_UNIX;
	strncpy(srv_addr.sun_path, ZPI_SOCKET_PATH, sizeof(srv_addr.sun_path)-1);
	if( (bind(sock_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr))) == -1 )
	{
		dprintf(2, "[%s,%d] ERROR : bind, (%s)\n ",__func__,__LINE__,strerror(errno));
		close(sock_fd);
		goto exit;
	}

	if( listen(sock_fd, 1) == -1 )
	{
		dprintf(2, "[%s,%d] ERROR : malloc, (%s)\n ",__func__,__LINE__,strerror(errno));
		close(sock_fd);
		goto exit;
	}
	len=sizeof(clt_addr);

	while(1)
	{
		/* One client */
		if( (acpt_fd = accept(sock_fd,(struct sockaddr*)&clt_addr,&len)) < 0)
		{
			dprintf(2, "[%s,%d] ERROR : accept, (%s)\n ",__func__,__LINE__,strerror(errno));
			close(sock_fd);
			goto start;
		}

		memset(recv_buff, 0, LEN_SOCK_BUFF);
		cnt_read = read(acpt_fd, recv_buff, LEN_SOCK_BUFF);
		printf("buff:%s\n", recv_buff);
		r_head = recv_buff;

		int cmd_type = r_head->cmd_code;
		dprintf(2, "[%s,%d] CMD Type(%d) \n",__func__,__LINE__,cmd_type);
		switch(cmd_type)
		{
			case ZPI_CMD_TEST:
				break;

			case ZPI_CMD_SET_CONFIG:
				{
					// uart send
					// uart read

					// sock send
					memset(send_buff, 0, LEN_SOCK_BUFF);
					s_head = send_buff;
					s_head->cmd_code = r_head->cmd_code;
					cnt_read = write(acpt_fd, send_buff, LEN_SOCK_BUFF);
				}
				break;

			case ZPI_CMD_GET_STATUS:
				break;

			case ZPI_CMD_GET_SLAVES:
				break;

			default:
				{
					printf("%s,%d \n",__func__,__LINE__);
					memset(send_buff, 0, LEN_SOCK_BUFF);
					s_head = send_buff;
					s_head->cmd_code = r_head->cmd_code;
					sleep(2);
					cnt_read = write(acpt_fd, send_buff, LEN_SOCK_BUFF);
				}
				break;
		}

		close(acpt_fd);
	}

exit:
	unlink(ZPI_SOCKET_PATH);
	free(send_buff);
	free(recv_buff);
	return NULL;
}

int main(int argc, char **argv)
{
	int ret = 0;
	int tid_recv;
	int tid_sock;
	DEV_RS232 znp;
	struct targ_rx_st data_rx;

	signal(SIGPIPE, SIG_IGN);

	memset(&data_rx, 0, sizeof(struct targ_rx_st));
	pthread_mutex_t m_buff;
	pthread_mutex_init(&m_buff,NULL);

	memset(&znp, 0, sizeof(znp));

	/* Init Serial */
	librs232_init(&znp, ZPI_SERIAL_DEV, 500000);
	librs232_open(&znp, ZPI_BANDRATE);
	dprintf(1, "[%s,%d] INFO : Uart init done!\n", __func__,__LINE__);

	/* Serial RX Thread */
	data_rx.dev = &znp;
	data_rx.mutex = &m_buff;
	data_rx.buff.offset = 0;
	if( NULL == (data_rx.buff.ptr = (char *)malloc( SIZE_RX_BUFF * sizeof(char) ) ) )
	{
		dprintf(2, "[%s,%d] ERROR : malloc, (%s)\n ",__func__,__LINE__,strerror(errno));
		ret = errno;
		goto exit;
	}
	memset(data_rx.buff.ptr, 0, SIZE_RX_BUFF);
	//pthread_create((pthread_t *)&tid_recv, NULL, thread_serial_rx, (void *)&data_rx);

	/* Socket Server Thread */
	pthread_create((pthread_t *)&tid_sock, NULL, thread_sock_server, (void *)&data_rx);

	while(1)
	{
		//dprintf(1, "[%s,%d] INFO : main thread... \n", __func__,__LINE__);
		sleep(2);
	}

exit:
	/* Close Serial */
	librs232_close(&znp);
	return ret;
}
