#! /bin/bash
#
# 2021/01/30, dramalife@live.com
#

PUB_DIR=pub_openwrt
PERSONAL_DIR=${USER}_openwrt

# Warning
echo -e "\n\nUSER:${USER}"
echo -e "Public dir:\t${PUB_DIR}"
echo -e "Personal dir:\t${PERSONAL_DIR}"
echo "Press anykey to continue..."
read xxxxxx


# Create Folder
if [ `test -e ${PUB_DIR}` ]
then
	mkdir ${PUB_DIR}
fi
if [ `test -e ${PERSONAL_DIR}` ]
then
	mkdir ${PERSONAL_DIR}
fi

# Mount
sudo mount -t nfs 172.16.1.1:/mnt/sda1/pub ./pub_openwrt;sudo chown ${USER} ./${PUB_DIR}
echo -e "mount to ./${PUB_DIR}		\nret:$?"
sudo mount -t nfs 172.16.1.1:/root/sda1/devs/nanopi_m4_184/users/${USER} ./${PERSONAL_DIR}; sudo chown ${USER} ./${PERSONAL_DIR}
echo -e "mount to ./${PERSONAL_DIR}	\nret:$?"



