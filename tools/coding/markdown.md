```bash
# note coding-markdown related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

#### referenced Dramalife

|no|path|Remarks|
|--|--|--|
|0|/README.md||
|-|-|-|
[TODO](https://www.jianshu.com/p/40ba812dd973)
#### 实现标准
```
MarkDown 没有统一标准，不同网站实现的方式不同；
GitHub 实现的 MarkDown 语法叫 GFM，GitHub Favorite MarkDown；
GFM 比普通的 MarkDown 语法增加了表格和完成列表，等语法；
但是，GFM 并没有实现流程图的 MarkDown 语法。
```

# 这是一级标题
## 这是二级标题
### 这是三级标题
#### 这是四级标题
##### 这是五级标题
###### 这是六级标题

**这是加粗的文字**
*这是倾斜的文字*`
***这是斜体加粗的文字***
~~这是加删除线的文字~~

换行
有一些引擎在渲染机制上是有出入的，直接回车不能换行，
但是你可以在上一行文本后面补两个空格，
这样下一行的文本就换行了。  
或者就是在两行文本直接加一个空行。

也能实现换行效果，不过这个行间距有点大。

>这是引用的内容
>>这是引用的内容
\>>>>>>>>>>这是引用的内容

`分割线三个或者三个以上的 - 或者 * 都可以`
---
----
***
*****
### 链接
![图片alt](图片地址 ''图片title'')
图片alt就是显示在图片下面的文字，相当于对图片内容的解释。
图片title是图片的标题，当鼠标移到图片上时显示的内容。title可加可不加
#### 图片示例：
语法：!\[blockchain\]\(https://ss0.bdstatic.com/70cFvHSh_Q1YnxGkpoWK1HF6hhy/it/u=702257389,1274025419&fm=27&gp=0.jpg "区块链")  

![blockchain](https://ss0.bdstatic.com/70cFvHSh_Q1YnxGkpoWK1HF6hhy/it/u=702257389,1274025419&fm=27&gp=0.jpg "区块链")

#### 链接外部URL
|语法|效果|
|-|-|
|\[简书](http://jianshu.com)  |[简书](http://jianshu.com)|
|\[百度](http://baidu.com)|[百度](http://baidu.com)|
#### 链接本仓库里的URL
|语法|效果|
|-|-|
|\[我的简介](/example/profile.md)|[我的简介](/example/profile.md)|
|\[Book](./Book)|[Book](./Book)|

`无序列表用 - + * 任何一种都可以`
- 列表内容
  - 二级
    - 三级
+ 列表内容
* 列表内容

1.列表内容
2.列表内容
3.列表内容
`注意：序号跟内容之间要有空格`


列表嵌套
上一级和下一级之间敲三个空格即可


表头|表头|表头
---|:--:|---:
内容|内容|内容
内容|内容|内容

第二行分割表头和内容。
“\-” 有一个就行，为了对齐，多加了几个
文字默认居左
“\-”两边加：表示文字居中
“\-”右边加：表示文字居右
注：原生的语法两边都要用 | 包起来。此处省略

### Block
`code line`
```
code block:c,shell,diff...
```
```c
int main(void);
//c code clock
```

```shell
ls -al
```

```diff
+hello
-hi
```
