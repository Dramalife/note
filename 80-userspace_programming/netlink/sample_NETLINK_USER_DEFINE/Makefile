# Dramalife update, 2019.05.13 
# source url: https://www.cnblogs.com/wenqiang/p/6306727.html
# insmod,lsmod,rmmod,,dmesg,

#
#Desgin of Netlink
#

#MODULE_NAME :=netlink_test
MODULE_NAME :=module_kernel
APP_NAME :=user
obj-m :=$(MODULE_NAME).o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
	rm -rvf $(APP_NAME).out
	gcc -o $(APP_NAME).out $(APP_NAME).c -v

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rvf $(APP_NAME).out
