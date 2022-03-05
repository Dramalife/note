int *ret_stack_after_scope(void)
{
	int i = 0;
	return &i;
}

int main(void)
{
	int *ptr = ret_stack_after_scope();
	return 0;
}
