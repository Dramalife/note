/*
Source Url : https://www.runoob.com/w3cnote/const-char.html
Update : fix : '/n' > '\n'
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>


/*****
 * p is a pointer to const char ;) 
 * const char *p;
 *            *p : p is a pointer (to)
 * const char    : const char
 * * * * * * * * * * * * * * * * * *
 * Vaule of p can be changed;
 * Memory pointed by p can not be changed;
 */
const char *p="hello";


void ptr_point2newmem(const char **pp)
{
	*pp = (char *) malloc(10);
	snprintf(*pp, 10, "hi google!");
}

void chg_ptr_vaule(const char **pp)
{
	/* error: assignment of read-only location ‘*(*pp + 1u)’ */
	//(*pp)[1] = 'x';
}

/*****
 * pp is a pointer to pointer to const char
 * const char **pp;
 *             *pp : pp is a pointer (to)
 *            *    : pointer (to)
 * const char      : const char
 * * * * * * * * * * * * * * * * * *
 * Vaule of pp can be changed;
 * Vaule of *pp (Memory pointed by pp) can be changed;
 * Memory pointed by *pp can not be changed;
 */
void chg_ptr_point(const char **pp)
{
	*pp=NULL;
	*pp="Hello world!";
}

int main()
{
	printf("before foo %s\n",p);
	ptr_point2newmem(&p);
	printf("after foo %s\n",p);

	chg_ptr_point(&p);
	printf("%d:%s\n",__LINE__, p);

	chg_ptr_vaule(&p);
	printf("%d:%s\n",__LINE__, p);

	/* error: assignment of read-only location ‘*(p + 1u)’ */
	//p[1] = 'x';

	return;
}

