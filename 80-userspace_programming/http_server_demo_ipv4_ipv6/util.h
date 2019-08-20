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
int countChar(char *str, char c); //统计一串字符串中某个字符的个数
int indexOfStrFirst(char *str, char c); //查询字符首次出现的位置
char *getFileType(const char *filename);    //获取对应的HTML的响应头的文件类型
int getFileSize(const char *filename);      //获取文件大小
