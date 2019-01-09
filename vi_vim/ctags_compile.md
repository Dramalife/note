no|-|content|
--|--|--
0||Linux
1||tools
2||ctags
3|author|dramalife@live.com
---
#### 下载源码
```
http://ctags.sourceforge.net
```
#### 配置，编译，安装
解压，进入目录
```
# ./configure //自动生成makefile
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
# ctags -R //-R递归
```
生成tags文件，在有tags文件的目录运行vi，如
```
# vi ./apps/cell/cell_card.h
```

在VIM中

no|keys|func|
--|--|--|
0|ctrl + ]|jump to def|
1|g + ]|list def
