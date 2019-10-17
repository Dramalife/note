### 1. Configuring crosstool-NG

#### 1.1 menuconfig

```bash
$ ct-ng menconfig
Paths and misc options  --->
	# GCC source path, change "" in "./.config" 
	(${HOME}/src) Local tarballs directory (NEW)
	# Prefix path
	(${CT_PREFIX:-${HOME}/x-tools}/${CT_HOST:+HOST-${CT_HOST}/}${CT_TARGET}) Prefix directory (NEW)
Target options  --->
	Target Architecture (mips)  --->
	# Hide if mips
	()  Emit assembly for CPU
Toolchain options  --->
	(dramalife) Tuple's vendor string
Operating System  --->
	Target OS (linux)  --->
	[ ] custom tarball or directory
		Linux kernel version (4.10.8)  --->
C compiler  --->
	gcc version (6.3.0)  --->
Companion libraries  --->
	libiconv version (1.15)  --->
	gettext version (0.19.8.1)  --->
	GMP version (6.1.2)  --->
	MPFR version (3.1.5)  --->
	# Compatible with gcc-6.3.0
	ISL version (0.15)  --->
	# Different !!
	MPC version (1.0.3)  --->
	ncurses version (6.0)  --->
	```

#### 1.2 Change default name

```bash
cat ./.config | grep CT_TARGET_VENDOR
```
