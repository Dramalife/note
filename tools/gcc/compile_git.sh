#! /bin/bash

make configure
./configure
make all
# sudo apt-get purge git #remove old version
sudo make install

