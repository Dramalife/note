# note coding-tree related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


no|-|content|
--|--|--
0||Linux
1||tools
2||tree
3|author|dramalife@live.com
---
#### 下载源码
```
wget ftp://mama.indstate.edu/linux/tree/tree-1.6.0.tgz
```
#### 配置，编译，安装
解压，进入目录
```
# make //compile
# make install //安装
```
#### 环境变量
如果没有执行 make install

vi ~/.bash_profile
```
export PATH=$PATH:/home/user/xxx
```
#### use
在代码顶层目录执行
```
# tree
```
