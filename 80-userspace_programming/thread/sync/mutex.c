/*
 * note "Thread - Sync - Mutex" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux iZ2zeeq1jai7e6qn7xqrnuZ 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Thu Feb 18 17:30:02 CST 2021
 * 	Ref : "The Linux Programming Interface";
 * Update : Thu Feb 18 17:30:02 CST 2021
 *  
 * Update
 *
 */


/*****
 * 死锁 (Dead Lock)
 *
 * 避免死锁
 * 1) 定义互斥量的层级关系：当多个线程对一组互斥量操作时，总是应该以相同顺序对该组互斥量进行锁定。
 * 2) 尝试一下，然后恢复：较之于按锁的层级关系来规避死锁，这种方法效率要低一些，
 *    因为可能需要历经多次循环。另一方面，由于无需受制于严格的互斥量层级关系，该方法也更为灵活。
 */


/*****
 * 属性 (Attr)
 *
 *
 ****
 * o 同一线程不应对同一互斥量加锁两次。
 * o 线程不应对不为自己所拥有的互斥量解锁（亦即，尚未锁定互斥量）。
 * o 线程不应对一尚未锁定的互斥量做解锁动作。
 * 准确地说，上述情况的结果将取决于互斥量类型（type）。SUSv3 定义了以下互斥量类型。
 *
 * 类型 (Type)
 *
 * PTHREAD_MUTEX_NORMAL
 * 	该类型的互斥量不具有死锁检测（自检）功能。如线程试图对已由自己锁定的互斥量加
 * 	锁，则发生死锁。互斥量处于未锁定状态，或者已由其他线程锁定，对其解锁会导致不确定
 * 	的结果。（在 Linux 上，对这类互斥量的上述两种操作都会成功。）
 *
 * PTHREAD_MUTEX_ERRORCHECK
 * 	对此类互斥量的所有操作都会执行错误检查。所有上述 3 种情况都会导致相关 Pthreads 函
 * 	数返回错误。这类互斥量运行起来比一般类型要慢，不过可将其作为调试工具，以发现程序
 * 	在哪里违反了互斥量使用的基本原则。
 *
 * PTHREAD_MUTEX_RECURSIVE
 * 	递归互斥量维护有一个锁计数器。当线程第 1 次取得互斥量时，会将锁计数器置 1。后续
 * 	由同一线程执行的每次加锁操作会递增锁计数器的数值，而解锁操作则递减计数器计数。只
 * 	有当锁计数器值降至 0 时，才会释放（release，亦即可为其他线程所用）该互斥量。解锁时如
 * 	目标互斥量处于未锁定状态，或是已由其他线程锁定，操作都会失败。
 *
 */

 // pthread_mutex_init
 // pthread_mutex_destroy

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_for_recursive_test(void *arg)
{
	int ret = 0;
	pthread_mutex_t *pmtx = (pthread_mutex_t *)arg;

	ret = pthread_mutex_lock(pmtx);
	printf("%s,%d ret=%d, lock\n", __func__, __LINE__, ret);

	printf("thread sleep 3 seconds...\n");
	sleep(3);

	ret = pthread_mutex_unlock(pmtx);
	printf("%s,%d ret=%d, unlock\n", __func__, __LINE__, ret);

	return NULL;
}

int test_mutex_type_recursive(void)
{
	printf("\n\n#####\n#%s\n#####\n", __func__);
	int ret = 0;

	pthread_mutex_t mtx;
	pthread_mutexattr_t mtx_attr;


	ret = pthread_mutexattr_init(&mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_RECURSIVE);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutex_init(&mtx, &mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutexattr_destroy(&mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	/* Lock 1 time */
	ret = pthread_mutex_lock(&mtx);
	printf("%s,%d ret=%d, lock\n", __func__, __LINE__, ret);

	/* Create Thread for test */
	pthread_t tid;
	ret = pthread_create(&tid, NULL, thread_for_recursive_test, &mtx);
	printf("%s,%d ret=%d, create thread!\n", __func__, __LINE__, ret);

	/* Lock 2 times */
	ret = pthread_mutex_lock(&mtx);
	printf("%s,%d ret=%d, lock\n", __func__, __LINE__, ret);
	ret = pthread_mutex_lock(&mtx);
	printf("%s,%d ret=%d, lock\n", __func__, __LINE__, ret);

	/* Unlock 3 times */
	sleep(1);
	ret = pthread_mutex_unlock(&mtx);
	printf("%s,%d ret=%d, unlock\n", __func__, __LINE__, ret);
	sleep(1);
	ret = pthread_mutex_unlock(&mtx);
	printf("%s,%d ret=%d, unlock\n", __func__, __LINE__, ret);
	sleep(1);
	ret = pthread_mutex_unlock(&mtx);
	printf("%s,%d ret=%d, unlock\n", __func__, __LINE__, ret);

	/* Join thread */
	ret = pthread_join(tid, NULL);
	printf("%s,%d ret=%d, join thread!\n", __func__, __LINE__, ret);

	printf("#####\nDestroy\n#####\n");
	ret = pthread_mutex_destroy(&mtx);
	printf("destroy mtx, ret=%d.\n", ret);

	printf("sleep 3 seconds...\n");
	sleep(3);
	return 0;
}

int test_mutex_type_errorcheck(void)
{
	printf("\n\n#####\n#%s\n#####\n", __func__);
	int ret = 0;

	pthread_mutex_t mtx;
	pthread_mutexattr_t mtx_attr;


	ret = pthread_mutexattr_init(&mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_ERRORCHECK);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutex_init(&mtx, &mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutexattr_destroy(&mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutex_lock(&mtx);
	printf("%s,%d ret=%d, lock. \nwill not block.\n", __func__, __LINE__, ret);
	ret = pthread_mutex_lock(&mtx);	// Return err
	printf("%s,%d ret=%d, lock\n", __func__, __LINE__, ret);

	printf("#####\nDestroy\n#####\n");
	/* Destroy without unlock(release) */
	ret = pthread_mutex_destroy(&mtx);
	printf("destroy mtx without release, ret=%d.\n", ret);
	ret = pthread_mutex_unlock(&mtx);
	printf("%s,%d ret=%d, unlock\n", __func__, __LINE__, ret);

	/* Destroy after unlock(release) */
	ret = pthread_mutex_destroy(&mtx);
	printf("destroy mtx, ret=%d.\n", ret);

	return 0;
}

int test_mutex_type_normal(void)
{
	printf("\n\n#####\n#%s\n#####\n", __func__);
	int ret = 0;

	pthread_mutex_t mtx;
	pthread_mutexattr_t mtx_attr;


	ret = pthread_mutexattr_init(&mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutexattr_settype(&mtx_attr, PTHREAD_MUTEX_NORMAL);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutex_init(&mtx, &mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutexattr_destroy(&mtx_attr);
	if( 0 != ret ){
		printf("%s,%d !!!\n", __func__, __LINE__);
	}

	ret = pthread_mutex_lock(&mtx);
	printf("%s,%d ret=%d, lock. \nwill block!\n", __func__, __LINE__, ret);
	ret = pthread_mutex_lock(&mtx); // Will Block
	printf("%s,%d ret=%d, lock\n", __func__, __LINE__, ret);


	printf("#####\nDestroy\n#####\n");
	ret = pthread_mutex_destroy(&mtx);
	printf("destroy mtx, ret=%d.\n", ret);

	return 0;
}

int main(int argc, char **argv)
{

	test_mutex_type_recursive();

	test_mutex_type_errorcheck();

	test_mutex_type_normal();


	return 0;
}

