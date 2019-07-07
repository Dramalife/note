### Host

#### 查找延时最小dns
1. 打开[Dns检测|Dns查询](https://link.zhihu.com/?target=http%3A//tool.chinaz.com/dns)
2. 在检测输入栏中输入http://github.com官网
3. 把检测列表里的TTL值最小的IP输入到hosts里，并对应写上github官网域名

#### 添加host
```
Windows 系统位于 C:\Windows\System32\drivers\etc\
Android（安卓）系统hosts位于 /etc/
Mac（苹果电脑）系统hosts位于 /etc/
iPhone（iOS）系统hosts位于 /etc/
Linux系统hosts位于 /etc/
绝大多数Unix系统都是在 /etc/
```
#### 使Host生效 [链接](https://www.zhihu.com/question/20732532/answer/253922215)
```
Windows
开始 -> 运行 -> 输入cmd -> 在CMD窗口输入  ： ipconfig /flushdns

Linux
终端输入 ：  sudo rcnscd restart

Mac OS X终端输入 ：  sudo killall -HUP mDNSResponder

其他：断网，再开网；
终极方法： 重启机器；
```
