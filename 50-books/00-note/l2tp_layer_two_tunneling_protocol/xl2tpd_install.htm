
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<!-- 设置标题 -->
<title>
  </title>
<!-- 关键词写在模板中 header.php -->
<div class="centent-article fonts">
		<div class="post-content"><table>
<tbody>
<tr>
<td style="padding: 5px 12px; width: 25px; font-size: 22px; text-align: center; background: #E8E8E8; line-height: 30px; color: #999;">导读</td>
<td style="padding: 10px 10px 12px; line-height: 20px;"><strong>L2TP是一种工业标准的Internet隧道协议，功能大致和PPTP协议类似，比如同样可以对网络数据流进行加密。不过也有不同之处，比如PPTP要求网络为IP网络，L2TP要求面向数据包的点对点连接；PPTP使用单一隧道，L2TP使用多隧道；L2TP提供包头压缩、隧道验证，而PPTP不支持。本文来介绍如何搭建L2TP。</strong></td>
</tr>
</tbody>
</table>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>1.先看看你的主机是否支持pptp，返回结果为yes就表示通过</strong></span></div>
<pre>modprobe ppp-compress-18 && echo yes</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>2.是否开启了TUN</strong></span></div>
<p>有的虚拟机主机需要开启，返回结果为<span style="padding: 4px 8px; font-size: 12px; border-radius: 3px; color: #c7254e; background-color: #f9f2f4;">cat: /dev/net/tun: File descriptor in bad state</span>。就表示通过。</p>
<pre>cat /dev/net/tun</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>3.更新一下再安装</strong></span></div>
<pre>yum install update 
yum update -y</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>4.安装EPEL源</strong></span></div>
<pre>yum install -y epel-release</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>5.安装xl2tpd和libreswan</strong></span></div>
<pre>yum install -y xl2tpd libreswan lsof</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>6.编辑xl2tpd配置文件</strong></span></div>
<pre>vim /etc/xl2tpd/xl2tpd.conf</pre>
<p>修改内容如下：</p>
<pre>[global]
[lns default]
ip range = 172.100.1.100-172.100.1.150   #分配给客户端的地址池
local ip = 172.100.1.1
require chap = yes
refuse pap = yes
require authentication = yes
name = <a href="https://www.linuxprobe.com/" title="linux"target="_blank">Linux</a>VPNserver
ppp debug = yes
pppoptfile = /etc/ppp/options.xl2tpd
length bit = yes</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>7.编辑pppoptfile文件</strong></span></div>
<pre>vim /etc/ppp/options.xl2tpd</pre>
<p>修改内容如下：</p>
<pre>ipcp-accept-local
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
logfile /var/log/xl2tpd.log</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>8.编辑ipsec配置文件</strong></span></div>
<pre>vim /etc/ipsec.conf</pre>
<pre>config setup
        protostack=netkey
        dumpdir=/var/run/pluto/
        virtual_private=%v4:10.0.0.0/8,%v4:172.100.0.0/12,%v4:25.0.0.0/8,%v4:100.64.0.0/10,%v6:fd00::/8,%v6:fe80::/10
        include /etc/ipsec.d/*.conf</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>9.编辑include的conn文件</strong></span></div>
<pre>vim /etc/ipsec.d/l2tp-ipsec.conf</pre>
<p>修改内容如下：</p>
<pre>conn L2TP-PSK-NAT
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
                        #<a href="https://www.linuxprobe.com/" title="centos"target="_blank">CentOS</a>7以下的用iptables定义转发规则
    leftprotoport=17/1701
    right=%any
    rightprotoport=17/%any</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>10.设置用户名密码</strong></span></div>
<pre>vim /etc/ppp/chap-secrets</pre>
<p>修改内容： </p>
<pre>vpnuser * pass * 
说明：用户名[空格]service[空格]密码[空格]指定IP</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>11.设置PSK</strong></span></div>
<pre>vim /etc/ipsec.d/default.secrets</pre>
<pre>: PSK "testvpn"</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>12.CentOS7防火墙设置</strong></span></div>
<pre>firewall-cmd --permanent --add-service=ipsec
firewall-cmd --permanent --add-port=1701/udp
firewall-cmd --permanent --add-port=4500/udp
firewall-cmd --permanent --add-masquerade
firewall-cmd --reload</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>13.IP_FORWARD 设置</strong></span></div>
<pre>vim /etc/sysctl.d/60-sysctl_ipsec.conf</pre>
<pre>net.ipv4.ip_forward = 1
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
net.ipv4.conf.ppp0.send_redirects = 0</pre>
<p>重启生效</p>
<pre>systemctl restart network</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>13.ipsec启动&检查</strong></span></div>
<pre>systemctl enable ipsec
systemctl restart ipsec</pre>
<p>检查：<span style="padding: 4px 8px; font-size: 12px; border-radius: 3px; color: #c7254e; background-color: #f9f2f4;">ipsec verify</span></p>
<p>正常输出：</p>
<pre>Verifying installed system and configuration files

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
Opportunistic Encryption                                [DISABLED]</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>14.xl2tpd启动</strong></span></div>
<pre>systemctl enable xl2tpd
systemctl restart xl2tpd</pre>
<div style="margin-top:2em;margin-bottom:1em"><span style="color:#1E1E1E;letter-spacing: 2px;border-left:#FF3030 3px solid;border-right:#FF3030 3px solid;padding-left: 8px;padding-right:8px;font-size: 12pt"><strong>15.Windows连接</strong></span></div>
<p>Windows连接，需要修改注册表键值（据说可以不用修改，但是我的不修改的话，一直789，log无显示）</p>


<p><!-- --><!-- Page reform for Baidu by 爱上极客熊掌号 (i3geek.com) --></p>
</div>
		<!-- 分页 -->


		<!-- 文章版权信息 -->
		<div class="copyright alert alert-success">
			<p>
转载必需保留本文链接:
				<a href="https://www.linuxprobe.com/centos7-install-l2tp.html" title="CentOS7 搭建L2TP">https://www.linuxprobe.com/centos7-install-l2tp.html</a><br></p>
		</div>
		<!-- 文章版权信息结束 -->

	</div>				
</article>
<!-- 内容主体结束 -->

 
			</div>


		</div>		
	</div>
</div>
</div>


</body>
</html>
</body>
</html>