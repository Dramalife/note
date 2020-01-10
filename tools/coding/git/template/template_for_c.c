/*
 * note "coding template for note*" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * TODO;
 * 
 * $ uname -a
 * TODO;
 * 
 * Init : 2020.01.09
 *	Sample stage;
 * Update 
 *
 */



#include <stdio.h>
#include <unistd.h>

typedef enum cm_index{
	INDEX_TITLE=0,
	INDEX_GCCVER	,
	INDEX_UNAME	,
	INDEX_INIT_	,
	INDEX_UPDATE_	,
	INDEX_MAX
}cm_index;
struct cm_insert
{
	cm_index index;
	char *str;
	unsigned char flag;//0x01-need_free
};

char *str[]={
	"/*\n"
		" * note \"",/*TITLE*/"\" related file\n"
		" * Copyright (C) 2019 Dramalife <dramalife@live.com>\n"
		" * \n"
		" * This file is part of [note](https://github.com/Dramalife/note.git)\n"
		" * \n"
		" * note is distributed in the hope that it will be useful, but\n"
		" * WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
		" *\n"
		" * $ gcc --version\n"
		" * ",/*GCC*/";\n"
		" * \n"
		" * $ uname -a\n"
		" * ",/*UNAME*/";\n"
		" * \n"
		" * Init : ",/*DATE,EVENTS*/";\n"
		" * Update"
		" : ",/*DATE,EVENTS*/ " \n * Update"
		"\n"
		" *\n"
		" */\n"
		,NULL
};

struct cm_insert data_insert[]={
	{ INDEX_TITLE	, NULL, 0x00 },
	{ INDEX_GCCVER	, NULL, 0x00 },
	{ INDEX_UNAME	, NULL, 0x00 },
	{ INDEX_INIT_	, NULL, 0x00 },
	{ INDEX_UPDATE_	, NULL, 0x00 },
	{ INDEX_MAX	, NULL, 0x00 },
};

#define DEBUG_PRINT0(i,x)	do{if(i == x)	\
	printf("%s",#x);}while(0)
void show_dynamic(cm_index index)
{
#if 0
	DEBUG_PRINT0(index, INDEX_TITLE		);
	DEBUG_PRINT0(index, INDEX_GCCVER	);
	DEBUG_PRINT0(index, INDEX_UNAME		);
	DEBUG_PRINT0(index, INDEX_INIT_		);
	DEBUG_PRINT0(index, INDEX_UPDATE_	);
#else
	if(index < INDEX_MAX)
	{
		printf("%s"
				,data_insert[index].str?data_insert[index].str:"NULL"
		      );
	}
#endif
	return;
}
void show_finish(char *str[])
{
	cm_index index = INDEX_TITLE;

	for(index = 0;str[index]!=NULL;index++)
	{
		printf("%s",str[index]);
		show_dynamic(index);
	}
}

void main()
{
	show_finish(str);
}
