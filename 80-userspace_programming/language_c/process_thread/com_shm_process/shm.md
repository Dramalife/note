#### 1 共享内存的基本概念
　共享内存区是最快的IPC形式。一旦这样的内存映射到共享它的进程的地址空间，这些进程间数据传递不再涉及到内核，换句话说是进程不再通过执行进入内核的系统调用来传递彼此的数据。
  内核为每个IPC(pipe,FIFO,消息队列)对象维护一个数据结构。


System V共享内存API:

首先了解一下下面结构体
```c
struct shmid_ds {
     struct ipc_perm shm_perm;    /* Ownership and permissions */
     size_t          shm_segsz;   /* Size of segment (bytes) */
     time_t          shm_atime;   /* Last attach time */
     time_t          shm_dtime;   /* Last detach time */
     time_t          shm_ctime;   /* Last change time */
     pid_t           shm_cpid;    /* PID of creator */
     pid_t           shm_lpid;    /* PID of last shmat(2)/shmdt(2) */
     shmatt_t        shm_nattch;  /* No. of current attaches */
     /*...*/
     };
```
共享内存函数
```c
#include <sys/ipc.h>
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);
void *shmat(int shmid, const void *shmaddr, int shmflg);
int shmdt(const void *shmaddr);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```
下面依次介绍一下上述函数的一些使用方法

**shmget函数**  
功能：用来创建共享内存  
原型：
```c
int shmget(key_t key, size_t size, intshmflg);
```
参数：  
  key:这个共享内存段名字
  size:共享内存大小  
shmflg:由九个权限标志构成，它们的用法和创建文件时使用的mode模式标志是一样的  
返回值：成功返回一个非负整数，即该共享内存段的标识码；失败返回-1  

**shmat函数**  
功能：将共享内存段连接到进程地址空间  
原型：
```c
void *shmat(intshmid, const void *shmaddr, intshmflg);
```
参数：  
  shmid: 共享内存标识  
  shmaddr:指定连接的地址  
  shmflg:它的两个可能取值是SHM_RND和SHM_RDONLY  
返回值：成功返回一个指针，指向共享内存第一个节；失败返回-1  

shmaddr为NULL，核心自动选择一个地址  
shmaddr不为NULL且shmflg无SHM_RND标记，则以shmaddr为连接地址。  
shmaddr不为NULL且shmflg设置了SHM_RND标记，则连接的地址会自动向下调整为SHMLBA的整数倍。公式：shmaddr - (shmaddr % SHMLBA)  
shmflg=SHM_RDONLY，表示连接操作用来只读共享内存  

**shmdt函数**  
功能：将共享内存段与当前进程脱离  
原型：
```c
int shmdt(const void *shmaddr);
```
参数：  
    shmaddr: 由shmat所返回的指针  
返回值：成功返回0；失败返回-1  
注意：将共享内存段与当前进程脱离不等于删除共享内存段  
**shmctl函数**  
功能：用于控制共享内存  
原型：
```c
int shmctl(intshmid, intcmd, structshmid_ds *buf);
```
参数：  
    shmid:由shmget返回的共享内存标识码  
    cmd:将要采取的动作（有三个可取值）  
    buf:指向一个保存着共享内存的模式状态和访问权限的数据结构  
返回值：成功返回0；失败返回-1  
