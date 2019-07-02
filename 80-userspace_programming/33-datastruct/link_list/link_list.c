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
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct if_down2up
{
	char name[20];
	int address_type;
	struct if_down2up *next;
	struct if_down2up *priv;
};

struct if_down2up *head;
void debug_if_down2up(struct if_down2up *st);
struct if_down2up *add_if_down2up(struct if_down2up *st, const char *name, int type);
struct if_down2up *find_if_down2up(struct if_down2up *st, const char*name);
int chg_if_down2up(struct if_down2up *st, const char *name, int type);

int main(void)
{
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

	head = add_if_down2up(head,"aaaa", 666);
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	return 0;
}

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


/* Add item, or init the linklist
ARGS	: name==NULL -- init, name != NULL -- add item;
RETURN	: the new */
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
		tmp = st;
		while(tmp->next != NULL)
			tmp = tmp->next;

		new = (struct if_down2up *)malloc(sizeof(struct if_down2up));
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
	printf("[%4d],priv:%d,next:%d,addr:(%8X) ADD\n" ,__LINE__, new->priv == NULL ? 0 : 1, new->next == NULL ? 0 : 1 ,(unsigned int)new);
	return new;
}

/* Find item by name 
RETURN : Pointer of the item, or NULL if not found.*/
struct if_down2up *find_if_down2up(struct if_down2up *st, const char*name)
{
	struct if_down2up *tmp;
	tmp = st;

	while(tmp->priv != NULL)
	{
		tmp = tmp->priv;
	}
	while(tmp->next != NULL)
	{
		if(0 == strcmp(tmp->name, name))
		{
			printf("[%4d],priv:%d,next:%d,addr:(%8X) FIND\n" ,__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp);
			return tmp;
		}
		tmp = tmp->next;
	}
	/* FIX:add check the la_st */
	if(0 == strcmp(tmp->name, name))
	{
		printf("[%4d],priv:%d,next:%d,addr:(%8X) FIND\n" ,__LINE__, tmp->priv == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,(unsigned int)tmp);
		return tmp;
	}
	return NULL;
}

/* Update or Delete item, found by name
ARGS	: type < 0 -- del;   type >=0 -- change [type];
RETURN 	: 0 - SUCCESS */
int chg_if_down2up(struct if_down2up *st, const char *name, int type)
{
	struct if_down2up *tmp;
	if(NULL == (tmp = find_if_down2up(st,name)))
	{
		return 2;//NOT EXIST
	}

	if(type < 0)//DEL
	{
		if(NULL != tmp->next)
		{
			tmp->priv->next = tmp->next;
			tmp->next->priv = tmp->priv;
		}
		else/*  */
		{
			tmp->priv->next = NULL;
		}
		free(tmp);
	}
	else//CHG
	{
		strcpy(tmp->name,name);
		tmp->address_type = type;
	}
	return 0;
}

