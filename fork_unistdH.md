|no|define|include|other|
|--|--|--|--|
|0|pid_t fork( void);|#include <unistd.h>  #include<sys/types.h>||
#### RETURN
若成功调用一次则返回两个值，子进程返回0，父进程返回子进程ID；否则，出错返回-1
```
1）当前的进程数已经达到了系统规定的上限，这时errno的值被设置为EAGAIN。
2）系统内存不足，这时errno的值被设置为ENOMEM。
```
#### pid_t
pid_t 是一个宏定义，其实质是int 被定义在#include<sys/types.h>中
#### 说明
1. 在语句fpid=fork()之前，只有一个进程在执行这段代码，但在**这条语句之后**，就变成两个进程在执行了，这两个进程的几乎完全相同
3. 为什么不是从#include处开始复制代码的，这是因为fork是把进程当前的情况拷贝一份
4. 这两个进程执行没有固定的先后顺序,哪个进程先执行要看系统的进程调度策略。
5. 可以使用wait或 waitpid函数让父进程等待子进程的结束并获取子进程的返回状态。
#### [原文链接]（https://www.cnblogs.com/jycboy/p/l_fork.html）
