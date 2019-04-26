
#### 1. 缓冲
printf某些内容时，操作系统仅仅是把该内容放到了stdout的缓冲队列里了,并没有实际的写到屏幕上。
但是,只要看到有\/n 则会立即刷新stdout,因此就马上能够打印了。

#### 2. 内存泄漏
printf样式字符串和变量类型不对应，可能导致内存泄漏：%s->int

#### 3. console, terminal, tty [\[source url\]](http://blog.chinaunix.net/uid-21501855-id-3430953.html)
我们经常说的控制台，就是指控制台终端（/dev/ttyn, console，在UNIX系统中计算机显示器就叫做控制台终端）。通常pc，显示器和键盘构成控制台。  
并且控制台终端与一些设备特殊文件关联：tty0、tty1、tty2。。。ttyn  
通常情况下/dev/console与tty0关联。  
于是在启动脚本里修改启动参数1 >/dev/console  2>/dev/console，重启，打印出现。  
继续修改启动参数为1 >/dev/tty0  2>/dev/tty0，重启，也同样出现打印内容。搞定。  
```c
#define stdin   0
#define stdout  1
#define stderr  2
//1 > /dev/tty1   2 > /dev/tty1  
```
##### 3.1 Telnet
```bash
/ # ps | grep vtysh
 1048 root       0:00 vtysh -f
 1049 root       0:00 vtysh -b
 1192 root       0:00 vtysh -t /dev/pts/0 -a 192.168.1.10
 1197 root       0:00 vtysh -t /dev/pts/1 -a 192.168.1.10
 1210 root       0:00 grep vtysh
/ # echo 111 > /dev/pts/0
111
/ # echo 111 > /dev/pts/1
/ #
```
