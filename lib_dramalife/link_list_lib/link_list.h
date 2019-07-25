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
#define LINKLIST_DEF_PERSONAL_STRUCT_DRAMALIFE 0

#if (0 == LINKLIST_DEF_PERSONAL_STRUCT_DRAMALIFE)
struct if_down2up
{
       char name[20];
       int address_type;
       struct if_down2up *next;
       struct if_down2up *priv;
};
//TODO : :match Type /ll_data_type/
typedef struct if_down2up ll_data_type;
#else
//TODO typedef it.
#endif



#endif

