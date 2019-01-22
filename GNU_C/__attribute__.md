#### referenced Dramalife
|no|path|Remarks|
|0|/README.md||
|1|/note/CMD-CLI.md||

### analysis
|No|Keyword|Content|
|--|--|--|
|0|who|Dramalife|
|1|section|驱动加载__init,,存放在.initlist段|

### 概述
```
GNU C的一大特色（却不被初学者所知）就是__attribute__机制。
__attribute__可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。
大致有六个参数值可以被设定，即：aligned, packed, transparent_union, unused, deprecated 和 may_alias 。
```
[主要参考url](https://blog.csdn.net/tang_jin_chan/article/details/9079373)

### unused
- This attribute, attached to a function, means that the function is meant to be possibly unused. GCC will not produce a warning for this function.

### section
[sample-section](https://github.com/Dramalife/note/blob/master/GNU_C/sample/attribute_section.md)
使用格式为：
```
__attribute__((section("section_name")))
```
其作用是将作用的函数或数据放入指定名为"section_name"输入段。
这里还要注意一下两个概念：输入段和输出段
输入段和输出段是相对于要生成最终的elf或binary时的Link过程说的，Link过程的输入大都是由源代码编绎生成的目标文件.o，那么这些.o文件中包含的段相对link过程来说就是输入段，而Link的输出一般是可执行文件elf或库等，这些输出文件中也包含有段，这些输出文件中的段就叫做输出段。输入段和输出段本来没有什么必然的联系，是互相独立，只是在Link过程中，Link程序会根据一定的规则（这些规则其实来源于Link Script），将不同的输入段重新组合到不同的输出段中，即使是段的名字，输入段和输出段可以完全不同。
