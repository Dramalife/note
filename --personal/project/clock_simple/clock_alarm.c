#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int hour;
int min;
int sec;
int refresh_flag = 1;
int ahour;
int amin;
int alarm_flag = 0;
int alarm_ing = 0;

void *input(void *arg)
{
	char *buff = (char *)malloc(100 * sizeof(char));
	while(1)
	{
		gets(buff);
		if(alarm_ing == 0)
			refresh_flag = 0;
		else
			alarm_flag = 0;

		printf("Hour:");
		gets(buff);
		if(strlen(buff))
			hour = atoi(buff);

		printf("Min:");
		gets(buff);
		if(strlen(buff))
			min = atoi(buff);

		printf("Alarm Hour:");
		gets(buff);
		if(strlen(buff))
			ahour = atoi(buff);

		printf("Alarm Min:");
		gets(buff);
		if(strlen(buff))
			amin = atoi(buff);

		printf("Alarm Enable:");
		gets(buff);
		if(strlen(buff))
			alarm_flag = atoi(buff);


		refresh_flag = 1;
	}

}
void main(void)
{
	hour = 13;
	min = 0;
	sec = 40;
	ahour = 0;
	amin = 0;
	int tid;

	pthread_create((pthread_t *)&tid, NULL, input, NULL);

	while(1)
	{
		sleep(1);
		sec++;
		if(sec>=60)
		{
			sec=0;
			min++;
			if(min>=60)
			{
				min = 0;
				hour++;
				if(hour>=24)
					hour=0;
			}
		}
		if(alarm_flag)
		{
			if( (hour >= ahour)&&(min >= amin) )
			{
				alarm_ing = 1;
				printf("Alarming ... %d:%d \n",ahour,amin);
				refresh_flag = 0;
			}
		}
		if(refresh_flag)
		{
			printf("\r\e[K");
			printf("%02d:%02d:%02d \n",hour,min,sec);
		}
	}

}
