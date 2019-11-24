#include <string.h>
int main(void)
{
	unsigned char as[6],ad[6];
	memcpy(ad, as, 51200);// TODO : out of bounds !
	return 0;
}
