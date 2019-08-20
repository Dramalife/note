/*
 * note network http related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Ref Url : https://blog.csdn.net/g1418377085/article/details/76994218
 * Ref Url2 : https://www.cnblogs.com/dancheblog/p/4126258.html
 *
 * Init : 2019.08.19, COPY FROM https://blog.csdn.net/g1418377085/article/details/76994218
 * Update : 2019.08.19, support inet6
 * Update  
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <pthread.h>
#include "http.h"

#define BUFFER_SIZE 1024

//处理用户的连接的线程方法
void *handle(void *arg){
	int conn = *((int *)arg),i=0,j=0,len=0;
	char buffer[BUFFER_SIZE];
	char *buf = NULL;
	char temp[1024];
	int fp = -1;
	int count = 0;
	int flag = 0;
	//需要优化
	while(1){
		memset(buffer,0,sizeof(buffer));
		len = recv(conn, buffer, sizeof(buffer),0);
		if (buf == NULL) {
			buf = (char *)malloc(BUFFER_SIZE);
		}else {
			buf = (char *)realloc(buf, (i + 1)*BUFFER_SIZE);
		}
		for (j = 0; j < BUFFER_SIZE; j++) {
			buf[i*BUFFER_SIZE + j] = buffer[j];
			if(buffer[j]==13&&buffer[j+1]==10&&buffer[j+2]==13&&buffer[j+3]==10&&j<BUFFER_SIZE-4){
				flag = 1;
			}
		}
		if(flag)
			break;
	}
	printf("%s\n\n",buf);
	Request res = parseRequest(buf);
	free(buf);
	//处理请求文件  发送数据
	//发送状态码  (用字符串链接)
	len = strlen("HTTP/1.1 200 OK\r\nConnection: close\r\nAccept-Ranges: bytes\r\n")+1;
	buf = (char *)malloc(sizeof(char)*len);
	strcpy(buf,"HTTP/1.1 200 OK\r\nConnection: close\r\nAccept-Ranges: bytes\r\n");
	sprintf(temp,"Content-Type: %s\r\n", getFileType(res.file));
	len += strlen(temp);
	buf = (char *)realloc(buf,sizeof(char)*len);
	strcat(buf,temp);
	printf("filename: %s\n", res.file);
	printf("Content-Length: %d\n", getFileSize(res.file));
	sprintf(temp, "Content-Length: %d\r\n\r\n", getFileSize(res.file));
	len += strlen(temp);
	buf = (char *)realloc(buf,sizeof(char)*len);
	strcat(buf,temp);
	//二进制发送文件
	fp = open(res.file,O_RDONLY);
	while (1) {
		i = read(fp,temp,sizeof(temp));
		if (i <= 0)
			break;
		buf = (char *)realloc(buf,sizeof(char)*(len+i));
		memcpy(&buf[len], temp, i);
		len+=i;
	}
	close(fp);
	buf = (char *)realloc(buf,sizeof(char)*(len+4));
	memcpy(&buf[len], "\r\n", 2);
	send(conn, buf, (len+2), 0);
	printf("finish\n");
	close(conn);//关闭连接
}

int main(int argc,char *argv[]){
#if USE_XXX_IPV6
	struct sockaddr_in6 client_addr;
	struct sockaddr_in6 server_sockaddr;
#else
	struct sockaddr_in client_addr;     //获取客户机信息
	struct sockaddr_in server_sockaddr;
#endif
	socklen_t length = sizeof(client_addr); //类型大小
	pthread_t *thread = NULL;       //处理事务线程
	int conn,*temp=NULL,err=0;
#if USE_XXX_IPV6
	int httpServerFd = socket(AF_INET6,SOCK_STREAM,0);
#else
	int httpServerFd = socket(AF_INET,SOCK_STREAM,0);
#endif
	int   opt   =   1; 
	setsockopt(httpServerFd,   SOL_SOCKET,   SO_REUSEADDR, &opt, sizeof(int));
#if USE_XXX_IPV6
	server_sockaddr.sin6_family = AF_INET6;
	server_sockaddr.sin6_port = htons(atoi(argv[1]));
	server_sockaddr.sin6_addr = in6addr_any;//TODO
#else
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(atoi(argv[1]));
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
#endif
	if(bind(httpServerFd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1){
		printf("绑定失败!\n");
		return 0;   
	}    
	///listen，成功返回0，出错返回-1
	if(listen(httpServerFd,10) == -1){
		printf("监听失败!\n");
		return 0;   
	}

	while(1){
		///成功返回非负描述字，出错返回-1
		conn = accept(httpServerFd, (struct sockaddr*)&client_addr, &length);
		if(conn==-1){
			printf("客户机连接出错!\n");
			return 0;
		}
		temp = (int *)malloc(sizeof(int));
		*temp = conn;
		thread = (pthread_t *)malloc(sizeof(pthread_t));
		err = pthread_create(thread,NULL,handle,(void *)temp);  
		if(err != 0 ){  
			printf("create thread fail\n");
		}  
	}

}

