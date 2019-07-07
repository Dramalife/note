1. 模块都是事件驱动的，不像有些应用程序那样顺序地执行；
2. 模块的退出函数必须撤销初始化函数所做的一切；
3. 模块仅仅被链接到内核，因此它能调用的函数仅仅是内核导出的那些函数，而不存在任何可被链接的函数库；
4. 在模块中使用函数调用和函数指针，从而为运行中的内核增加新的功能；
5. 一个内核错误即使不影响整个系统，也至少会杀死当前进程；
6. 内核代码不能实现浮点数运算（可以打开支持）；
7. 内核API中“\_\_”前缀的函数，通常是接口的底层组件，应谨慎使用。
8. 内核是一个大的、独立的程序，为了将它的各个片段放在一起，要满足很多详细而明确的要求。
>《Linux Device Drivers》  

### 内核中的并发
1. Linux内核代码（包括驱动程序代码）必须是可重入的；
2. Linux系统中通常正在运行多个并发进程，并且可能有多个进程同时使用我们的驱动程序；
3. 内核代码（几乎）始终不能假定在给定代码段中能够独占处理器；

### 编译模块
1. 具备了正确版本的编译器、模块工具和其他必要的工具。（Documentation/Changes文件列出了需要的工具版本）
2. 内核源代码对编译器作了大量假定；
3. 内核源代码树：  
**编译**
```makefile
obj-m := module.o
module-objs := file1.o file2.o
```
```bash
make -C /KERNEL/kernel-2.6 M='pwd' modules
#首先改变到-C指定的位置（内核源代码目录），其中保存有内核的顶层makefile文件。
#M=选项让该makefile在构造modules目标之前返回到模块源代码目录。
#然后，modules目标指向obj-m变量中设定的模块；上述例子中该变量为module.o  
```
内核开发者开发了一种makefile方法，使得内核树之外的模块构造变得更加容易：  
```makefile
#如果已定义KERNELRELEASE，则说明是从内核构造系统调用的，
#因此可以利用其内建语句。
ifneq ($(KERNELRELEASE),)
  obj-m := hello.o  
#否则，是直接从命令行调用的，
#这时要调用内核构造系统
else
  KERNELDIR ?= /lib/modules/$(shell uname -r)/build
  PWD := $(shwll pwd)
default:
  $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
```
