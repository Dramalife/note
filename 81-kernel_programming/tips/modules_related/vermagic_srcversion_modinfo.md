root@Lenovo:~/linux-source-5.0.0# cat include/config/kernel.release
5.0.21

root@Lenovo:~/linux-source-5.0.0# cat Makefile | grep kernel.release
# Read KERNELRELEASE from include/config/kernel.release (if it exists)
KERNELRELEASE = $(shell cat include/config/kernel.release 2> /dev/null)
filechk_kernel.release = \
# Store (new) KERNELRELEASE string in include/config/kernel.release
include/config/kernel.release: $(srctree)/Makefile FORCE
	$(call filechk,kernel.release)
prepare3: include/config/kernel.release
include/generated/utsrelease.h: include/config/kernel.release FORCE
%pkg: include/config/kernel.release FORCE


