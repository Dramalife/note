#### 1 
make defconfig

#### 2.1 cross_compile

```bash
vi Makefile +164 
```

```diff
+ CROSS_COMPILE ?= arm-linux-gnueabihf-
```

```bash
make -j4
```

#### 2.2 local_compile

```bash
make
```

