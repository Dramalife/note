#include<stdio.h>

typedef void (*init_call)(void);

/*
 * These two variables are defined in link script.
 */
extern init_call _init_start;
extern init_call _init_end;

void do_initcalls(void)
{
	init_call *init_ptr = &_init_start;
	for (; init_ptr < &_init_end; init_ptr++) {
		printf("init address: %p\n", init_ptr);
		(*init_ptr)();
	}
}

int main(void)
{
	do_initcalls();
	return 0;
}

