#include <stdlib.h>

int main(void)
{
	int *pint = malloc(sizeof(int));
	free(pint);
	*pint = 9;
	return *pint;
}
