#include<time.h> 
#include<stdio.h>

void main()   
{   
	time_t now;
	struct tm *timenow;
	time(&now);   
printf("time:%d\n",now);
	timenow = localtime(&now);   

	printf("Local time is %s\n",asctime(timenow));   
}   

