#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int func_a();
int func_b();
int func_c();
int func_d();
int func_x();
int func_y();
int func_yy();
int func_yyy();

int func_c()
{
	int ret = random();
	func_a();
	return ret;
}
int func_d()
{
	int ret = random();
	func_b();
	return ret;
}
int func_x()
{
	system("uname > /dev/null");
	return 0;
}
int func_yyy()
{
	sleep(1);
	return 0;
}
int func_yy()
{
	system("uname > /dev/null");
	func_yyy();
	return 0;
}
int func_y()
{
	system("uname > /dev/null");
	system("uname > /dev/null");
	func_yy();
	return 0;
}
int func_a()
{
	printf("%s,%s,%d \n",__FILE__,__func__,__LINE__);
	system("ls");
	func_x();
	return 0;
}
int func_b()
{
	printf("%s,%s,%d \n",__FILE__,__func__,__LINE__);
	system("uname > /dev/null");
	func_y();
	return 0;
}
int main(void)
{
#if 0
	struct sigaction s;
	s.sa_flags = SA_SIGINFO;
	s.sa_sigaction = (void *)dlbt_signal_handler;
	sigaction (SIGUSR1,&s,NULL);
	sigaction (SIGABRT,&s,NULL);
#endif
	system("uname -a");

	printf("%s,%s,%d \n",__FILE__,__func__,__LINE__);
	while(1)
	{
		printf("%s,%s,%d (%d)\n",__FILE__,__func__,__LINE__,func_c() );
		sleep(1);
		printf("%s,%s,%d (%d)\n",__FILE__,__func__,__LINE__,func_d() );
		sleep(1);
		printf("%s,%s,%d (%d)\n",__FILE__,__func__,__LINE__,func_d() );
		sleep(1);
	}
	
	return 0;
}
