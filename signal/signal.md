## SIGNAL
|信号数字|信号名|detail|
|--|--|--|
||SIG_IGN|ignore signal|
||SIG_DFL|default signal handling|
||SIGPIPE|当服务器close一个连接时，若client端接着发数据。根据TCP协议的规定，会收到一个RST响应，client再往这个服务器发送数据时，系统会发出一个SIGPIPE信号给进程，告诉进程这个连接已经断开了，不要再写了。|
||SIGCHLD|子进程退出的时候会向其父进程发送一个SIGCHLD信号，linux下的[僵尸进程处理(Dramalife.git)](https://github.com/Dramalife/note/blob/master/thread/child_signal.md)SIGCHLD信号|
||SIGINT|程序终止信号，\[Ctrl+C , kill -2 or kill -SIGINT\]|
||SIGSEGV|Segmentation fault|
||SIGPIPE|Broken pipe|
||SIGBUS|Bus error|
||SIGILL|Illegal instruction|
||SIGFPE|Floating point exception|
||SIGABRT|多次free;abort;assert;堆越界|
