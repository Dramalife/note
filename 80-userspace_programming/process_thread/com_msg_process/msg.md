>消息队列，是消息的链接表，存放在内核中。一个消息队列由一个标识符（即队列ID）来标识。

### 一、 特点
1. 消息队列是面向记录的，其中的消息具有特定的格式以及特定的优先级。  
2. 消息队列独立于发送与接收进程。进程终止时，消息队列及其内容并不会被删除。  
3. 消息队列可以实现消息的随机查询,消息不一定要以先进先出的次序读取,也可以按消息的类型读取。  

### 二、 原型
```c
#include <sys/msg.h>
// 创建或打开消息队列：成功返回队列ID，失败返回-1
int msgget(key_t key, int flag);
// 添加消息：成功返回0，失败返回-1
int msgsnd(int msqid, const void *ptr, size_t size, int flag);
// 读取消息：成功返回消息数据的长度，失败返回-1
int msgrcv(int msqid, void *ptr, size_t size, long type,int flag);
// 控制消息队列：成功返回0，失败返回-1
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

在以下两种情况下，msgget将创建一个新的消息队列：  
- 如果没有与键值key相对应的消息队列，并且flag中包含了IPC_CREAT标志位。
- key参数为IPC_PRIVATE。  

函数msgrcv在读取消息队列时，type参数有下面几种情况：  
- type == 0，返回队列中的第一个消息；  
- type > 0，返回队列中消息类型为 type 的第一个消息；
- type < 0，返回队列中消息类型值小于或等于 type 绝对值的消息，如果有多个，则取类型值最小的消息。  

可以看出，type值非 0 时用于以非先进先出次序读消息。也可以把 type 看做优先级的权值。
