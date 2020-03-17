#include <string.h>
#include <stdio.h>

#ifdef __SIZE_WIDTH__
#if __SIZE_WIDTH__ == 64
#define print_show(x)	do{printf("%-16s : %-4ld \n", #x,x);}while(0)
#else
#define print_show(x)	do{printf("%-16s : %-4d \n", #x,x);}while(0)
#endif
#endif


/*
 * Impractical way !!!
 * Data type & array variable only !!!
 */
#define _sizeof(T)	( (size_t)((T*)0 + 1))
#define array_sizeof(T)	( (size_t)(&T+1)  - (size_t)(&T)  )

struct astruct_3int
{
	int a1;
	int a2;
	int a3;
	char c1;
};


/* Golbal, for Symbols 
 * Local variables are stored in the stack when the program is running, not in the (.bss or .data) section.
 */
struct astruct_3int st_array[3]={{2,2,2,'c'},{3,3,3}};
struct astruct_3int st_var;
struct astruct_3int *ptr_st;

void main(void)
{
	/* a sizeof */
	print_show(_sizeof(struct astruct_3int));
	///print_show(_sizeof(((struct astruct_3int)(st_var))));
	///printf("%x,%x \n", &st_var, st_var*);
	print_show(array_sizeof(st_array));
	printf("\n\n\n");


	/* struct type
	 * 4.15.0-74-generic, x86_64, gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0 . result is 16.
	 */
	print_show(sizeof(struct astruct_3int));

	/* struct array */
	print_show(sizeof(st_array));

	/* struct variable */
	print_show(sizeof((struct astruct_3int)st_var));

	/* struct pointer */
	print_show(sizeof((struct astruct_3int *)ptr_st));
}

