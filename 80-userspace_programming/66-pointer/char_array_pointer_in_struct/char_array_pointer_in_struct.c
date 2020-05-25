struct char_pointer_st
{
	int id;
	char *name
};
struct char_array_st
{
	int id;
	char name[];
};


#define TEST_FUNC(ptr, tsize, i, n)	do{\
	memset(buff, 0, sizeof(buff));\
	ptr = buff;\
	ptr->id = i;\
	strncpy(ptr->name, n, sizeof(buff)- tsize);\
	printf("id:%d,name:%s\n",ptr->id,ptr->name);\
}while(0)


int main(void)
{
	char buff[64];
	struct char_array_st *ca;
	struct char_pointer_st *cp;

	printf("array of struct\n");
	TEST_FUNC(ca, sizeof(struct char_array_st), __LINE__, __func__);
	printf("pointer of struct (SIGSEGV)\n");
	TEST_FUNC(cp, sizeof(struct char_pointer_st), __LINE__, __func__);
}

