#root@NETAC-SERVER:~/ # vi /etc/resolvconf/resolv.conf.d/base 
#root@NETAC-SERVER:~/ # vi /etc/resolvconf/resolv.conf.d/head

echo "clean.."
mv /etc/resolvconf/resolv.conf.d/base /etc/resolvconf/resolv.conf.d/base_bk$(date "+%Y%m%d")
mv /etc/resolvconf/resolv.conf.d/head /etc/resolvconf/resolv.conf.d/head_bk$(date "+%Y%m%d")

echo "dns.."
echo "nameserver 192.168.0.1" > /etc/resolvconf/resolv.conf.d/head
echo "nameserver 114.114.114.114" > /etc/resolvconf/resolv.conf.d/base


echo "route.."
route add default gw 192.168.0.1

