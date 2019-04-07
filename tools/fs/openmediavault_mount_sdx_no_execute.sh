#! /bin/bash
#to solve problem tha file can`t execute on mobile hard disk.
#Dramalife@live.com

#$1:disk file in path "/dev/sd*";
#$2:target path;
sudo umount $2 
sudo mount $1 $2 -o rwx

