| 导读 | **L2TP是一种工业标准的Internet隧道协议，功能大致和PPTP协议类似，比如同样可以对网络数据流进行加密。不过也有不同之处，比如PPTP要求网络为IP网络，L2TP要求面向数据包的点对点连接；PPTP使用单一隧道，L2TP使用多隧道；L2TP提供包头压缩、隧道验证，而PPTP不支持。本文来介绍如何搭建L2TP。** |
| ---- | ------------------------------------------------------------ |
|      |                                                              |

**1.先看看你的主机是否支持pptp，返回结果为yes就表示通过**

```
modprobe ppp-compress-18 && echo yes
```

**2.是否开启了TUN**

有的虚拟机主机需要开启，返回结果为cat: /dev/net/tun: File descriptor in bad state。就表示通过。

```
cat /dev/net/tun
```

**3.更新一下再安装**

```
yum install update 
yum update -y
```

**4.安装EPEL源**

```
yum install -y epel-release
```

**5.安装xl2tpd和libreswan**

```
yum install -y xl2tpd libreswan lsof
```

**6.编辑xl2tpd配置文件**

```
vim /etc/xl2tpd/xl2tpd.conf
```

修改内容如下：

```
[global]
[lns default]
ip range = 172.100.1.100-172.100.1.150   #分配给客户端的地址池
local ip = 172.100.1.1
require chap = yes
refuse pap = yes
require authentication = yes
name = LinuxVPNserver
ppp debug = yes
pppoptfile = /etc/ppp/options.xl2tpd
length bit = yes
```

**7.编辑pppoptfile文件**

```
vim /etc/ppp/options.xl2tpd
```

修改内容如下：

```
ipcp-accept-local
ipcp-accept-remote
ms-dns  8.8.8.8
ms-dns 209.244.0.3
ms-dns 208.67.222.222
name xl2tpd
#noccp
auth
crtscts
idle 1800
mtu 1410         #第一次配置不建议设置mtu，mru，否则可能789错误
mru 1410
nodefaultroute
debug
lock
proxyarp
connect-delay 5000
refuse-pap
refuse-chap
refuse-mschap
require-mschap-v2
persist
logfile /var/log/xl2tpd.log
```

**8.编辑ipsec配置文件**

vim /etc/ipsec.conf
```
config setup
		protostack=netkey
		dumpdir=/var/run/pluto/
		virtual_private=%v4:10.0.0.0/8,%v4:172.100.0.0/12,%v4:25.0.0.0/8,%v4:100.64.0.0/10,%v6:fd00::/8,%v6:fe80::/10
		include /etc/ipsec.d/*.conf
```

**9.编辑include的conn文件**

```
vim /etc/ipsec.d/l2tp-ipsec.conf
```

修改内容如下：

```
conn L2TP-PSK-NAT
    rightsubnet=0.0.0.0/0
    dpddelay=10
    dpdtimeout=20
    dpdaction=clear
    forceencaps=yes
    also=L2TP-PSK-noNAT
conn L2TP-PSK-noNAT
    authby=secret
    pfs=no
    auto=add
    keyingtries=3
    rekey=no
    ikelifetime=8h
    keylife=1h
    type=transport
    left=192.168.0.17   #service/VPS的外网地址，某些vps只有eth0一块网卡的，
                        #就填内网地址，内核开启nat转发就可以了，
                        #CentOS7以下的用iptables定义转发规则
    leftprotoport=17/1701
    right=%any
    rightprotoport=17/%any
```

**10.设置用户名密码**

```
vim /etc/ppp/chap-secrets
```

修改内容：

```
vpnuser * pass * 
说明：用户名[空格]service[空格]密码[空格]指定IP
```

**11.设置PSK**

```
vim /etc/ipsec.d/default.secrets
: PSK "testvpn"
```

**12.CentOS7防火墙设置**

```
firewall-cmd --permanent --add-service=ipsec
firewall-cmd --permanent --add-port=1701/udp
firewall-cmd --permanent --add-port=4500/udp
firewall-cmd --permanent --add-masquerade
firewall-cmd --reload
```

**13.IP_FORWARD 设置**

```
vim /etc/sysctl.d/60-sysctl_ipsec.conf
net.ipv4.ip_forward = 1
net.ipv4.conf.all.accept_redirects = 0
net.ipv4.conf.all.rp_filter = 0
net.ipv4.conf.all.send_redirects = 0
net.ipv4.conf.default.accept_redirects = 0
net.ipv4.conf.default.rp_filter = 0
net.ipv4.conf.default.send_redirects = 0
net.ipv4.conf.eth0.accept_redirects = 0
net.ipv4.conf.eth0.rp_filter = 0
net.ipv4.conf.eth0.send_redirects = 0
net.ipv4.conf.eth1.accept_redirects = 0
net.ipv4.conf.eth1.rp_filter = 0
net.ipv4.conf.eth1.send_redirects = 0
net.ipv4.conf.eth2.accept_redirects = 0
net.ipv4.conf.eth2.rp_filter = 0
net.ipv4.conf.eth2.send_redirects = 0
net.ipv4.conf.ip_vti0.accept_redirects = 0
net.ipv4.conf.ip_vti0.rp_filter = 0
net.ipv4.conf.ip_vti0.send_redirects = 0
net.ipv4.conf.lo.accept_redirects = 0
net.ipv4.conf.lo.rp_filter = 0
net.ipv4.conf.lo.send_redirects = 0
net.ipv4.conf.ppp0.accept_redirects = 0
net.ipv4.conf.ppp0.rp_filter = 0
net.ipv4.conf.ppp0.send_redirects = 0
```

重启生效

```
systemctl restart network
```

**13.ipsec启动&检查**

```
systemctl enable ipsec
systemctl restart ipsec
```

检查：ipsec verify

正常输出：

```
Verifying installed system and configuration files

Version check and ipsec on-path                         [OK]
Libreswan 3.15 (netkey) on 3.10.0-123.13.2.el7.x86_64
Checking for IPsec support in kernel                    [OK]
 NETKEY: Testing XFRM related proc values
         ICMP default/send_redirects                    [OK]
         ICMP default/accept_redirects                  [OK]
         XFRM larval drop                               [OK]
Pluto ipsec.conf syntax                                 [OK]
Hardware random device                                  [N/A]
Two or more interfaces found, checking IP forwarding    [OK]
Checking rp_filter                                      [OK]
Checking that pluto is running                          [OK]
 Pluto listening for IKE on udp 500                     [OK]
 Pluto listening for IKE/NAT-T on udp 4500              [OK]
 Pluto ipsec.secret syntax                              [OK]
Checking 'ip' command                                   [OK]
Checking 'iptables' command                             [OK]
Checking 'prelink' command does not interfere with FIPSChecking for obsolete ipsec.conf options             [OK]
Opportunistic Encryption                                [DISABLED]
```

**14.xl2tpd启动**

```
systemctl enable xl2tpd
systemctl restart xl2tpd
```

**15.Windows连接**

Windows连接，需要修改注册表键值（据说可以不用修改，但是我的不修改的话，一直789，log无显示）



转载必需保留本文链接: https://www.linuxprobe.com/centos7-install-l2tp.html