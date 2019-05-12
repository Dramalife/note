#! /bin/bash
#644
sudo cp -f /etc/hostname /etc/hostname_backup
sudo chmod 666 /etc/hostname
echo $1 > /etc/hostname
sudo chmod 644 /etc/hostname
