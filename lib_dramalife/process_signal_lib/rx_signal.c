#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "process_signal_lib.h"


void sample_handler_process_signal(int sig)
{ 
	printf("[%s] Received SIGUSR1(%d)\n",__FILE__,sig);
}

int main(void)
{ 
	printf("\n");

	if( signal(SIGUSR1, sample_handler_process_signal) == SIG_ERR ) 
	{  
		printf("[%s] signal error \n",__FILE__);

	}  

	printf("[%s] My pid(%d) \n",__FILE__,getpid());

	pause();// pause - wait for signal

	printf("[%s] I am going done. \n",__FILE__);

	return 0;
}
