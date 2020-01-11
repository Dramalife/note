### SOURCE
THE LINUX PROGRAMMING INTERFACE (TLPI), Chapter 63 .

### KEYWORDS
I/O multiplexing
Signal driven I/O

### Diff
|名称		|APIs			|man							|tlpi_name	|demo_path|
|--|--|--|--|--|
|I/O多路复用	|select(2), poll(2)	|synchronous I/O multiplexing				|altio		|[multio](/80-userspace_programming/io/multiplexing_io)|
|信号驱动I/O	|fcntl(2),signal(2)  	|manipulate file descriptor;ANSI C signal handling	|sigio		|[sigio](/80-userspace_programming/io/signal_io)|


### Learning log
|Date	|Events	|
|--|--|
|2020.01.05 |compile multiplexing_io	successfully|
|2020.01.09 |compile signal_io		successfully|
