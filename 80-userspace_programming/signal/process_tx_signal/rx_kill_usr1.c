#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler_sig_usr(int sig)
{ 
	printf("[%s] Received SIGUSR1(%d)\n",__FILE__,sig);
}

int main(void)
{ 
	printf("\n");

	if( signal(SIGUSR1, handler_sig_usr) == SIG_ERR ) 
	{  
		printf("[%s] signal error \n",__FILE__);

	}  

	printf("[%s] My pid(%d) \n",__FILE__,getpid());

	pause();// pause - wait for signal

	printf("[%s] I am going done. \n",__FILE__);

	return 0;
}
