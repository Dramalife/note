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
int countChar(char *str, char c); //ͳ��һ���ַ�����ĳ���ַ��ĸ���
int indexOfStrFirst(char *str, char c); //��ѯ�ַ��״γ��ֵ�λ��
char *getFileType(const char *filename);    //��ȡ��Ӧ��HTML����Ӧͷ���ļ�����
int getFileSize(const char *filename);      //��ȡ�ļ���С
