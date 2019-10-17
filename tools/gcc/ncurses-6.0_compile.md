```
ncurses-6.0 used by crosstool-NG (gcc-6.3.0)
```

### 1. Download Source

```bash
wget https://mirrors.tuna.tsinghua.edu.cn/gnu/ncurses/ncurses-6.0.tar.gz
```

### 2. Configure && Make && Install

```bash
export CPPFLAGS="-P"
./configure
make -j4
sudo make install
```
