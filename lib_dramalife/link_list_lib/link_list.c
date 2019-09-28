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
[2019.07.25]	Divided
 */

#include "link_list.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#if (1 == AUTO_TEST_DOWN2UP)
#include <unistd.h>/* sleep() */
#include <time.h>/* time_t time(time_t *t); */
#endif

#if (1 == HAVE_TERM_COLOR_DRAMALIFE)
#include "../terminal_color_dramalife.h"/* Installed from "note/lib_dramalife" */
#define AC_NONE		CNONE
#define AC_LRED		CLRED
#define AC_LGREEN	CLGREEN
#define AC_YELLOW	CYELLOW
#else
#define AC_NONE		""
#define AC_LRED		""
#define AC_LGREEN	""
#define AC_YELLOW	""
#endif

#ifndef __WORDSIZE 
#error WORDSIZE undefined!!
#endif




/* DATASTRUCT-QUEUE
WARNING : Success only when value returned equal to zero */
int find_by_fifo_down2up(ll_data_type *st, ll_data_type *ret_val)
{
	//goto head(priv)
	ll_data_type *tmp;
	if(NULL == (tmp = goto_head_down2up(st)) )/* FINDING */
		return -2;

	tmp = tmp->next;/* Skip HEAD node */

	strcpy(ret_val->name, tmp->name);/* Get data */
	ret_val->address_type = tmp->address_type;

	chg_if_down2up(st,tmp->name,-1);/* Delete item of the linklist ,TODO:if items have same name*/
	return 0;/* SUCCESS */
}
/* DATASTRUCT-STACK 
WARNING : Success only when value returned equal to zero */
int find_by_filo_down2up(ll_data_type *st, ll_data_type *ret_val)/* and delete it */
{
	//goto end(next)
	ll_data_type *tmp;
	if(NULL == (tmp = goto_end_down2up(st)) )/* FINDING */
		return -2;

	strcpy(ret_val->name, tmp->name);/* Get data */
	ret_val->address_type = tmp->address_type;

	chg_if_down2up(st,tmp->name,-1);/* Delete item of the linklist ,TODO:if items have same name*/
	return 0;/* SUCCESS */
}


#if AUTO_TEST_DOWN2UP
#ifdef RAND_MAX
#undef RAND_MAX
#endif
#define RAND_MAX 1
void test_func_down2up(ll_data_type *st, int times, int interval)
{
	while(times--)
	{
		usleep(interval);
		//if( (int)time(NULL) & 0x1 )
		if( rand() & 0x1 )
		{
			add_if_down2up(st,"aaaa", (int)time(NULL));/* Add item to the linklist */
		}
		else
		{
			chg_if_down2up(st,"aaaa",-1);/* Delete item of the linklist */
		}
		debug_if_down2up(st);
	}
}
#else
void test_func_down2up(ll_data_type *st, int times, int interval);
#endif

/* Debug func, print all item(s) of the linklist */
void debug_if_down2up(ll_data_type *st)
{
	ll_data_type *tmp = st;
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

/* FUNC   : ll_data_type *goto_end_down2up(ll_data_type *st);
 * ARGIN  : A pointer of the link_list.
 * RETURN : The function return a pointer to the ending of the link_list,or NULL
 * 		if the ending is not found or 
 * 		the size of the link_list is bigger than MAX_ITEM_NUM_DOWN2UP;
 * ADDDATE: 2019.07.04;
 */
ll_data_type *goto_end_down2up(ll_data_type *st)
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
ll_data_type *goto_head_down2up(ll_data_type *st)
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
ll_data_type *add_if_down2up(ll_data_type *st, const char *name, int type)
{
	ll_data_type *tmp,*new;

	if(NULL == name)/* init */
	{
		new  = (ll_data_type *)malloc(sizeof(ll_data_type));
		memset(new, 0, sizeof(ll_data_type));

		new->next = NULL;
		new->priv = NULL;
	}
	else/* add item */
	{
		if(NULL == (tmp = goto_end_down2up(st)) )/* can not finish looking up ,20190704*/
			goto not_chg;

		if(NULL == (new = (ll_data_type *)malloc(sizeof(ll_data_type))) )
			goto not_chg;
		memset(new, 0, sizeof(ll_data_type));

		tmp->next = new;
		new->priv = tmp;
		new->next = NULL;

		strcpy(new->name,name);
		new->address_type = type;
	}
#if  __WORDSIZE ==  64
	printf("[%4d],priv:%d,next:%d,"AC_LGREEN"addr"AC_NONE":(0x%016llX) "AC_YELLOW"ADD"AC_NONE"\n" ,
			__LINE__, new->priv == NULL ? 0 : 1, new->next == NULL ? 0 : 1 ,(long long unsigned int)new);
#elif  __WORDSIZE ==  32
	printf("[%4d],priv:%d,next:%d,"AC_LGREEN"addr"AC_NONE":(0x%08X) "AC_YELLOW"ADD"AC_NONE"\n" ,
			__LINE__, new->priv == NULL ? 0 : 1, new->next == NULL ? 0 : 1 ,(unsigned int)new);
#endif

	return new;/* NORMAL */
not_chg:
	printf("[%4d],"AC_LRED"Failed ADD "AC_NONE"\n",__LINE__);
	return st;/* unexpected */
}

/* Find item by name 
RETURN : Pointer of the item, or NULL if not found.*/
/*LINK LIST*/
ll_data_type *find_by_name_down2up(ll_data_type *st, const char*name)
{
	ll_data_type *tmp;
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
#if  __WORDSIZE ==  64
	printf("[%4d],priv:%d,next:%d,"AC_LGREEN"addr"AC_NONE":(0x%016llX) "AC_YELLOW"FIND"AC_NONE"\n" ,
			__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(long long unsigned int)tmp);
#elif  __WORDSIZE ==  32
	printf("[%4d],priv:%d,next:%d,"AC_LGREEN"addr"AC_NONE":(0x%08X) "AC_YELLOW"FIND"AC_NONE"\n" ,
			__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp);
#endif
	return tmp;
}

/* Update or Delete item, found by name
ARGS	: type < 0 -- del;   type >=0 -- change [type];
RETURN 	: 0 - SUCCESS */
int chg_if_down2up(ll_data_type *st, const char *name, int type)
{
	ll_data_type *tmp;
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
			st = tmp->next;
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

#if  __WORDSIZE ==  64
	printf("[%4d],priv:%d,next:%d,"  AC_LGREEN  "addr"  AC_NONE  ":(0x%016llX)"  "%s"  " %s"  AC_NONE  "\n",
			__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(long long unsigned int)tmp, type<0 ? AC_LRED : AC_YELLOW , (type<0) ? "DEL" : "CHG" );
#elif  __WORDSIZE ==  32
	printf("[%4d],priv:%d,next:%d,"  AC_LGREEN  "addr"  AC_NONE  ":(0x%08X)"  "%s"  " %s"  AC_NONE  "\n",
			__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp, type<0 ? AC_LRED : AC_YELLOW , (type<0) ? "DEL" : "CHG" );
#endif
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


