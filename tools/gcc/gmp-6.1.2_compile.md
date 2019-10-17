```
gmp-6.1.2 used by crosstool-ng
```

#### 1. Download source code

```bash
cat ../00-source_code_of_tools/wget-gmp-6.1.2.sh
```

#### 2. Configurate

```bash
gmp-6.1.2 $ ./configure --prefix=/usr --enable-cxx --disable-static --docdir=/usr/share/doc/gmp-6.1.2
```

#### 3. Make && Install

```bash
make -j4
make check
sudo make install
```
