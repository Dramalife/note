> \# note "tree" related file  
\# Copyright (C) 2019 Dramalife  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#   
\# Init : 2019.05.14 ;   
\# Update : 2019.09.15 ;   



|no|-|content|
|--|--|--|
|0||Linux                   |
|1||tools                   |
|2||tree                    |
|3|author|dramalife@live.com|

#### 1. Download source code / 下载源码

```bash
wget ftp://mama.indstate.edu/linux/tree/tree-1.6.0.tgz
```

#### 2. Configure, compile and install / 配置，编译，安装

```bash
# decompress and cd / 解压，进入目录
make //compile
make install //安装
```

#### 3. Environment / 环境变量

```bash
vi ~/.bash_profile
# Add the line below to the file opened
export PATH=$PATH:/home/user/xxx
```

#### 4. use

```
# Sample / 在代码顶层目录执行
tree
```

