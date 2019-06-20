#! /bin/bash
#
# note network-dhcp related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
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

