REF : https://blog.csdn.net/fst438060684/article/details/80880280
REF : https://blog.csdn.net/jiuweideqixu/article/details/104408432

wget https://mirrors.tuna.tsinghua.edu.cn/gnu/glibc/glibc-2.23.tar.gz
tar zxvf glibc-2.23.tar.gz


configure: error: you must configure in a separate build directory
cd ../

$ CC=arm-linux-gnueabihf-gcc LD=arm-linux-gnueabihf-ld RANLIB=arm-linux-gnueabihf-ranlib ./glibc-2.23/configure --host=armv7a-linux --prefix=/home/dramalife/temp/glibc_cross/install_glibc

make 
make install




```
setenv.c: In function ‘__unsetenv’:
setenv.c:279:6: error: suggest explicit braces to avoid ambiguous ‘else’ [-Werror=dangling-else]
   if (ep != NULL)
       ^
cc1: all warnings being treated as errors
../o-iterator.mk:9: recipe for target '/home/dramalife/temp/glibc_cross/stdlib/setenv.o' failed
```
glibc-2.23/nis/nis_call.c
glibc-2.23/stdlib/setenv.c
```diff
+ {}
```



../sysdeps/ieee754/dbl-64/e_pow.c:469:13: error: ‘<<’ in boolean context, did you mean ‘<’ ? [-Werror=int-in-bool-context]
```diff
+ 0!=()
```


getconf.c: In function ‘main’:
getconf.c:577:6: error: statement will never be executed [-Werror=switch-unreachable]
      {
      ^
cc1: all warnings being treated as errors
```
```

