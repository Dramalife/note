#include <unistd.h>
#define NOT_SUGGESTED	1

int func(int argc, char **argv)
{
	int index = 0;
	char tmp[10] = {0};

	if (argc > 3)
		argc = 3;

	for(index = 0; index < argc; index++)
	{
		sprintf(tmp, "%s", argv[index]);
		printf("(%s) \n",tmp);
	}
}

int main(int argc, char **argv)
{
	char name[5] = {0};
	char *ptr = name;
	char *pptr[3] = {name,name,name};

	sprintf(name, "%s", "xxxx");

#if NOT_SUGGESTED
	func(argc,&ptr);/* argc > 1, SEGV */
#else
	func(argc,pptr);
#endif


	return 0;
}
