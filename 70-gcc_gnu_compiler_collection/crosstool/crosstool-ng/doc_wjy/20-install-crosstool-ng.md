### 1. Prepare

```bash
$ uname -a
Linux server 4.15.0-65-generic #74-Ubuntu SMP Tue Sep 17 17:06:04 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux

$ sudo apt install awk gperf bison help2man

# configure: error: missing required tool: makeinfo
$ sudo apt install texinfo

# curses.h
$ sudo apt install libncurses5-dev

# Install gmp-6.1.2
# See "NOTE/tools/gcc/gmp-6.1.2_compile.md"

# Install mpc-1.0.3

# Install ncurses6

# Install libiconv-1.15

# Install gettext-0.19.8.1

#
#gcc-9.2.0 $ ./contrib/download_prerequisites
```



### 2. Configure && Make

```bash
./configure --prefix=/home/dramalife/note/70-gcc_gnu_compiler_collection/crosstool-ng/prefix_build

make -j4

make install

export PATH="${PATH}:/home/dramalife/note/70-gcc_gnu_compiler_collection/crosstool-ng/prefix_build/bin"

```

