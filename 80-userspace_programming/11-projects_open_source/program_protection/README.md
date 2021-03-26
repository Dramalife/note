> note "program_protection" related file
> Copyright (C) 2019 Dramalife <dramalife@live.com>
>
> This file is part of [note](https://github.com/Dramalife/note.git)
>
> note is distributed in the hope that it will be useful, but
> WITHOUT ANY WARRANTY; without even the implied warranty of
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
>
> $ gcc --version
> gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
> Copyright (C) 2019 Free Software Foundation, Inc.
> This is free software; see the source for copying conditions.  There is NO
> warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.;
>
> $ uname -a
> Linux NanoPi-M4 4.19.111 #4 SMP PREEMPT Tue Oct 20 13:17:49 CST 2020 aarch64 aarch64 aarch64 GNU/Linux
> ;
>
> Init : Fri Mar 26 23:19:58 CST 2021
>
> ​		添加说明文档与运行日志;
>
> Update : Fri Mar 26 23:19:58 CST 2021
>
> Update
>
> 

第一版在2020年5月完成，在gitee的个人闭源仓库中。



### 简介

监控程序的函数调用流程，不修改程序文件或者修改源码后编译。

实用场景：

- 检测程序是否被反汇编后修改逻辑；
- 在不方便使用gdb的嵌入式设备中，起到调试程序的辅助作用；



也尝试过使用ptrace（gdb的实现原理）实现，未果，后续更新。



### 技术点介绍

#### LD_PRELOAD 和 backtrace

实现效果：程序执行例如printf函数时，会先把栈回溯发送到server，再调用libc中的具体实现，即在不影响功能的前提下，发送栈回溯。

```c
//根据libc中printf函数的声明，声明一个PRINTF类型的函数指针；
typedef int (*PRINTF)(const char *format, ...);
//定义PRINTF类型的函数指针
PRINTF printf_glibc = NULL;
//定义hook函数
int printf(const char *format, ...)
{
    //打开libc，并找到其中符号printf的地址
	void *handle = dlopen("libc.so.6", RTLD_LAZY);
	printf_glibc = (PRINTF)dlsym(handle, "printf");
	
	get_stack_backtrace();

	va_list ap;
	char buff[256]={0};
	va_start(ap, format);
	vsnprintf(buff, sizeof(buff), format, ap);
	va_end(ap);

    //执行完上述自定功能后，传递参数到libc的printf中
	int ret = printf_glibc(buff);
	return ret;
}
```



#### 栈回溯的分析（本质是字符串解析）

```log
backtrace() returned 4 addresses
==>main 
for_gdb.c,main,39 
for_gdb.c,func_a,19 
backtrace() returned 6 addresses
==>func_a 
==>func_c 
==>main 
dlhook.c  dlhook.h  for_gdb.ass  for_gdb.c  for_gdb.out  libdlhook.so  makefile
backtrace() returned 5 addresses
==>func_c 
==>main 
for_gdb.c,main,42 (1804289383)
for_gdb.c,func_b,24 
backtrace() returned 6 addresses 注意，这里屏蔽了于分析无用的动态库中的函数名
==>func_b 
==>func_d 
==>main 
backtrace() returned 5 addresses
==>func_d 
==>main 
for_gdb.c,main,44 (846930886)
for_gdb.c,func_a,19 
backtrace() returned 6 addresses
==>func_a 
==>func_c 
==>main
```



#### 部分ARM架构的平台，栈回溯获取不到的问题

添加这些编译选项即可解决：-rdynamic -funwind-tables -ffunction-sections





### server进程的说明

```log
Pdd.c

主循环中，接收来自unix socket的消息，每一条消息的内容为一个函数名或者栈开始与结束的标识。例：
函数名：my.out main()，关键数据，用于分析；
开始/结束标识：“####START/END####”，用于截取一段完整的backtrace；

至此，可以拿到一段完整的backtrace（栈回溯）；
但是，这些backtrace可能来自同一个函数层级的多个hook函数（以printf为例），即重复的情况；
也有可能来自完整调用栈的中间函数，比如完整的调用关系为main->funa（printf * n）->funx->funy,
但是当前获取的backtrace来自funa或者funx；
我们期待的是main->funa->funx->funy，完整且最深的调用栈。

proc_recode函数是进行分析的入口：
1.如果收到的是函数名数据，则存入本地数据结构栈中，用于分析；
2.如果接收到的是结束标识，说明已经获取了hooklib发来的完整backtrace，但是注意，这个backtrace大概率不是最深调用栈；此时调用comp_records函数，来比较当前栈cur与上一个接收到的栈old；
3.如果接收到的是开始标识，初始化临时内存；

comp_records函数是获取完整最深栈的方法，以函数栈的大小为第一层判断依据：
1.如果old为空，说明cur是接收到的第一个backtrace，移动cur到old，等待下次判断；

2.如果old栈高小于cur：
a)如果cur包含old，说明old不是最深栈，而cur要等下次判断；
b)如果cur不包含old，判读STAGE_DES，如果成立则移动数据，否则说明old是上一个最深栈要进行分析 ；

3.如果old栈高等于cur：
a)如果old内容与cur相同，说明这两个栈回溯来自同一个函数的同一级，移动cur到old，等待下次判断；
b)如果old内容与cur不同，判断STAGE_DES，成立则移动数据，否则说明old是上一个最深栈要进行分析；

4.如果old栈高大于cur：
a)如果old包含cur，可能old是最深栈，而cur是上一级函数中的栈回溯，此时old为最深栈要进行分析 并设置flag，以保证一直到最靠近main的调用为止不会被重复认为是最深栈；
b)如果old不包含cur，old为最深栈需要进行分析；
```



### 完整的功能验证流程

#### 0 Prepare
```bash
# Hit rate calculation
# 这个脚本比较自定义库中的hook函数与目标程序文件的符号表，从而估算能被检测到的函数数量；
./hit_rate.sh libdlhook.so for_gdb.out
```

#### 1 Library
```bash
# Compile hooked lib
# 编译自定义的库函数，主要是定义libc中的同名函数，获取栈回溯；
make lib_bt
```

#### 2 Target Program
```bash
# Compile App
# Sample : xxxxx.c
make compile_myapp FNAME=xxxxx

# Exec App
# Sample : xxxxx.out
# 原理是运行程序前设置PRE_LOAD，来预先加载自定义的库
make run_myapp APP_PATH=./xxxxx.out
```

#### 3 Server Program
```bash
# Compile & Exec Program Detect Daemon
# Sample legal process name : default.df
make pdd
./pdd default.df
```

#### 4 Sample - my.c
```bash
make lib_bt
make compile_myapp FNAME=my
make pdd

# Terminal 1
./pdd.out my.df

# Terminal 2
make run_myapp APP_PATH=./my.out
```





### 命中率分析

hook的库函数越多，获取到的栈回溯越完整，函数调用流程越详细。

比如，当只hook掉printf函数时，就只能监测到“调用了printf的函数”的栈回溯。没有调用的流程不会被检测到。