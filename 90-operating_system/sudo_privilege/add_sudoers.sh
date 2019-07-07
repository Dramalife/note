#! /bin/bash
sudo useradd -m $1
sudo cp /etc/sudoers /etc/sudoers_backup8888
sudo echo $1"	ALL=(ALL:ALL) ALL" >> /etc/sudoers
echo "input passwd!"
sudo passwd $1
