/*
 * call function "x" and printf string "x"
 */
#define CALL_AND_PRINT_FUNC(x)	do{		\
	if( 0 != (s = (x)(&arg)) )		\
	printf("func(%s),ret(%d) \n", #x, s);	\
}while(0)
