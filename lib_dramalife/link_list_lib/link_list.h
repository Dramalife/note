#ifndef	LINK_LIST_DRAMALIFE_H
#define LINK_LIST_DRAMALIFE_H

/* Test related */
#define AUTO_TEST_DOWN2UP	1

/* Limits */
#define MAX_ITEM_NUM_DOWN2UP	256

/* Print related */
#define HAVE_TERM_COLOR_DRAMALIFE	1
#define HAVE_GCC_REL_SHOW		1

/* Data type */
#define LINKLIST_DEF_PERSONAL_STRUCT_DRAMALIFE 0/* Should not be changed. */

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

#endif

/* [Additional] */ int find_by_fifo_down2up(ll_data_type *st, ll_data_type *ret_val);/* Get the oldest item */
/* [Additional] */ int find_by_filo_down2up(ll_data_type *st, ll_data_type *ret_val);/* Get the newst  item */

/* [Func4Test]  */ void test_func_down2up(ll_data_type *st, int times, int interval);
/* [Func4Test]  */ void debug_if_down2up(ll_data_type *st);

/* [Core Func]  */ ll_data_type *goto_end_down2up(ll_data_type *st);
/* [Core Func]  */ ll_data_type *goto_head_down2up(ll_data_type *st);
/* [Core Func]  */ ll_data_type *add_if_down2up(ll_data_type *st, const char *name, int type);
/* [Core Func]  */ ll_data_type *find_by_name_down2up(ll_data_type *st, const char*name);
/* [Core Func]  */ int chg_if_down2up(ll_data_type *st, const char *name, int type);

