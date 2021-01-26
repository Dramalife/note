#### stdint.h: No such file or directory

Erros
```bash
/usr/lib/gcc/aarch64-linux-gnu/7/include/stdint.h:9:16: fatal error: stdint.h: No such file or directory
 # include_next <stdint.h>
                 ^~~~~~~~~~
compilation terminated.
```

Fix [Ref](https://blog.csdn.net/zhangjun1992/article/details/26029959)
```bash
sudo apt install libc6-dev
```


