#include <string.h>
int main(void)
{
	unsigned char as[6],ad[6];
	memcpy(ad, as, 8);// TODO : Out of bounds !
	return 0;
}
