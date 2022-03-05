#include <stdlib.h>

void func1(void) 
{
	malloc(7);
}

void func2(void)
{
	malloc(5);
}

int main(void)
{
	func1();
	func2();
	printf("1111\n");
	return 0;
}
