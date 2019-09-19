#include <stdio.h>

void main(void)
{
	printf("%s endian \n", __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ? "little" : "big");
}

