#! /bin/bash

LIB_DRAMALIFE_SHELL_RELATIVE_PWD=../../lib_dramalife/
source ${LIB_DRAMALIFE_SHELL_RELATIVE_PWD}/lib_dramalife.sh

echo "===================START====================="
echo -e "="	${CLGREEN}"root@bpi-iot-ros-ai"${CNONE}":"${L_BLUE}"~/note/90-operating_system/lsusb #"${CNONE}" lsusb"
echo -e "="	"Bus 004 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub"
echo -e "="	"Bus 003 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub"
echo -e "="	"Bus 002 Device 002: ID 2109:0715 VIA Labs, Inc. "
echo -e "="	"Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub"
echo -e "="	"Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub"
echo -e "="	${CLGREEN}"root@bpi-iot-ros-ai"${CNONE}":"${L_BLUE}"~/note/90-operating_system/lsusb #"${CNONE}" lsusb -t"
echo -e "="	"/:  Bus 04.Port 1: Dev 1, Class=root_hub, Driver=xhci-mtk/1p, 5000M"
echo -e "="	"/:  Bus 03.Port 1: Dev 1, Class=root_hub, Driver=xhci-mtk/1p, 480M"
echo -e "="	"/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=xhci-mtk/1p, 5000M"
echo -e "="	"    |__ Port 1: Dev 2, If 0, Class=Mass Storage, Driver=usb-storage, 5000M"
echo -e "="	"/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=xhci-mtk/1p, 480M"
echo "===================END====================="
