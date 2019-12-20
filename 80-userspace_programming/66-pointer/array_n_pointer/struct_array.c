#define SHOW_NAME_VAULE(x)	do{printf("sizeof(%s)=(%d) \n",#x,sizeof(x));}while(0)

struct array_st
{
	int num;
	char name[15];
};

int main(void)
{
	struct array_st st;
	struct array_st *pst = &st; 

	SHOW_NAME_VAULE(st);
	SHOW_NAME_VAULE(st.name);
	SHOW_NAME_VAULE(pst);
	SHOW_NAME_VAULE(pst->name);

	return 0;
}
