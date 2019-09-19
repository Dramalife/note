#include <stdio.h>

int main(void)
{
	int i = 1;
	unsigned char *pointer = (unsigned char *)&i;
	printf("%s endian \n", *pointer ? "little":"big");
}
