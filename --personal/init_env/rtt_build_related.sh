#! /bin/bash

sudo apt isntall -y scons

# ctype.h: No such file or directory
sudo apt install -y libc6-dev

sudo apt install -y libncurses5-dev

sudo apt install -y gcc-arm-none-eabi

sudo apt install -y qemu


# Edit rtconfig.h
#rt-thread/bsp/qemu-vexpress-a9/rtconfig.h
#define HAVE_SYS_SELECT_H

