struct mymmst
{
	int num;
};
struct myst
{
	struct mymmst id;
	struct mymmst old;
};

struct myst data = {0};

#define SET_VAULT_ST_MEMBER(st, var, vaule)	do{st.var = vaule;}while(0)
int main(void)
{

	SET_VAULT_ST_MEMBER(data.id, num, 6 );
	SET_VAULT_ST_MEMBER(data.old, num, 6 );

	printf("%d,%d\n", data.id.num, data.old.num);
	return 0;
}
