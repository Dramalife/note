#include <stdlib.h>

#define TURN(x)	do{system("echo " x  " > /dev/stdout");}while(0)

// system( "echo" "xxxx" " > /dev/stdout"  );

int main(void)
{
	TURN("on");
	TURN("off");
	return 0;
}
