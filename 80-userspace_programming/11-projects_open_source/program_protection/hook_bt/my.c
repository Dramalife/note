// count.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void fun1();
void fun2();
void fun3();
void fun4();
void fun5();
void fun6();
void fun7();
void fun8();


void fun1()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);
	int j;
	printf("Enter a value to continue FUN2 : ");
	scanf("%d",&j);
	fun2();
}

void fun2()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);
	printf("FUN2 CHOOSE :\n");
	printf("If =0 FUN3.\n");
	printf("If !=0 FUN4.\n");
	printf("Enter a value to choose : ");
	int b;
	scanf("%d",&b);
	if(b == 0)
	{
		fun3();
	}
	else if (b != 0)
    	{
		fun4();
	}
}

void fun3()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);
}

void fun4()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);
}

void fun5()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);
	int k;
	printf("Enter a value to continue FUN6 : ");
	scanf("%d",&k);
	fun6();
}

void fun6()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);
}

void fun7()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);
	printf("Enter a value to continue FUN8 : ");
	int l;
	scanf("%d",&l);
	fun8();
}

void fun8()
{
	printf("NOW FUNCTION IS : ");
	puts(__FUNCTION__);

}

int main()
{
	puts(__FUNCTION__);

	int a;
	printf("MAIN CHOOSE:\n");
	printf("If >0 FUN1.\n");
	printf("If =0 FUN5.\n");
	printf("If <0 FUN7.\n");
	printf("Enter a value to choose : ");
	scanf("%d",&a);
	if(a > 0)
	{
		fun1();
	}
	else if (a == 0)
   	{
		fun5();
	}
	else
	{
		fun7();
	}

	while(1)
	{
		fun1();
		sleep(1);
	}
	return 0;
}
