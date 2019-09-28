/*
 * note "link list" related file
 * Copyright (C) 2019 Dramalife@live.com
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
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-64-generic #73-Ubuntu SMP Thu Sep 12 13:16:13 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux;
 * 
 * Init : See the related c file;
 * Update : 2019.09.28, Add VERSION;
 *
 */
#ifndef	LINK_LIST_DRAMALIFE_H
#define LINK_LIST_DRAMALIFE_H



/* VERSION */
#define DL_LL_VERSION  		1	//Change mood ;)
#define DL_LL_PATCHLEVEL	0	//Change Interface OR Datastruct;
#define DL_LL_SUBLEVEL		1	//Change Function name;
#define DL_VERSION(a,b,c) (((a)<<16)+((b)<<8)+(c)) /* COPY FROM Linux source tree. */
/* VERSION NUM CHECK */
#if DL_LL_VERSION >= 1<<8 || DL_LL_PATCHLEVEL >= 1<<8 || DL_LL_SUBLEVEL >= 1<<8
#error VERSION_NUM_CHECK_ERROR !!!
#endif


/* Test related */
#define AUTO_TEST_DOWN2UP	1
/* Limits */
#define MAX_ITEM_NUM_DOWN2UP	256
/* Print related */
#define HAVE_TERM_COLOR_DRAMALIFE	1
#define HAVE_GCC_REL_SHOW		1
/* Data type */
#define LINKLIST_DEF_PERSONAL_STRUCT_DRAMALIFE 0/* Should not be changed. */


/* Datastruct */
#if (0 == LINKLIST_DEF_PERSONAL_STRUCT_DRAMALIFE)
struct if_down2up
{
       char name[20];	/* a specific data type */
       int address_type;/* a specific data type */
       void *data;	/*** generic data type (2019.08.10) ***/
       struct if_down2up *priv;	/* HEAD */
       struct if_down2up *next;	/* TAIL */
};
/* TODO : :match Type /ll_data_type/ 
 * UPDATE : 2019.08.10 ,this def becomes unuseful.
 */
typedef struct if_down2up ll_data_type;
#else
//TODO typedef it.
#endif


#if DL_LL_VERSION > 1 || DL_LL_PATCHLEVEL > 0 || DL_LL_SUBLEVEL > 0
/* Compatible for version 1.0.0 and version 1.0.1 START */
#define find_by_fifo_down2up    /**/    find_fifo_dlll
#define find_by_filo_down2up    /**/    find_filo_dlll
#define test_func_down2up       /**/    test_dlll
#define debug_if_down2up        /**/    debug_dlll
#define goto_end_down2up        /**/    dlll_go2tail
#define goto_head_down2up       /**/    dlll_go2head
#define add_if_down2up          /**/    add_elem_dlll
#define find_by_name_down2up    /**/    find_name_dlll
#define chg_if_down2up          /**/    chg_elem_dlll
/* Compatible for version 1.0.0 and version 1.0.1 END */
#endif


/* VERSION 1.0.0 */
#if DL_LL_VERSION == 1 && DL_LL_PATCHLEVEL == 0 && DL_LL_SUBLEVEL == 0
/* [Additional] */ int find_by_fifo_down2up(ll_data_type *st, ll_data_type *ret_val);/* Get the oldest item */
/* [Additional] */ int find_by_filo_down2up(ll_data_type *st, ll_data_type *ret_val);/* Get the newst  item */

/* [Func4Test]  */ void test_func_down2up(ll_data_type *st, int times, int interval);
/* [Func4Test]  */ void debug_if_down2up(ll_data_type *st);

/* [Core Func]  */ ll_data_type *goto_end_down2up(ll_data_type *st);
/* [Core Func]  */ ll_data_type *goto_head_down2up(ll_data_type *st);
/* [Core Func]  */ ll_data_type *add_if_down2up(ll_data_type *st, const char *name, int type);
/* [Core Func]  */ ll_data_type *find_by_name_down2up(ll_data_type *st, const char*name);
/* [Core Func]  */ int chg_if_down2up(ll_data_type *st, const char *name, int type);

/* VERSION 1.0.1 */
#elif DL_LL_VERSION == 1 && DL_LL_PATCHLEVEL == 0 && DL_LL_SUBLEVEL == 1
/* [Additional] */ int find_fifo_dlll(ll_data_type *st, ll_data_type *ret_val);
/* [Additional] */ int find_filo_dlll(ll_data_type *st, ll_data_type *ret_val);

/* [Func4Test]  */ void test_dlll(ll_data_type *st, int times, int interval);
/* [Func4Test]  */ void debug_dlll(ll_data_type *st);

/* [Core Func]  */ ll_data_type *dlll_go2tail(ll_data_type *st);
/* [Core Func]  */ ll_data_type *dlll_go2head(ll_data_type *st);
/* [Core Func]  */ ll_data_type *add_elem_dlll(ll_data_type *st, const char *name, int type);
/* [Core Func]  */ ll_data_type *find_name_dlll(ll_data_type *st, const char*name);
/* [Core Func]  */ int chg_elem_dlll(ll_data_type *st, const char *name, int type);
#endif



#endif
