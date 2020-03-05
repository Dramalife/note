/*
 * note "data storage" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
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
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-74-generic #84-Ubuntu SMP Thu Dec 19 08:06:28 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Thu Mar  5 19:16:09 CST 2020
 * 	ex. Storage float variable to array that has unsigned char type ;
 * Update
 *
 */



#include <string.h>
#include <stdio.h>

unsigned char buff[4] = {0};

/*
 *d : data(type : int, float ...)
 *p : pointer point to data
 *b : buffer(array)
 *l : sizeof(data)
 */
#define data2array(d, b, l)	do{memset(b, 0, l); memcpy(b, &d, l);}while(0)
#define array2data(p, b, l)	do{memcpy(p, b, l);}while(0)

void main(void)
{
	int idata_int = 9;
	int odata_int = 0;
	data2array( idata_int, buff, sizeof(int));
	array2data(&odata_int, buff, sizeof(int));
	printf("%d \n", odata_int);

	float idata_float = 9.9;
	float odata_float = 0;
	data2array( idata_float, buff, sizeof(float));
	array2data(&odata_float, buff, sizeof(float));
	printf("%f \n", odata_float);
}

