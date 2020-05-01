#include "lib_dramalife.h"


/* SWITCH - Debug Print */
#ifdef _DLTERMINAL_DEBUG_ENABLED_
#define debugout(x,...)	do{printf("[%s,%s,%d] ",__FILE__,__func__,__LINE__);printf(x,##__VA_ARGS__);}while(0)
#else
#define debugout(x,...)	do{}while(0)
#endif


#ifdef _DL_TERMINAL_LIB_ENABLE_
/*
 * WARNING : dangerous function
 */
char *dl_terminal_get_password(char *buff)
{
	struct termios oldt, newt;
	int size = -1;

	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	debugout("BE CAREFUL : buff size ! \n");
	size = scanf("%s", buff); // TODO : size
	if(size){}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return buff;
}
#endif


#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(void)
{
	char passwd[1];

	printf("input (%s),(%s) \n",
			dl_terminal_get_password(passwd),
			passwd
	      );


	return 0;
}
#endif

