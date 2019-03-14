信号量（semaphore）与已经介绍过的 IPC 结构不同，它是一个计数器。信号量用于实现进程间的互斥与同步，而不是用于存储进程间通信数据。

### 1、特点
信号量用于进程间同步，若要在进程间传递数据需要结合共享内存。  
信号量基于操作系统的 PV 操作，程序对信号量的操作都是原子操作。  
每次对信号量的 PV 操作不仅限于对信号量值加 1 或减 1，而且可以加减任意正整数。  
支持信号量组。  

### 2、原型
最简单的信号量是只能取 0 和 1 的变量，这也是信号量最常见的一种形式，叫做二值信号量（Binary Semaphore）。而可以取多个正整数的信号量被称为通用信号量。  
Linux 下的信号量函数都是在通用的信号量数组上进行操作，而不是在一个单一的二值信号量上进行操作。
```c
#include <sys/sem.h>
// 创建或获取一个信号量组：若成功返回信号量集ID，失败返回-1
int semget(key_t key, int num_sems, int sem_flags);
// 对信号量组进行操作，改变信号量的值：成功返回0，失败返回-1
int semop(int semid, struct sembuf semoparray[], size_t numops);  
// 控制信号量的相关信息
int semctl(int semid, int sem_num, int cmd, ...);
```
#### semget
创建新的信号量集合时，必须指定集合中信号量的个数（即num_sems），通常为1； 如果是引用一个现有的集合，则将num_sems指定为 0 。  
在semop函数中，sembuf结构的定义如下：  
```c
struct sembuf
{
  short sem_num; // 信号量组中对应的序号，0～sem_nums-1
  short sem_op;  // 信号量值在一次操作中的改变量
  short sem_flg; // IPC_NOWAIT, SEM_UNDO
}
```
#### sem_op
是一次操作中的信号量的改变量：  
**1. 若sem_op > 0** ,表示进程释放相应的资源数，将 sem_op 的值加到信号量的值上。如果有进程正在休眠等待此信号量，则唤醒它们。  
**2. 若sem_op < 0** ,请求 sem_op 的绝对值的资源  
- 如果相应的资源数可以满足请求,则将该信号量的值减去sem_op的绝对值，函数成功返回。  
- 当相应的资源数不能满足请求时,这个操作与sem_flg有关:  
  - sem_flg 指定IPC_NOWAIT，则semop函数出错返回EAGAIN。  
  - sem_flg 没有指定IPC_NOWAIT，则将该信号量的semncnt值加1，然后进程挂起直到下述情况发生：
    - 当相应的资源数可以满足请求，此信号量的semncnt值减1，该信号量的值减去sem_op的绝对值。成功返回；  
    - 此信号量被删除，函数smeop出错返回EIDRM；  
    - 进程捕捉到信号，并从信号处理函数返回，此情况下将此信号量的semncnt值减1，函数semop出错返回EINTR  

**3. 若sem_op == 0** ,进程阻塞直到信号量的相应值为0
- 当信号量已经为0，函数立即返回。
- 如果信号量的值不为0，则依据sem_flg决定函数动作：
  - sem_flg指定IPC_NOWAIT，则出错返回EAGAIN。
  - sem_flg没有指定IPC_NOWAIT，则将该信号量的semncnt值加1，然后进程挂起直到下述情况发生：
      - 信号量值为0，将信号量的semzcnt的值减1，函数semop成功返回；
      - 此信号量被删除，函数smeop出错返回EIDRM；
      - 进程捕捉到信号，并从信号处理函数返回，在此情况将此信号量的semncnt值减1，函数semop出错返回EINTR  

#### semctl
函数中的命令有多种，这里就说两个常用的：
 SETVAL：用于初始化信号量为一个已知的值。所需要的值作为联合semun的val成员来传递。在信号量第一次使用之前需要设置信号量。
 IPC_RMID：删除一个信号量集合。如果不删除信号量，它将继续在系统中存在，即使程序已经退出，它可能在你下次运行此程序时引发问题，而且信号量是一种有限的资源。
