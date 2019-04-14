#include<stdio.h>
void main(void)
{
printf("%d,%d,%d\n",
strncmp("eoip1", "eoip", 4),
strncmp("eoip", "eoip1", 4),
strncmp("eoip", "eoip", 4));
}
