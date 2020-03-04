version : coreutils-8.28  


#### 1. Configure && Make && Install

```bash
./configure --prefix=/home/dramalife/temp/coreutils-8.28/prefix --host=aarch64-linux-gnu

make CC=aarch64-linux-gnu-gcc

make install
```

#### 2. Error(s)

##### 3. error-install

```bash
make[2]: Entering directory '/home/dramalife/temp/coreutils-8.28'
  GEN      man/chroot.1
  help2man: can't get `--help' info from man/chroot.td/chroot
  Try `--no-discard-stderr' if option outputs to stderr
  Makefile:14870: recipe for target 'man/chroot.1' failed
  make[2]: *** [man/chroot.1] Error 2

# binary has already been created.
```

