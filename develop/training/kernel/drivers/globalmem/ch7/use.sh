#! /bin/bash
# Dramalife@live.com
#/home/baohua/develop/training/kernel/drivers/globalmem/ch7
make clean
make
echo "*************"
sudo insmod globalmem.ko
echo "*************"
sudo lsmod
#sudo rmmod globalmem.ko
