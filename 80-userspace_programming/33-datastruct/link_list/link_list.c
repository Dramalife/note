/*
   note datastruct linklist related file
   Copyright (C) 2019 Dramalife

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

TODO : 
[2019.06.26] If already exist an item, which name is same as the item to be added.

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
	struct if_down2up *last;
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

	head = add_if_down2up(head,"aaaa", 1111);/* Add item to the linklist */
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	head = add_if_down2up(head,"bbbb", 2222);
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

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
	printf("[%4d],last:%d,next:%d SHOW\n" ,__LINE__, tmp->last == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 );
	while(tmp->last != NULL)
	{
		tmp = tmp->last;
		printf("going to HEAD...\n");
	}//goto HEAD
	while(tmp->next != NULL)////while(tmp->next != NULL);
	{
		if(tmp->last != NULL)//HEAD
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
		new->last = NULL;
	}
	else/* add item */
	{
		tmp = st;
		while(tmp->next != NULL)
			tmp = tmp->next;

		new = (struct if_down2up *)malloc(sizeof(struct if_down2up));
		memset(new, 0, sizeof(struct if_down2up));

		tmp->next = new;
		new->last = tmp;
		new->next = NULL;
#if 0
		sprintf(new->name,"%d",(int)time(NULL));
		new->address_type = (int)time(NULL);
#else
		strcpy(new->name,name);
		new->address_type = type;
#endif
	}
	printf("[%4d],last:%d,next:%d,addr:(%8X) ADD\n" ,__LINE__, new->last == NULL ? 0 : 1, new->next == NULL ? 0 : 1 ,new);
	return new;
}

/* Find item by name 
RETURN : Pointer of the item, or NULL if not found.*/
struct if_down2up *find_if_down2up(struct if_down2up *st, const char*name)
{
	struct if_down2up *tmp;
	tmp = st;

	while(tmp->last != NULL)
	{
		tmp = tmp->last;
	}
	while(tmp->next != NULL)
	{
		if(0 == strcmp(tmp->name, name))
		{
			printf("[%4d],last:%d,next:%d,addr:(%8X) FIND\n" ,__LINE__, tmp->last == NULL ? 0 : 1, tmp->next == NULL ? 0 : 1 ,tmp);
			return tmp;
		}
		tmp = tmp->next;
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
		tmp->last->next = tmp->next;
		tmp->next->last = tmp->last;
		free(tmp);
	}
	else//CHG
	{
		strcpy(tmp->name,name);
		tmp->address_type = type;
	}
	return 0;
}

