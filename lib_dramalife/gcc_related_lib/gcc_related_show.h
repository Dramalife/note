/*gcc_related_show.h*/
#ifndef GCC_RELATED_SHOW_H
#define GCC_RELATED_SHOW_H

#include <stdio.h>


#define DL_GCC_SHOW_VERSIONPT		0X8
#define DL_GCC_SHOW_VERSION		0X4
#define DL_GCC_SHOW_DATE		0X2
#define DL_GCC_SHOW_TIME		0X1


/*
 * USE : 
 * dl_gcc_print_compile_info( DL_GCC_SHOW_VERSION | DL_GCC_SHOW_DATE |
 * 	DL_GCC_SHOW_TIME );
 */
#define dl_gcc_print_compile_info(options, p)\
	do{\
		if( options & DL_GCC_SHOW_VERSION)\
		p("GCC VER:(%s)",__VERSION__);\
		if( options & DL_GCC_SHOW_DATE)\
		p(" DATE:(%s)",__DATE__);\
		if( options & DL_GCC_SHOW_TIME)\
		p(" TIME:(%s)",__TIME__);\
		if( options & DL_GCC_SHOW_VERSIONPT)\
		p("\nGCC VERSION:(%d)(%d)(%d) \n",__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__);\
	}while(0)
/* 
 * TODO : OUTDATED MACRO !
 * Compatiable with old code. 
 */
//#d e f i n e gcc_related_show_no_arg_in(options)	dl_gcc_print_compile_info(options, printf)


/* Make gcc happy ;-)
 * error: unused parameter ‘arg’ [-Werror=unused-parameter]
 * error: suggest braces around empty body in an ‘if’ statement [-Werror=empty-body]
 */
#define MAKE_GCC_HAPPY(x)	do{if(x == x){}}while(0)


/*
 * Print var_name & var_vaule, one parameter needed.
 * ARG1:the variable;
 * ARG2:the print function;
 */
#define dl_gcc_print_name_vaule(x,p)   do{\
	if(sizeof(x)<=4)\
	p("%-16s : %-4d \n", #x,(int)(x) );\
	else if(sizeof(x)<=8)\
	p("%-16s : %-4ld \n", #x,(long int)(x) );\
}while(0)



#endif

