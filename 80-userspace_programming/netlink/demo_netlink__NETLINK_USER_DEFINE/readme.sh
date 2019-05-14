#! /bin/bash
source ~/note/lib_dramalife/terminal_color_bash.sh
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

