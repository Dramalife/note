# Windows cmd.exe mount samba

[Ref url : windows使用cmd（dos命令）映射网络驱动器](https://blog.csdn.net/fangye945a/article/details/87743291)



### 1 View

```bash
net view \\172.16.127.202
发生系统错误 5。

拒绝访问。


```

### 2 Map / Mount

```bahs
net use Z: \\172.16.127.202\dramalife
为“172.16.127.202”输入用户名: dramalife
输入 172.16.127.202 的密码:
命令成功完成。


```

### 3 Unmount

```bash
net use Z: /del
Z: 已经删除。


```

### 4 Unmount All

```bash
net use * /d /y
```

