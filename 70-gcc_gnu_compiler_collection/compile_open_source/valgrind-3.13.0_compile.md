REF : https://blog.csdn.net/weixin_34375054/article/details/86130304


Compile

ARMv7 - cross compile
$ CC=arm-linux-gnueabihf-gcc LD=arm-linux-gnueabihf-ld RANLIB=arm-linux-gnueabihf-ranlib ./configure --host=armv7a-linux
$ CC=arm-linux-gnueabihf-gcc LD=arm-linux-gnueabihf-ld RANLIB=arm-linux-gnueabihf-ranlib ./configure --host=armv7a-linux --prefix=/home/dramalife/valgrind/install_armv7


ARMv8 - cross compile
$ ./configure --build=aarch64-linux

make
make install

Runtime:
export VALGRIND_LIB=/lib/valgrind
