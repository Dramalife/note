/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   client
   Init	2019.08.11 COPY FROM /note/80-userspace_programming/com_unix_sock.
   Update 
   
   errno is thread-local;
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include "dlpi_common.h"

int main(void)
{
    int connect_fd;
    int ret;
    char snd_buf[1024];
    int i;

    static struct sockaddr_un serv_addr;
    struct stat stat_buf;

    ret = stat(DLPI_UNIX_PROCESS_MAIN, &stat_buf);

    if(ret < 0)
    {
	    perror("stat sockfile err!");
    }

    if( !S_ISSOCK(stat_buf.st_mode)
		    || 0
      )
    {
	    perror("not socket file!");
    }

    connect_fd=socket(PF_UNIX,SOCK_STREAM,0);
    if(connect_fd<0){
        perror("cannot create communication socket");
        return 1;
    }

    memset(&serv_addr,0,sizeof(struct sockaddr_un));
    serv_addr.sun_family=AF_UNIX;
    strcpy(serv_addr.sun_path,DLPI_UNIX_PROCESS_MAIN);

    ret=connect(connect_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret==-1){
        perror("cannot connect to the server");
        close(connect_fd);

        return 1;
    }//^FD


    memset(snd_buf,0,1024);
    strcpy(snd_buf,"xxxxxhahahahah");

    write(connect_fd,snd_buf,sizeof(snd_buf));

    while(1)
    {
    	int r_bytes = read(connect_fd,snd_buf,sizeof(snd_buf));
	if(r_bytes <= 0)
	{
		perror("read!");
		break;
	}
	else if(r_bytes <= 10)//TODO : ctl_struct_size
	{
		break;
	}
	else//DATA
	{
		if(0)//cmd err
		{
			break;
		}
	}
    }

    close(connect_fd);
    return 0;
}

