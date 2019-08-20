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

#include "config.h"
#pragma once
typedef struct req {
	char *method;           //请求方式
	char *file;             //请求文件
	char *host;             //主机名称
	char *accept;           //请求文件类型
	char *accept_Language;  //请求语言
	char *accept_Encoding;  //客户端支持编码
	char *connection;       //链接状态
	char *user_Agent;       //用户环境
	//form表单 暂不处理
}Request;
Request parseRequest(char *buffer);     //根据请求头构造请求信息
