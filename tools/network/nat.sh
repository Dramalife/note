#! /bin/bash
#
# REF : https://www.cnblogs.com/along1226/p/4853895.html
# REF : https://blog.csdn.net/cooling88/article/details/51040054
#

echo 1 > /proc/sys/net/ipv4/ip_forward
/sbin/modprobe ip_tables
/sbin/modprobe ip_nat_ftp
/sbin/modprobe iptable_nat


# [RECV] Change des_ip from 192.168.0.122 to 192.168.67.LIST
iptables -t nat -A PREROUTING -d 192.168.0.122 -j DNAT --to-destination 192.168.67.109
iptables -t nat -A PREROUTING -d 192.168.0.122 -j DNAT --to-destination 192.168.67.104
# [SEND] Change src_ip from 192.168.67.0/24 to 192.168.0.122
iptables -t nat -A POSTROUTING -s 192.168.67.0/24 -j SNAT --to-source 192.168.0.122
