ioctl在socket中的一些用法及示例

```
函数 : ioctl(int fd, int request, void * arg)
定义 : <sys/ioctl.h>
功能 : 控制I/O设备, 提供了一种获得设备信息和向设备发送控制参数的手段.
参数 : int  fd      文件句柄. 用于socket时, 是socket套接字.
       int  request 函数定义的所有操作. 关于socket的操作, 定义在<linux/sockios.h>文件中.
       void *arg    指针的类型依赖于request参数.
```
