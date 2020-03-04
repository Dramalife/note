```
mpfr-3.1.5 used by crosstool-ng
```

#### 1. Download source code

```bash
cat ../00-source_code_of_tools/wget-mpfr-3.1.5.sh
```

#### 2. Configurate

```bash
./configure
```

#### 3. Make && Install

```bash
make -j4
make check
sudo make install
```
