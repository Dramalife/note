#define CASE_MACRO	\
case 5:	\
case 6:	

int main(void)
{
	int i;

	for(i=0; i<10; i++)
	{
		switch(i)
		{
			case 2:
				printf("%s,%d (%d) \n",__func__,__LINE__,i);
				break;
			case 3:
			CASE_MACRO
				printf("%s,%d (%d) \n",__func__,__LINE__,i);
				break;
			default:
				printf("%s,%d (%d) \n",__func__,__LINE__,i);
				break;
		}
	}

	return 0;
}
