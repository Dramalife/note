
### 1. Configure && Make

```bash
# 64 Bit only
./configure --disable-multilib
make -j4

```


### 2. ERRORs

#### 2.1 recipe for target 'xxx' failed :

```text
The virtual machine out of memory.
Try "make -j1" !!!
```

#### 2.2 error: dereferencing pointer to incomplete type ¡®struct ucontext¡¯

vi x86_64-pc-linux-gnu/libgcc/md-unwind-support.h +61

```diff
- struct ucontext *uc_ = context->cfa;
+ struct ucontext_t *uc_ = context->cfa; 
```

#### 2.3 msgfmt: error while loading shared libraries: libgettextsrc-0.19.8.1.so: cannot open shared object file: No such file or directory

```log
$ find /usr/ -name "*gettext*"
...
/usr/local/lib/libgettextsrc-0.19.8.1.so
...

$ msgfmt --version
msgfmt: error while loading shared libraries: libgettextlib-0.19.8.1.so: cannot open shared object file: No such file or directory

$ ldd /usr/local/bin/msgfmt 
	linux-vdso.so.1 (0x00007ffdf0727000)
	libgettextsrc-0.19.8.1.so => /usr/lib/libgettextsrc-0.19.8.1.so (0x00007efdba12d000)
	libgettextlib-0.19.8.1.so => not found
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007efdb9d3c000)
	libgettextlib-0.19.8.1.so => /usr/local/lib/libgettextlib-0.19.8.1.so (0x00007efdb99a9000)
	libiconv.so.2 => /usr/local/lib/libiconv.so.2 (0x00007efdb96c4000)
	/lib64/ld-linux-x86-64.so.2 (0x00007efdba58f000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007efdb9326000)
	libtinfo.so.5 => /lib/x86_64-linux-gnu/libtinfo.so.5 (0x00007efdb90fc000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007efdb8edd000)

# src and lib !!!
$ sudo ln -s /usr/local/lib/libgettextsrc-0.19.8.1.so /usr/lib/libgettextsrc-0.19.8.1.so
$ sudo ln -s /usr/local/lib/libgettextlib-0.19.8.1.so /usr/lib/libgettextlib-0.19.8.1.so
```

