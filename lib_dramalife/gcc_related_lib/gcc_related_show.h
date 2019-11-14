/*gcc_related_show.h*/
#ifndef GCC_RELATED_SHOW_H
#define GCC_RELATED_SHOW_H

#define GCC_R_SHOW_MAX		0X80000000
#define GCC_R_SHOW_VERSION	0X40000000
#define GCC_R_SHOW_DATE		0X20000000
#define GCC_R_SHOW_TIME		0X10000000

#define GCC_R_SHOW_MIN		0X1

void gcc_related_show_no_arg_in(unsigned int options);

/* Make gcc happy ;-)
 * error: unused parameter ‘arg’ [-Werror=unused-parameter]
 * error: suggest braces around empty body in an ‘if’ statement [-Werror=empty-body]
 */
#define MAKE_GCC_HAPPY(x)	do{if(NULL == x){}}while(0)


#endif

