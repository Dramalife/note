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


sudo kill -9 $(pidof dhclient)
sudo ifconfig ${1} down
sudo ifconfig ${1} up
echo "if restart done, press"
read
#tcpdump -i ${1} -w /home/baohua/sharehahaha/dhcp.pcapng &
sudo echo "" > /var/lib/dhcp/dhclient.leases
sudo dhclient ${1}
cat /var/lib/dhcp/dhclient.leases

