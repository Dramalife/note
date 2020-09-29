### 1. Configuring crosstool-NG

#### 1.0 Default(samples)

```bash
# prints the list of all samples (for scripting)
./ct-ng list-samples

# Load sample && Configure
./ct-ng arm-cortex_a8-linux-gnueabi
./ct-ng menuconfig

# show a brief overview of <sample> (list with list-samples)
./ct-ng show-mips-unknown-linux-uclibc
[L..]   mips-unknown-linux-uclibc
	OS             : linux-4.10.8
	Companion libs : gmp-6.1.2 mpfr-3.1.5 isl-0.16.1 mpc-1.0.3 expat-2.2.0 ncurses-6.0
	binutils       : binutils-2.28
	C compilers    : gcc  |  6.3.0
	Languages      : C,C++
	C library      : uClibc-ng-1.0.22 (threads: nptl)
	Tools          : duma-2_5_15 gdb-7.12.1

```

#### 1.1 menuconfig

```bash
$ ct-ng menconfig
Paths and misc options  --->
	# Path of downloaded source code
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
		[*] custom tarball or directory
		(/home/dramalife/linux-4.19.38) Path to custom source, tarball or directory
		(linux-4.19.38-sunxi) Custom Linux version
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
