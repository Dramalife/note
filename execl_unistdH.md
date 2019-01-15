|no|define|include|other|
|--|--|--|--|
|0|int execl(const char *path, const char *arg, ...);|#include <unistd.h>||

###
```
execl函数特点:
        当进程调用一种exec函数时，该进程完全由新程序代换，而新程序则从其main函数开始执行。因为调用exec并不创建新进程，所以前后的进程ID并未改变。exec只是用另一个新程序替换了当前进程的正文、数据、堆和栈段。
用另一个新程序替换了当前进程的正文、数据、堆和栈段。
当前进程的正文都被替换了，那么execl后的语句，即便execl退出了，都不会被执行。
---------------------
[原文](https://blog.csdn.net/hongkangwl/article/details/21341971)
```
