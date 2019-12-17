#include <stdio.h>

int main(int argc, char **argv)
{
	int num;
	FILE *fp = popen(argv[1],"r");
#if 0
	/* get string */
	while ( NULL != fgets(buf, 32, fp) )
	{
		printf("%s \n",buf);
	}
	printf("--------\n" "%s \n",buf);
#else
	/* get num */
	fscanf(fp,"%d", &num);
	printf("--------\n" "%d \n",num);
#endif
	pclose(fp);
	return 0;
}
