### Configuration Files
|No|File|Use|
|--|--|--|
|0|/etc/samba/smb.conf|#samba服务的主要配置文件|
|1|/etc/samba/lmhosts|#samba服务的域名设定，主要设置IP地址对应的域名，类似linux系统的/etc/hosts|
|2|/etc/samba/smbusers|#samba服务设置samba虚拟用户的配置文件|
|3|/var/log/samba|#samab服务存放日志文件|
|4|/var/lib/samba/private/{passdb.tdb,secrets.tdb}|#存放samba的用户账号和密码数据库文档|

### install

- 标注\(参考\)：Samab服务开启之前需要关闭两个服务，iptables防火墙（如果你熟悉可以不关闭，放行smb的端口即可，SAMBA服务TCP端口139,445  UDP端口 137,138）；selinux服务。

#### firewall
|||
|--|--|
|/etc/init.d/iptables stop|#关闭防火墙|
|chkconfig --list iptables|#查看防火墙启动状态|
|chkconfig iptables off#关闭防火墙开机自动启动|

#### selinux
```
vim /etc/selinux/config                      #永久关闭selinux

set SELINUX=disabled       #SELINUX=enforcing改为SELINUX=disabled
```
### 使用实例
#### Add User
|No|CMD|FUN|
|--|--|--|
|0|useradd user01|添加Linux用户|
|1|passwd user01|修改Linux用户密码|
|2|smbpasswd -a user01|把系统用户user01**添加为samba用户**并设置用户登录密码|
|3|pdbedit –L|查看samba用户|

#### vi smb.conf
```
[global]
workgroup = WORKGROUP                 #设置主机工作组
server string = Samba Server Version %v      #samba服务注释
log level = 1                         #设置日志文件安全级别为1
log file = /var/log/samba/%m          #设置日志文件名称，%m以IP地址为名称
max log size = 50                     #设置日志文件最大容量50KB，0表示不限制
security = user                       #以user验证方式访问
passdb backend = tdbsam               #定义用户后台类型
load printers = no                    #关闭打印共享功能
cups options = raw                    #打印机选项

[usershare]
comment  =  Home Directories          #共享文件描述
path  =  /home/smbuser01              #共享路径
browseable  =  yes                    #共享文件可以浏览
read only  =  yes                     #共享文件可读，不能与writable共用
valid users  =  test01,test02         #设置允许访问共享用户

[adminshare]
comment  =  Home Directories          #共享文件描述
path  =  /home/smbadmin01             #共享路径
browseable  =  yes                    #共享文件可以浏览
writable  =  yes                      #共享文件可写
create  make  =  0664                 #设置用户创建文件权限0664
directory  make  =  0775              #设置用户创建目录权限0775
write  list   =   test01              #设置允许访问共享具有写入权限的用户
```

#### Restart Service
\# /etc/init.d/smb  restart       　　　　　　　　　　　　　
