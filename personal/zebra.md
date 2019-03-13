**Note Zebra**

|No|||
|--|--|--|
|0|Zebra进程函数不能有阻塞|Zebra的thread不是线程，只是添加到在while(1)中按序执行|
|1|Zebra while循环|**while循环**可以通过在函数结尾thread_add_timer(自己)等实现|
|2|THREAD_OFF|如果关闭自己这个“线程”，程序会退出，其定义中有exit|
|3||printf样式字符串和变量类型不对应，可能导致内存泄漏：%s->int|
|4||使用未定义的指针?内存泄漏|
