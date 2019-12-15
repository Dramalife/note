#ifndef DRAMALIFE_GETOPT_LIB
#define DRAMALIFE_GETOPT_LIB


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DL_OPT_VERSION	"v0.8 (2019.12.15)"


/* DL_OPT_DEBUG 
 * TODO - NOT USED YET 
 */
#define DL_OPT_DEBUG_ENABLE_GLIBC_ERROR	0x80
#define DL_OPT_DEBUG_ENABLE_FUNCTION_IN	0x40
#define DL_OPT_DEBUG_ENABLE_PRINT_NONE	0x00
#ifndef DL_OPT_DEBUG
#define DL_OPT_DEBUG	DL_OPT_DEBUG_ENABLE_PRINT_NONE
#endif


/* DL_OPT_DETECT_ERROR_LEVEL 
 * Exported to user
 */
#define DL_OPT_DETECT_ERROR_LEVEL1_DEFAULT	1
#define DL_OPT_DETECT_ERROR_LEVEL2_NO_PRINT_ERR	2
#define DL_OPT_DETECT_ERROR_LEVEL3_DISTINGUISH	3
#ifndef DL_OPT_DETECT_ERROR_LEVEL
#define DL_OPT_DETECT_ERROR_LEVEL	DL_OPT_DETECT_ERROR_LEVEL3_DISTINGUISH
#endif
#define DL_OPT_DETECT_ETTOR_CHECK(x) (x == DL_OPT_DETECT_ERROR_LEVEL)

/* Used by "struct dl_option - dlopt_flag" */
#define DL_OPT_CHECK_FLAG(x,y)	(x&y)

/* Show version information */
#define DL_OPT_PRINT_NAME_VAULE_INT(x)	do{ printf("* %s(%d) \n",#x,x ); }while(0)
#define DL_OPT_SHOW_VERSION(f,l,c)	do{					\
	printf("Version : %s \n", DL_OPT_VERSION);				\
	printf("* [%s,%d] argc(%d) \n",f,l,c );					\
	DL_OPT_PRINT_NAME_VAULE_INT( DL_OPT_DETECT_ERROR_LEVEL );		\
	DL_OPT_PRINT_NAME_VAULE_INT( DL_OPTD_DATA_BYTE_SIZE );			\
	DL_OPT_PRINT_NAME_VAULE_INT( DL_OPT_DEBUG );			\
}while(0)

/* Used by "struct dl_option - dlopt_flag", runtime vaule compare. */
#define DL_OPT_ELEMENT_DATA_EXIST		0x80
#define DL_OPT_ELEMENT_DATA_NEED_FREE		0x40
#define DL_OPT_ELEMENT_DATA_TYPE_CHAR_ARR	0x20
#define DL_OPT_ELEMENT_DATA_TYPE_INT_ARR	0x10
struct dl_option
{
	char dlopt_name;
	void *dlopt_data;
	int (*dlopt_handler)(void *);
	unsigned char dlopt_flag;	/* Have element? */
};

/* Used by "struct dl_option_data - dloptd_u" */
#ifndef	DL_OPTD_DATA_BYTE_SIZE
#define	DL_OPTD_DATA_BYTE_SIZE	8
#endif
struct dl_option_data
{
	unsigned char dloptd_flag;	/* type? */
	union{
		char dloptdu_string[	DL_OPTD_DATA_BYTE_SIZE			];
		int dloptdu_int[	DL_OPTD_DATA_BYTE_SIZE / sizeof(int)	];
	} dloptd_u;/*array pointer*/
#define dloptd_string	dloptd_u.dloptdu_string
#define dloptd_int	dloptd_u.dloptdu_int
};

/* MACRO Provided by lib_dramalife_getopt for debugging print */
#define DL_OPT_HANDLER_PRINT_INFO(x)	do{							\
	struct dl_option *self = (struct dl_option *)x;						\
	if(self){										\
		printf("[%s,%d] SELF - name(%c),flag(0x%02X),havedata(%c),havehandler(%c). \n" 	\
				,__func__,__LINE__                                         	\
				,self->dlopt_name                                          	\
				,self->dlopt_flag                                          	\
				,self->dlopt_data?'Y':'N'                                  	\
				,self->dlopt_handler?'Y':'N'                               	\
				);                                                             	\
	}											\
}while(0)


void dl_getopt_freeall(struct dl_option (*dlopt)[]);
int dl_getopt(int argc, char *argv[], struct dl_option (*dlopt)[]);

#endif
