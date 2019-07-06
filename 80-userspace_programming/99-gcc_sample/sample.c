/*
   note gcc sample related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include<stdio.h>

void word_size_include(void)
{
	const char *my_path = "#include <bits/wordsize.h>";
#if  __WORDSIZE ==  64

#elif  __WORDSIZE ==  32

#else

#endif

	printf("\"__WORDSIZE:%d\"  \nMy path : \"%s\"  \n",__WORDSIZE,  my_path);
	return;
}

int main(void)
{

	word_size_include();

	return 0;
}

