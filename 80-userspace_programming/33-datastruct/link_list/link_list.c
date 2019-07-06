/*
   note datastruct linklist related file
   Copyright (C) 2019 Dramalife

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

TODO : 
[2019.06.26]	If already exist an item, which name is same as the item to be added.
[2019.07.02]	Fix bug :  Function "find_if_down2up" can not find the last item;
			   Function "chg_if_down2up" del the last item cause fault;
		Chg name:  var "struct if_down2up -> last  >> priv";
[2019.07.04]	Chg name:  func "find_if_down2up >> find_by_name_down2up";
		Add func:  "goto_end_down2up";
			   "test_func_down2up";
 */

#define AUTO_TEST_DOWN2UP	1

#define MAX_ITEM_NUM_DOWN2UP	256

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#if AUTO_TEST_DOWN2UP
#include <unistd.h>/* sleep() */
#include <time.h>/* time_t time(time_t *t); */
#endif

#include "terminal_color_dramalife.h"/* Installed from "note/lib_dramalife" */
//#include "../datastruct_dramalife.h"
struct if_down2up
{
       char name[20];
       int address_type;
       struct if_down2up *next;
       struct if_down2up *priv;
};



#define AC_NONE		CNONE
#define AC_LRED		CLRED
#define AC_LGREEN	CLGREEN
#define AC_YELLOW	CYELLOW

struct if_down2up *head;
void debug_if_down2up(struct if_down2up *st);
struct if_down2up *add_if_down2up(struct if_down2up *st, const char *name, int type);
struct if_down2up *find_by_name_down2up(struct if_down2up *st, const char*name);
int chg_if_down2up(struct if_down2up *st, const char *name, int type);

struct if_down2up *goto_end_down2up(struct if_down2up *st);

int find_by_fifo_down2up(struct if_down2up *st, struct if_down2up *ret_val);/* Get the oldest item */
int find_by_filo_down2up(struct if_down2up *st, struct if_down2up *ret_val);/* Get the newst  item */

int main(void)
{
	struct if_down2up tmp;

	head = add_if_down2up(NULL, NULL, 0);/* Init a linklist */
	debug_if_down2up(head);//should not print
	printf("LINE:%d................\n",__LINE__);

	/*head =*/ add_if_down2up(head,"aaaa", 1111);/* Add item to the linklist */
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);
#if 0
	/*head =*/ add_if_down2up(head,"bbbb", 2222);
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);
#endif
	chg_if_down2up(head,"aaaa",3333);/* Change value of item of the linklist */
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	chg_if_down2up(head,"aaaa",-1);/* Delete item of the linklist */
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	/*head = */add_if_down2up(head,"aaaa", 666);
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	/* Add some items */
	int i;
	for(i = 0;i < 10; i++)
	{
		char nameaaa[20];
		sprintf(nameaaa,"eman%d",i);
		add_if_down2up(head,nameaaa, i);
	}
	debug_if_down2up(head);/* Print out all item(s) */

	if( 0 == find_by_fifo_down2up(head, &tmp) )
		printf("FIFO---name:%s,type:%d\n",tmp.name, tmp.address_type);
	debug_if_down2up(head);

	if( 0 == find_by_filo_down2up(head, &tmp) )
		printf("FILO---name:%s,type:%d\n",tmp.name, tmp.address_type);
	debug_if_down2up(head);

	return 0;
}

#if AUTO_TEST_DOWN2UP
void test_func_down2up(struct if_down2up *st, int times, int interval)
{
	while(times--)
	{
		sleep(interval);
		if( (int)time(NULL) & 0x1 )
		{
			add_if_down2up(head,"aaaa", (int)time(NULL));/* Add item to the linklist */
		}
		else
		{
			chg_if_down2up(head,"aaaa",-1);/* Delete item of the linklist */
		}
		debug_if_down2up(head);
	}
}
#else
void test_func_down2up(struct if_down2up *st, int times, int interval);
#endif

/* Debug func, print all item(s) of the linklist */
void debug_if_down2up(struct if_down2up *st)
{
	struct if_down2up *tmp = st;
	printf("[%4d],priv:%d,next:%d SHOW\n" ,__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 );
	while(tmp->priv != NULL)
	{
		tmp = tmp->priv;
		printf("going to HEAD...\n");
	}//goto HEAD
	while(tmp->next != NULL)////while(tmp->next != NULL);
	{
		if(tmp->priv != NULL)//HEAD
		{
			printf("name:%s,type:%d \n", tmp->name, tmp->address_type);
		}
		else
		{
			printf("do not print HEAD \n");
		}
		tmp = tmp->next;
	}
	printf("name:%s,type:%d \n", tmp->name, tmp->address_type);
}

/* FUNC   : struct if_down2up *goto_end_down2up(struct if_down2up *st);
 * ARGIN  : A pointer of the link_list.
 * RETURN : The function return a pointer to the ending of the link_list,or NULL
 * 		if the ending is not found or 
 * 		the size of the link_list is bigger than MAX_ITEM_NUM_DOWN2UP;
 * ADDDATE: 2019.07.04;
 */
struct if_down2up *goto_end_down2up(struct if_down2up *st)
{
	int cnt = 0;
	while(st->next != NULL)
	{
		st = st->next;
		if(cnt++ > MAX_ITEM_NUM_DOWN2UP	)/* MAX NUM & Keep from block ,20190704 */
			return NULL;
	}
	return st;
}
struct if_down2up *goto_head_down2up(struct if_down2up *st)
{
	int cnt = 0;
	while(st->priv != NULL)
	{
		st = st->priv;
		if(cnt++ > MAX_ITEM_NUM_DOWN2UP	)/* MAX NUM & Keep from block ,20190704 */
			return NULL;
	}
	return st;
}

/* Add item, or init the linklist
ARGS	: name==NULL -- init, name != NULL -- add item;
RETURN	: the new */
/**/
struct if_down2up *add_if_down2up(struct if_down2up *st, const char *name, int type)
{
	struct if_down2up *tmp,*new;

	if(NULL == name)/* init */
	{
		new  = (struct if_down2up *)malloc(sizeof(struct if_down2up));
		memset(new, 0, sizeof(struct if_down2up));

		new->next = NULL;
		new->priv = NULL;
	}
	else/* add item */
	{
		if(NULL == (tmp = goto_end_down2up(st)) )/* can not finish looking up ,20190704*/
			goto not_chg;

		if(NULL == (new = (struct if_down2up *)malloc(sizeof(struct if_down2up))) )
			goto not_chg;
		memset(new, 0, sizeof(struct if_down2up));

		tmp->next = new;
		new->priv = tmp;
		new->next = NULL;
#if 0
		sprintf(new->name,"%d",(int)time(NULL));
		new->address_type = (int)time(NULL);
#else
		strcpy(new->name,name);
		new->address_type = type;
#endif
	}
	printf("[%4d],priv:%d,next:%d,"AC_LGREEN"addr"AC_NONE":(0x%08X) "AC_YELLOW"ADD"AC_NONE"\n" ,
			__LINE__, new->priv == NULL ? 0 : 1, new->next == NULL ? 0 : 1 ,(unsigned int)new);

	return new;/* NORMAL */
not_chg:
	printf("[%4d],"AC_LRED"Failed ADD "AC_NONE"\n",__LINE__);
	return st;/* unexpected */
}

/* Find item by name 
RETURN : Pointer of the item, or NULL if not found.*/
/*LINK LIST*/
struct if_down2up *find_by_name_down2up(struct if_down2up *st, const char*name)
{
	struct if_down2up *tmp;
	tmp = st;

	while(tmp->priv != NULL)
	{
		tmp = tmp->priv;
	}
	while(tmp->next != NULL)
	{
		if(0 == strcmp(tmp->name, name))/* COMPARE */
		{
			goto done;
		}
		tmp = tmp->next;
	}
	/* FIX:add check the la_st */
	if(0 == strcmp(tmp->name, name))
	{
		goto done;
	}

	return NULL;

done:
	printf("[%4d],priv:%d,next:%d,"AC_LGREEN"addr"AC_NONE":(0x%08X) "AC_YELLOW"FIND"AC_NONE"\n" ,
			__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp);
	return tmp;
}
/* DATASTRUCT-QUEUE
WARNING : Success only when value returned equal to zero */
int find_by_fifo_down2up(struct if_down2up *st, struct if_down2up *ret_val)
{
	//goto head(priv)
	struct if_down2up *tmp;
	if(NULL == (tmp = goto_head_down2up(st)) )/* FINDING */
		return -2;

	tmp = tmp->next;/* Skip HEAD node */

	strcpy(ret_val->name, tmp->name);/* Get data */
	ret_val->address_type = tmp->address_type;

	chg_if_down2up(head,tmp->name,-1);/* Delete item of the linklist ,TODO:if items have same name*/
	return 0;/* SUCCESS */
}
/* DATASTRUCT-STACK 
WARNING : Success only when value returned equal to zero */
int find_by_filo_down2up(struct if_down2up *st, struct if_down2up *ret_val)/* and delete it */
{
	//goto end(next)
	struct if_down2up *tmp;
	if(NULL == (tmp = goto_end_down2up(st)) )/* FINDING */
		return -2;

	strcpy(ret_val->name, tmp->name);/* Get data */
	ret_val->address_type = tmp->address_type;

	chg_if_down2up(head,tmp->name,-1);/* Delete item of the linklist ,TODO:if items have same name*/
	return 0;/* SUCCESS */
}


/* Update or Delete item, found by name
ARGS	: type < 0 -- del;   type >=0 -- change [type];
RETURN 	: 0 - SUCCESS */
int chg_if_down2up(struct if_down2up *st, const char *name, int type)
{
	struct if_down2up *tmp;
	if(NULL == (tmp = find_by_name_down2up(st,name)))
	{
		return 2;//NOT EXIST
	}

	if(type < 0)//DEL
	{
		if(NULL == tmp->next)/* The end */
		{
			tmp->priv->next = NULL;
		}
		else if(NULL == tmp->priv)/* The head */
		{
			tmp->next->priv = NULL;
			head = tmp->next;
		}
		else/* Normal */
		{
			tmp->priv->next = tmp->next;
			tmp->next->priv = tmp->priv;
		}
		free(tmp);
	}
	else//CHG
	{
		strcpy(tmp->name,name);
		tmp->address_type = type;
	}

	printf("[%4d],priv:%d,next:%d,"  AC_LGREEN  "addr"  AC_NONE  ":(0x%08X)"  "%s"  " %s"  AC_NONE  "\n",
			__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp, type<0 ? AC_LRED : AC_YELLOW , (type<0) ? "DEL" : "CHG" );
	return 0;
}

/*
	printf("[%4d],priv:%d,next:%d,"  AC_LGREEN  "addr"  AC_NONE  ":(0x%08X)"  "%s"  "%s"  AC_NONE  "\n",
			__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp), AC_LRED, ((type<0) ? "DEL" : "CHG");
link_list.c:327:4: warning: format ‘%s’ expects a matching ‘char *’ argument [-Wformat=]
__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp), AC_LRED, ((type<0) ? "DEL" : "CHG");
^
link_list.c:327:4: warning: format ‘%s’ expects a matching ‘char *’ argument [-Wformat=]
*/


