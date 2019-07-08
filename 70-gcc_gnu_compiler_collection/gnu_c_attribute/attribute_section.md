```
/*
   note gcc attribute-section related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

First commit:
commit 19715134cd755c126401abf9b7a075f38f852d4a
Author: Dramalife <dramalife@live.com>
Date:   Mon Jan 21 17:17:52 2019 +0800
    //CLI接口添加新命令； 
    GNU C：attribute；
    //4g.md 格式； 
----


```



#### Referenced Dramalife
|no|path|Remarks|
|--|--|--|
|0|/README.md||
|1|/note/CMD-CLI.md||

### analysis
|No|Keyword|Content|
|--|--|--|
|0|who|Dramalife|
|1|section|驱动加载__init,,存放在.initlist段|

### [\_\_attribute\_\_((section()))](https://mp.weixin.qq.com/s?__biz=MzAwMDUwNDgxOA==&mid=2652663356&idx=1&sn=779762953029c0e0946c22ef2bb0b754&chksm=810f28a1b678a1b747520ba3ee47c9ed2e8ccb89ac27075e2d069237c13974aa43537bff4fba&mpshare=1&scene=1&srcid=0111Ys4k5rkBto22dLokVT5A&pass_ticket=bGNWMdGEbb0307Tm%2Ba%2FzAKZjWKsImCYqUlDUYPZYkLgU061qPsHFESXlJj%2Fyx3VM#rd)

#### 构建初始化函数表的原理分析

__attribute__((section(”name“)))是gcc编译器支持的一个编译特性（arm编译器也支持此特性），实现在编译时把某个函数/数据放到name的数据段中。
1. 模块通过__attribute__((section("name")))的实现，在编译时把初始化的接口放到name数据段中
2. main在执行初始化时并不需要知道有什么模块需要初始化，只需要把name数据段中的所有初始化接口执行一遍即可

首先：   
```bash
gcc -c  test.c -o test.o
```  

此时编译过程中处理了__atribute__((section(XXX)))，把标记的变量/函数放到了test.o的XXX的数据段，可用 readelf命令查询。

最后：  
```bash
ld -T <ldscript> test.o -otest.bin
```

链接时，test.o的XXX数据段（输入段），最终保存在test.bin的XXX数据段（输出段），如此在bin中构建了初始化函数表。  
由于自定义了一个数据段，而默认链接脚本缺少自定义的数据段的声明，因此并不能使用默认的链接脚本。  

ld链接命令有两个关键的选项：  
```bash
ld -T <script> #指定链接时的链接脚本
ld --verbose #打印出默认的链接脚本
```
通过”ld --verbose”获取默认链接脚本，然后修改链接脚本，添加自定义的段，最后在链接应用时通过“-T\<script\>” 指定我们修改后的链接脚本。

#### 分析内核module_init实现

##### 1. module_init的定义

module_init定义在\<include/linux/init.h\>。代码如下：
```c
//TODO
```
代码中使用的“_section_”，是一层层的宏，为了简化，把其等效理解为“section”。  
分析上述代码，我们发现module_init由__attribute__((section(“name”)))实现，把初始化函数地址保存到名为".initcall6.init" 的数据段中。

链接内核使用自定义的链接脚本

我们看到内核目录最上层的Makefile，存在如下代码：

```Makefile
# Rule to link vmlinux - also used during CONFIG_KALLSYMS
# May be overridden by arch/$(ARCH)/Makefile
quiet_cmd_vmlinux__ ?= LD      $@
cmd_vmlinux__ ?= $(LD) $(LDFLAGS) $(LDFLAGS_vmlinux) -o $@ \

      -T $(vmlinux-lds) $(vmlinux-init)                          \

      --start-group $(vmlinux-main) --end-group                  \

      $(filter-out $(vmlinux-lds) $(vmlinux-init) $(vmlinux-main) vmlinux.o FORCE ,$^)
```

本文的关注点在于：-T $(vmlinux-lds)，通过“ld -T \<script\>”使用了定制的链接脚本。定制的链接脚本在哪里呢？在Makefile存在如下代码：

```Makefile
vmlinux-lds  := arch/$(SRCARCH)/kernel/vmlinux.lds
```

我们以”ARCH=arm“ 为例，查看链接脚本：arch/arm/kernel/vmlinux.lds：
```
TODO
```

在上述代码中，我们聚焦于两个地方：

```Makefile
__initcall6_start = .; # 由__initcall6_start指向当前地址
 *(.initcall6.init) 	# 所有.o文件的.initcall6.init数据段放到当前位置
```
如此，“__initcall6_start”指向“.initcall6.init”数据段的开始地址，在应用代码中就可通过“__initcall6_start”访问数据段“.initcall6.init”。  
是不是如此呢？我们再聚焦到文件\<init/main.c\>中。  









