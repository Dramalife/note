#### 1. Build

```bash
./ct-ng build
# Then download sources automatically, but most tasks failed :-( whitch causing errors listed in "2.Error(s)"
# "2.1-build.log" shows the searching paths, you can download sources manually and copy to that ;
```

#### 2. Error(s)

##### 2.1 Retrieving 'gcc-6.3.0'

build.log
```log
build.log:937:[DEBUG]    Trying to retrieve an already downloaded copy of 'gcc-6.3.0'
build.log:938:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0.tar.xz'
build.log:939:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0.tar.lzma'
build.log:940:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0.tar.bz2'
build.log:941:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0.tar.gz'
build.log:942:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0.tgz'
build.log:943:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0.tar'
build.log:944:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0.zip'
build.log:945:[DEBUG]    Trying '/home/dramalife/src/gcc-6.3.0'
build.log:946:[EXTRA]    Retrieving 'gcc-6.3.0'
build.log:947:[DEBUG]    Trying 'http://ftp.gnu.org/gnu/gcc/gcc-6.3.0/gcc-6.3.0.tar.xz'
build.log:948:[DEBUG]    ==> Executing: 'wget' '--passive-ftp' '--tries=3' '-nc' '--progress=dot:binary' '-T' '10' '-O' '/home/dramalife/note/70-gcc_gnu_compiler_collection/crosstool-ng/crosstool-ng-1.23.0/.build/tarballs/gcc-6.3.0.tar.xz.tmp-dl' 'http://ftp.gnu.org/gnu/gcc/gcc-6.3.0/gcc-6.3.0.tar.xz' 
build.log:950:[ALL  ]    --2019-10-21 06:17:28--  https://ftp.gnu.org/gnu/gcc/gcc-6.3.0/gcc-6.3.0.tar.xz
build.log:956:[DEBUG]    Not at this location: "http://ftp.gnu.org/gnu/gcc/gcc-6.3.0/gcc-6.3.0.tar.xz"
```

solve
```bash
cp gcc-6.3.0.tar.bz2 /home/dramalife/src/gcc-6.3.0.tar.bz2
```


##### 2.2 Retrieving 'uClibc-ng-1.0.22'

```log
#// wait ...

$ tail build.log
[ALL  ]    Saving to: '/home/dramalife/note/70-gcc_gnu_compiler_collection/crosstool-ng/crosstool-ng-1.23.0/.build/tarballs/uClibc-ng-1.0.22.tar.xz.tmp-dl'
[ALL  ]    
[ALL  ]         0K ,,,,,,,,,,,,,,,, ,,..........                      11% 9.31K=8.6s
```
