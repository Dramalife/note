### 1/内核态->用户态
在kernel module中调用printk是最简单的传递信息到用户空间的方法。  
### 2/用户态->内核态
在linux中，用户对设备的操作往往被抽象为对文件的操作。利用这一特性，可以通过注册和实现伪字符设备到内核，来实现用户进程和内核空间的交互。当在用户空间执行对该伪设备的open/read/write/ioctl/mmap/release等操作时，这些被复用的系统调用就会使进程从用户态进入到内核态，从而在内核中完成事先注册的操作
```c
      int register_chrdev(unsigned int major, const char *name, struct file_operations *fops);

      static inline void unregister_chrdev(unsigned int major, const char *name)
```
### 3/内核态->用户态
内核态中，可以完成对用户文件系统任意文件的访问。因此，可以在内核态将要输出的信息写入文件，写入后用户态程序直接读取文件就可以完成从内核空间向用户空间的数据传递。
### 4/内核态<->用户态
proc文件系统，是当前内核或内核模块，和用户交互的主要方式，它通过将虚拟的文件系统挂载在/proc下，利用虚拟文件读写在用户和内核态间传递信息。通过内核模块，可以向/proc下注册新的文件，指定用户读写该文件时的回调函数；这样，当用户读写该文件时，工作在内核态的回调函数就可以执行信息交互的有关工作。
向内核中注册/proc下文件的调用是create_proc_entry 
### 5/内核态<->用户态 netlink
netlink是一种特殊的socket，用于用户态与内核态的双向通讯。在实现用户和内核交互的各种方式中，netlink的主要特点得意于它继承了 socket的一些基本特性，包括异步通讯，多播，双向性，不需要额外的文件。在用户态中，netlink的使用与标准的socket API相同，在内核态，则需要使用专门的API。  
在内核态，通过netlink_kernel_create可以在内核中新建socket结构并注册接收到消息的回调函数input，其原型为：
```c
      struct sock *netlink_kernel_create(int unit, void (*input)(struct sock *sk, int len));
      void sock_release(struct socket *sock)
```

[reference](https://blog.csdn.net/linseeker85/article/details/86599507)  
