#! /bin/bash

#source ~/note/lib_dramalife/terminal_color_bash.sh
export LIB_DRAMALIFE_PWD=~/note/lib_dramalife/
export LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5001
source ${LIB_DRAMALIFE_PWD}/lib_dramalife.sh

# kernel source
# --------
# struct user_msghdr
# struct msghdr

# userspace lib
# --------
# struct msghdr



# demo running
# --------
make
sudo rmmod module_kernel.ko
sudo insmod module_kernel.ko
dmesg
# right :
#echo -e $YELLOW"kernel print end."$CNONE
# right :
echo -e "${YELLOW}kernel print end.${CNONE}"
# error :
#echo -e $(YELLOW)"kernel print end."$(CNONE)

echo -e $L_CYAN"userspace print:"$CNONE
./user.out


# [note] vim cmd
# :%s/^#\s*$//g

