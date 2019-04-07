#! /bin/bash
#mkdir ./share_pc
mkdir ./$2
#chmod 777 ./share_pc
chmod 777 ./$2
#vm_share($1):shared folder created on PC;
#share_pc($2):local folder name of virtual pc;
#sudo mount -t vboxsf vm_share ./share_pc/
sudo mount -t vboxsf $1 ./$2/
