#! /bin/bash
# Dramalife@live.com
# 2019.06.05


kill -9 $(pidof dhclient)
ifconfig eth1 down
ifconfig eth1 up
echo "if restart done, press"
read
#tcpdump -i eth1 -w /home/baohua/sharehahaha/dhcp.pcapng &
echo "" > /var/lib/dhcp/dhclient.leases
dhclient eth1
cat /var/lib/dhcp/dhclient.leases

