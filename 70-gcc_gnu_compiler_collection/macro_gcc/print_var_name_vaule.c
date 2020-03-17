#include <stdio.h>

#if 0
#ifdef __SIZE_WIDTH__
#if __SIZE_WIDTH__ == 64
#define print_show(x)   do{printf("%-16s : %-4ld \n", #x,x);}while(0)
#else
#define print_show(x)   do{printf("%-16s : %-4d \n", #x,x);}while(0)
#endif
#endif
#define print_showl print_show
#define print_showi print_show
#else
#define print_showl(x)   do{printf("%-16s : %-4ld \n", #x,x);}while(0)
#define print_showi(x)   do{printf("%-16s : %-4d \n", #x,x);}while(0)
#endif

void main(void)
{
	int data_a = 8;

	print_showl(sizeof(data_a));
	print_showi(data_a);
}

