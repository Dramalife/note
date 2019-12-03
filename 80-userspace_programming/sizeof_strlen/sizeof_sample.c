#include <stdio.h>


#define MY_CODE()		do{ printf("sizeofptr(%d),sizeof(%d),strlen(%d) \n"		\
	,sizeof(str)	/*8*/		\
	,sizeof("eth")	/*4*/		\
	,strlen(str)	/*3*/		\
	);		\
	}while(0);

int main(void)
{
	const char *str="eth";

	printf("string(%s) \n",str);

	MY_CODE();
	//printf("\n\n %s \n\n",MY_CODE()); //;-(

	return 0;
}

