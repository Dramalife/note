/*gcc_related_show.h*/
#ifndef GCC_RELATED_SHOW_H
#define GCC_RELATED_SHOW_H

#include <stdio.h>


#define GCC_R_SHOW_MAX		0X8
#define GCC_R_SHOW_VERSION	0X4
#define GCC_R_SHOW_DATE		0X2
#define GCC_R_SHOW_TIME		0X1
#define GCC_R_SHOW_MIN		0X1


/*
 * USE : 
 * gcc_related_show_no_arg_in( GCC_R_SHOW_VERSION | GCC_R_SHOW_DATE |
 * GCC_R_SHOW_TIME );
 * No arg in,such as "__LINE__"
 */
#define dl_compile_info_print(options)\
do{\
	if( options & GCC_R_SHOW_VERSION)\
		printf("GCC VER:(%s)",__VERSION__);\
	if( options & GCC_R_SHOW_DATE)\
		printf(" DATE:(%s)",__DATE__);\
	if( options & GCC_R_SHOW_TIME)\
		printf(" TIME:(%s)",__TIME__);\
	printf("\nGCC VERSION:(%d)(%d)(%d) \n",__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__);\
}while(0)


/* Make gcc happy ;-)
 * error: unused parameter ‘arg’ [-Werror=unused-parameter]
 * error: suggest braces around empty body in an ‘if’ statement [-Werror=empty-body]
 */
#define MAKE_GCC_HAPPY(x)	do{if(x == x){}}while(0)


extern void gcc_related_show_no_arg_in(unsigned int options);


#endif

