### BCM2836 use lib_bcm2835 (bcm2835-1.16/src/bcm2835.h)

```diff
#define BCM2835_PERI_BASE               0x20000000
#define BCM2835_PERI_BASE               0x3F000000  
```

### Compile &

```bash
wget http://www.open.com.au/mikem/bcm2835/bcm2835-1.16.tar.gz
./configure
make
make install
gcc demo.c -l rt -l bcm2835
```

### REFs

REF URL1 : https://blog.csdn.net/u013738338/article/details/78723743
REF URL2 : http://blog.sina.com.cn/s/blog_55b759e60101ngvl.html

