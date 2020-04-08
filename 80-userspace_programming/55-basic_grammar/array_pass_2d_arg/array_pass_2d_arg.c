/*
 * REF URL : https://blog.csdn.net/qq_43868654/article/details/84641383
 */


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


#define DATA_LEN64	64
char c_array[2][DATA_LEN64];


/*******************************************************************************
 * Compile -  error
 * array type has incomplete element type ‘char[]’
 ******************************************************************************/
#if 0
void pass_array_2d_error(char array[][])
{
	strncpy(array[0], "aaaaa", DATA_LEN64);
	strncpy(array[1], "aaaaa", DATA_LEN64);
}
#endif

/*******************************************************************************
 * Runtime - coredump(SIGSEGV) 
 * arg : array of pointer
 ******************************************************************************/
void pass_array_typeofpointer(char *array[])
{
	snprintf(array[0], DATA_LEN64, "%s-%d",__func__,__LINE__);
	snprintf(array[1], DATA_LEN64, "%s-%d",__func__,__LINE__);
}

/*******************************************************************************
 * Compile - error 
 * invalid use of array with unspecified bounds
 ******************************************************************************/
#if 0
void pass_pointer_point2array_invalid(char (*array)[])
{
	snprintf(array[0], DATA_LEN64, "%s-%d",__func__,__LINE__);
	snprintf(array[1], DATA_LEN64, "%s-%d",__func__,__LINE__);
}
#endif

/*******************************************************************************
 * Runtime - Normal
 * arg : pointer point to array
 ******************************************************************************/
void pass_pointer_point2array(char (*array)[])
{
	snprintf( (*array + 0), DATA_LEN64, "%s-%d",__func__,__LINE__);
	snprintf( (*array + DATA_LEN64), DATA_LEN64, "%s-%d",__func__,__LINE__);
}

/*******************************************************************************
 * Runtime - Normal
 * arg : 2d array
 ******************************************************************************/
void pass_array_2d(char array[][DATA_LEN64])
{
	snprintf(array[0], DATA_LEN64, "%s-%d",__func__,__LINE__);
	snprintf(array[1], DATA_LEN64, "%s-%d",__func__,__LINE__);
}

/*******************************************************************************
 * Signal handler
 ******************************************************************************/
void signal_handler(unsigned int sn)
{
	printf("signal(%d)\n",sn);
	exit(1);
}

int main(void)
{
	/* Register signal handler */
	signal(SIGSEGV, (void *)signal_handler);


	pass_pointer_point2array(c_array);
	printf("#%s#%s# \n",c_array[0],c_array[1]);
	pass_array_2d(c_array);
	printf("#%s#%s# \n",c_array[0],c_array[1]);

	return 0;

}
