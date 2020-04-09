/*
 * SRC : https://www.runoob.com/cplusplus/cpp-multithreading.html
 */
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define NUM_THREADS     5

#define DEBUG_SW	1

void *work_thread(void *t)
{
	int i;
#if 0
	long tid;
	tid = (long)t;
#else
	int tid;
	tid = *(int *)t;
#endif


	sleep(1);
#if 0
	cout << "Sleeping in thread " << endl;
	cout << "Thread with id : " << tid << "  ...exiting " << endl;
#else
	//printf("\nSleeping in thread \n");
	printf("[%s,%d] Thread with id : %d ...exiting \n",__func__,__LINE__,tid);
#endif
	pthread_exit(NULL);
}

int main ()
{
	int rc;
	int i;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	void *status;

	// 初始化并设置线程为可连接的（joinable）
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for( i=0; i < NUM_THREADS; i++ ){
		//cout << "main() : creating thread, " << i << endl;
		printf("[%s,%d] creating thread (%d) \n", __func__,__LINE__,i);
		rc = pthread_create(&threads[i], NULL, work_thread, (void *)&i );
		if (rc){
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}

	// 删除属性，并等待其他线程
	pthread_attr_destroy(&attr);
	for( i=0; i < NUM_THREADS; i++ ){
		rc = pthread_join(threads[i], &status);
		if (rc){
			cout << "Error:unable to join," << rc << endl;
			exit(-1);
		}
		//cout << "Main: completed thread id :" << i << endl;
		//cout << "  exiting with status :" << status << endl;
		printf("[%s,%d] thread (%d) completed, exit(%d) \n",__func__,__LINE__,i, (int)status );
	}

	//cout << "Main: program exiting." << endl;
	printf("%s,%d exit. \n",__func__,__LINE__);
	pthread_exit(NULL);
}
