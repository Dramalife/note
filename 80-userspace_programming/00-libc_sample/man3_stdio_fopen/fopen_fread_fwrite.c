#include <stdio.h>

struct test_st
{
#define SIZE_ST_STR	64
	char str1[SIZE_ST_STR];
	char str2[SIZE_ST_STR];
	char str3[SIZE_ST_STR];
	char arr1[2][SIZE_ST_STR];
};

int main(int argc, char **argv)
{

	struct test_st data_w = {0};
	struct test_st data_r = {0};

	/* set data_w */
	snprintf(data_w.str1,	SIZE_ST_STR, "%s,%d",__func__,__LINE__);
	snprintf(data_w.str2,	SIZE_ST_STR, "%s,%d",__func__,__LINE__);
	snprintf(data_w.str3,	SIZE_ST_STR, "%s,%d",__func__,__LINE__);
	snprintf(data_w.arr1[0],SIZE_ST_STR, "%s,%d",__func__,__LINE__);
	snprintf(data_w.arr1[1],SIZE_ST_STR, "%s,%d",__func__,__LINE__);

	FILE *fp = NULL;
	if( (fp = fopen(argv[1], "w")) )
	{
		/* data_w stored in file */
		fwrite(&data_w, 1, sizeof(struct test_st), fp);
		fclose(fp);
		fp = NULL;
	}

	if( (fp = fopen(argv[1], "r")) )
	{
		/* data_r get from file */
		fread(&data_r, 1, sizeof(struct test_st), fp);
		fclose(fp);
		fp = NULL;
	}

	printf("(%s)(%s)(%s)(%s)(%s) \n",
			data_r.str1,
			data_r.str2,
			data_r.str3,
			data_r.arr1[0],
			data_r.arr1[1]);

}
