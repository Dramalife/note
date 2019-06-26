#include <stdlib.h>
int main(void)
{
char *ptr = malloc(100 * sizeof(char));
//TODO memset
printf("%s", ptr);
return 0;
}
