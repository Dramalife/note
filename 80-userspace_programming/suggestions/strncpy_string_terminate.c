#include "string.h"
#include "stdio.h"

#define STRING "string"

#if 1
#define MINNNN(x,y)	(((x)<(y))?(x):(y))
#define MINNN3(x,y,z)	MINNNN(MINNNN((x),(y)),(z))
#define strncpy(d,s,z)	do{							\
	strncpy(								\
			d,							\
			s,							\
			MINNN3((sizeof(d)-1),strlen(s),z)			\
	       );								\
	*(d + MINNN3((sizeof(d)-1),strlen(s),z) ) = 0;				\
	printf("sz1(%d),sz2(%d),sz3(%d) \n",(sizeof(d)-1),strlen(s),z);		\
}while(0)
#define safe_strncpy	strncpy
#endif

int strncpy_src_size(void)
{
	char tmp[64];
	char right[64];

	printf("[%s,%d] \n",__func__,__LINE__);

	memset(tmp, 'X', 64);
	memset(right, 'X', 64);

	printf("string(%s),len(%d) \n", STRING, strlen(STRING) );

	strncpy(tmp, STRING, strlen(STRING));
	printf("err-sample (%s) \n", tmp);

	strncpy(right, STRING, strlen(STRING) + 1);
	printf("right-samp (%s) \n", right);

	return 0;
}

int strncpy_maximum_size(void)
{
#define MAX_SIZE	6
	//char des[MAX_SIZE];
	char *des = (char *)malloc(MAX_SIZE * sizeof(char));
	char *data_tainted = (char *)malloc(MAX_SIZE * sizeof(char));
	memset(des, 'X', MAX_SIZE);//LOGIC ERROR !
	memset(data_tainted, 'Y', MAX_SIZE);

	// [strncpy_maximum_size,51] addr(0xa5a5670,0xa5a5690)
	int i = 0;
	for(i=0; i< 30; i++)
	{
		*(des + MAX_SIZE + i) = 'A';
		//	7	   8	     9	       A
		//	012345|67890123456789012345678901|234567
		//	XXXXXX|
		//(5670)string|AAAAAAAAAAAAAAAAAAAAAAAAAA|AAAAYY
		//	YYYYYY|
		//(5690)AAAAYY|--------------------------|
	}

	printf("[%s,%d] addr(0x%x,0x%x) \n"
			"sizeof_ptr(%d,%d) \n"
			,__func__,__LINE__, des,data_tainted
			,sizeof(des),sizeof(des)
	      );

	/* WARNING! Index should range from 0 to (MAX_SIZE - 1) */
#if 0	// ? memory manually
	*(des + MAX_SIZE) = 'X';
	*(des + MAX_SIZE + 1) = 'Y';
	*(des + MAX_SIZE + 2) = 0;
#endif

	strncpy(des, STRING, MAX_SIZE);	//LOGIC ERROR !
	//*(des + MAX_SIZE - 1) = 0;	//Fixed, some way better?

	printf("data_tainted(%s) \n",data_tainted);
	printf("[%s,%d] des(%s),sizeof_desarray(%d) \n",__func__,__LINE__,des,sizeof(des));
}

int main(void)
{
	strncpy_src_size();

	strncpy_maximum_size();//core dump

	return 0;
}
