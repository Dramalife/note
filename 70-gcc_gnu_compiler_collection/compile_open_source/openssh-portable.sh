#! /bin/bash

apt install autoconf automake -y
⁣
# zlib.h
sudo apt install zlib1g-dev -y

⁣# libcrypto
apt install libssl-dev  -y

git clone https://github.com/openssh/openssh-portable.git --depth=1
