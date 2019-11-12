/*
*
* once_run()函数仅执行一次，且究竟在哪个线程中执行是不定的，尽管pthread_once(&once,once_run)出现在两个线程中
*/

#include <stdio.h>
#include <pthread.h>

pthread_once_t  once=PTHREAD_ONCE_INIT;

void once_run(void)
{
        printf("[%s,%d]once_run in thread %d\n",__func__,__LINE__,pthread_self());
}

void *child1(void *arg)
{
        int tid=pthread_self();

        printf("[%s,%d]thread %d enter\n",__func__,__LINE__,tid);
        pthread_once(&once,once_run);
        printf("[%s,%d]thread %d returns\n",__func__,__LINE__,tid);
}

void *child2(void *arg)
{
        int tid=pthread_self();

        printf("[%s,%d]thread %d enter\n",__func__,__LINE__,tid);
        pthread_once(&once,once_run);
        printf("[%s,%d]thread %d returns\n",__func__,__LINE__,tid);
}

int main(void)
{
        int tid1,tid2;

        printf("[%s,%d]hello\n",__func__,__LINE__);

        pthread_create(&tid1,NULL,child1,NULL);
        pthread_create(&tid2,NULL,child2,NULL);

        sleep(10);

        printf("[%s,%d]main thread exit \n",__func__,__LINE__);

        return 0;
}
