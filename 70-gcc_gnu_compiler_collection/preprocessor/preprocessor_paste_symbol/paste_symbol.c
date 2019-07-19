/*
   note gcc preprocess related file
   Copyright (C) 2019 Dramalife

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   Ref Url : https://www.runoob.com/cprogramming/c-preprocessors.html
   Init	: 2019.07.19
*/
#include <stdio.h>

#define tokenpaster(n) printf ("token" #n " = %d\n", token##n)

#define show_name_value(v) do{ printf("name:%s,value:%d\n",#v, v); }while(0)
#define show_name_value2(v) show_handle(#v,v)

void show_handle(const char *name,int value)
{
	printf("name:%s,value:%d\n",name,value);
}

int main(void)
{
	int token34 = 40;

	int test_haha = 6;
	int atest_haha = 8;

	tokenpaster(34);
	show_name_value(test_haha);
	show_name_value2(atest_haha);
	return 0;
}

