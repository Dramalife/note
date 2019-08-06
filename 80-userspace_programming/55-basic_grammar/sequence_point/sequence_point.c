/*sequence_point
  序列点*/
#include<stdio.h>

int main(void)
{
	int a = 5;
	int b;

	printf("%d \n" , b = a++ > 5 ? 0 : a );//RESULT:6

	return 0;
}


//node = node = node->head
//operation on  may be undefined

