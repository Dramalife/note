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
	while(1)
	{
		uart_rx(arg);
		dprintf(1, "[%s,%d] INFO : rx thread... \n", __func__,__LINE__);
		sleep(2);
	}
}

int main(int argc, char **argv)
{
	int ret = 0;

	struct targ_rx_st data_rx;
	memset(&data_rx, 0, sizeof(struct targ_rx_st));
	pthread_mutex_t m_buff;
	pthread_mutex_init(&m_buff,NULL);

	DEV_RS232 znp;
	memset(&znp, 0, sizeof(znp));

	int tid_recv;

	/* Init Serial */
	librs232_init(&znp, ZPI_SERIAL_DEV, 500000);
	librs232_open(&znp, 115200);
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
	pthread_create((pthread_t *)&tid_recv, NULL, thread_serial_rx, (void *)&data_rx);
	dprintf(1, "[%s,%d] INFO : Create RX Thread finished! \n", __func__,__LINE__);

	while(1)
	{
		dprintf(1, "[%s,%d] INFO : main thread... \n", __func__,__LINE__);
		sleep(2);

	}

exit:
	/* Close Serial */
	librs232_close(&znp);
	return ret;
}
