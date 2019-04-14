>进程间也可以使用互斥锁 ，来达到同步的目的。但应在 pthread_mutex_init 初始化之前，修改其属性为进程间共享。mutex 的属性修改函数主要有以下几个。

**主要应用函数：**  
1、pthread_mutexattr_t   mutexattr 类型： 用于定义互斥锁的属性。  
2、pthread_mutexattr_init 函数：               初始化一个 mutex 属性对象  
```c
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
```
3、pthread_mutexattr_destroy 函数：        销毁 mutex 属性对象（而非销毁锁）  
```c
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
```
4、pthread_mutexattr_setpshared 函数：   修改 mutex 属性
```c
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr,int pshared);
```
   参数 2 ：pshared 取值：
   线程锁： PTHREAD_PROCESS_PRIVATE（ mutex 的默认属性即为线程锁，进程间私有）
   进程锁：PTHREAD_PROCESS_SHARED



[原文链接](https://blog.csdn.net/qq_35396127/article/details/78942245)
