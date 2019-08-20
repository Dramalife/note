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

#include "http.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
Request parseRequest(char * buffer)
{
	Request req;
	char *head = NULL,**line = NULL,*temp=NULL;
	int i = 0, line_count = 0,head_count=0,index=0;
	req.accept = NULL;
	req.accept_Encoding = NULL;
	req.accept_Language = NULL;
	req.connection = NULL;
	req.host = NULL;
	req.method = NULL;
	req.file = NULL;
	req.user_Agent = NULL;
	//按行解析请求头
	line_count = countChar(buffer, '\n');
	line = (char **)malloc(line_count*sizeof(char *));
	for (i = 0; i < line_count; i++)
		line[i] = NULL;
	temp = strtok(buffer, "\n");
	i = 0;
	while (temp) {
		line[i] = (char *)malloc((strlen(temp)+1)*sizeof(char));
		strcpy(line[i++], temp);
		temp = strtok(NULL, "\n");
	}
	for (i = 0; i < line_count&&line[i]!=NULL; i++) {
		head = strtok(line[i], " ");
		if (strcmp(head, "GET")==0) {       //获取请求文件  暂时不解析参数
			temp = strtok(NULL, " ");
			index = indexOfStrFirst(temp, '?');
			if(index!=-1)
				temp[index] = '\0';
			req.file = (char *)malloc((strlen("/var/www/html")+strlen(temp) + 1));
			printf("length:%d\n",(strlen(temp) + 1));
			sprintf(req.file,"/var/www/html%s", temp);
		}else if (strcmp(head, "POST")==0) {    //获取请求文件  暂时不解析参数
			temp = strtok(NULL, " ");
			index = indexOfStrFirst(temp, '?');
			if(index!=-1)
				temp[index] = '\0';
			req.file = (char *)malloc((strlen(temp) + 1));
			strcpy(req.file, temp);
		}else if (strcmp(head, "Host:")==0) {
			printf("FN:%s\n",req.file);
			printf("LN:%d\n",strlen(req.file));
			temp = strtok(NULL, " ");
			req.host = (char *)malloc((strlen(temp) + 1));
			strcpy(req.host, temp);
			printf("FN:%s\n",req.file);
			printf("LN:%d\n",strlen(req.file));
		}else if (strcmp(head, "User-Agent:")==0) {
			temp = strtok(NULL, " ");
			req.user_Agent = (char *)malloc((strlen(temp) + 1));
			strcpy(req.user_Agent, temp);
		}else if (strcmp(head, "Accept:")==0) {
			temp = strtok(NULL, " ");
			req.accept = (char *)malloc((strlen(temp) + 1));
			strcpy(req.accept, temp);
		}else if (strcmp(head, "Accept-Language:")==0) {
			temp = strtok(NULL, " ");
			req.accept_Language = (char *)malloc((strlen(temp) + 1));
			strcpy(req.accept_Language, temp);
		}else if (strcmp(head, "Accept-Encoding:")==0) {
			temp = strtok(NULL, " ");
			req.accept_Encoding = (char *)malloc((strlen(temp) + 1));
			strcpy(req.accept_Encoding, temp);
		}else if (strcmp(head, "Connection:")==0) {
			temp = strtok(NULL, " ");
			req.connection= (char *)malloc((strlen(temp) + 1));
			strcpy(req.connection, temp);
		}
	}
	return req;
}

