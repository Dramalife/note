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
 * Update : 2020.01.10
 *	Get dynamic data (using popen) successfully;
 *	Make Command : gcc template_for_c.c -I ~/note/lib_dramalife/ ~/note/lib_dramalife/ipc_lib/build/obj/ipc_lib_pipe.o
 *	To enable debug print of lib_popen, Add "CFLAGS+=-DDRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_SW=1" to ~/note/lib_dramalife/ipc_lib/config.mk
 * Update 
 *
 */
#define DO_USE_DRAMALIFE_LIB	1
#ifdef DO_USE_DRAMALIFE_LIB
#if 1 == DO_USE_DRAMALIFE_LIB
#define USING_DL_LIB
#else
#undef USING_DL_LIB
#error NOT SUPPORTED YET!
#endif
#endif



#include <stdio.h>
#include <unistd.h>
#ifdef USING_DL_LIB
#include "lib_dramalife.h"
#endif

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
		" * Init : ",/*DATE,EVENTS*/" * ;\n"
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
#if 0
		printf("%s"
				,data_insert[index].str?data_insert[index].str:"NULL"
		      );
#else
		if( data_insert[index].str )
		{
			int i = 0;
			char *ptr = data_insert[index].str;
			char cc = *(ptr + 0);

			for(;*(ptr+i);i++)
			{
			printf("%c", *(ptr+i));
			if('\n'==*(ptr+i))
				printf(" * ");
			}
		}
		else
		{
			printf("NULL");
		}
#endif

		if(data_insert[index].flag & 0x01)
		{
			free(data_insert[index].str);
		}
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

//index, command, size
#define DO_INIT_DYNAMIC(i,c,s)	do{			\
	data[i].str = (char *)malloc(s * sizeof(char));\
	data[i].flag |= 0x01;\
	dramalife_get_cmd_result(c,"r",data[i].str);	\
}while(0)
void show_init(struct cm_insert data[])
{
	DO_INIT_DYNAMIC(INDEX_INIT_, "date", 128);
	DO_INIT_DYNAMIC(INDEX_UPDATE_, "date", 128);
	DO_INIT_DYNAMIC(INDEX_GCCVER, "gcc --version", 1024);
	DO_INIT_DYNAMIC(INDEX_UNAME, "uname -a", 1024);
}
void main()
{
	show_init(data_insert);
	show_finish(str);
}
