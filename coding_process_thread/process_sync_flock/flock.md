>借助 fcntl 函数来实现文件锁。操作文件的进程没有获得锁时，可以打开，但无法执行 read,write 操作。
fcntl 函数：获取、设置文件访问控制属性。

```c
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, ... /* arg */ );
```

**参数 2 ：**  

```c
F_SETLK(struct flock *);  //设置文件锁 ( trylock )
F_SETLKW(struct flock*);  //设置文件锁（ lock ） W --- wait 
F_GETLK(struct flock*);   //获取文件锁
```

**参数 3：**  

```c
struct flock {
      //...
      short l_type;    /* Type of lock: F_RDLCK, F_WRLCK, F_UNLCK */
      short l_whence;  /* How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END */
      off_t l_start;   /* Starting offset for lock */
      off_t l_len;     /* Number of bytes to lock */
      pid_t l_pid;     /* PID of process blocking our lock (F_GETLK only) */
      //...
};
```
