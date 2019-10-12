> \# note "dd(man 1 dd)" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.10.12;  
\# Update   
\#  
  


#### 1. File exists(target:source.tgz, carrier:quagga-1.2.4.tar.gz)

```bash
dramalife@server:~/temp $ ls -al
total 32256
drwxrwxr-x  3 dramalife dramalife     4096 Oct 12 06:21 .
drwxr-xr-x 11 dramalife dramalife     4096 Oct 12 06:11 ..
-rwxrw-r--  1 dramalife dramalife  2925847 Oct 12 06:21 quagga-1.2.4.tar.gz
-rw-rw-r--  1 dramalife dramalife      160 Oct 12 06:00 source.tgz
```


##### 1.1 Align carrier(optional)

```bash
dramalife@server:~/temp $ dd of=quagga-1.2.4.tar.gz if=/dev/zero bs=1 count=74153 seek=2925847
dramalife@server:~/temp $ ls -al
total 32328
drwxrwxr-x  3 dramalife dramalife     4096 Oct 12 06:21 .
drwxr-xr-x 11 dramalife dramalife     4096 Oct 12 06:11 ..
-rwxrw-r--  1 dramalife dramalife  3000000 Oct 12 06:23 quagga-1.2.4.tar.gz
-rw-rw-r--  1 dramalife dramalife      160 Oct 12 06:00 source.tgz
```

#### 2. Carry

```bash
dramalife@server:~/temp $ dd of=quagga-1.2.4.tar.gz if=source.tgz bs=1 seek=3000000
dramalife@server:~/temp $ ls -al
total 32328
drwxrwxr-x  3 dramalife dramalife     4096 Oct 12 06:21 .
drwxr-xr-x 11 dramalife dramalife     4096 Oct 12 06:11 ..
-rwxrw-r--  1 dramalife dramalife  3000160 Oct 12 06:26 quagga-1.2.4.tar.gz
-rw-rw-r--  1 dramalife dramalife      160 Oct 12 06:00 source.tgz
```

##### 2.1 Test carrier(optional)

```bash
dramalife@server:~/temp $ tar zxvf quagga-1.2.4.tar.gz >/dev/null

gzip: stdin: decompression OK, trailing garbage ignored
tar: Child returned status 2
tar: Error is not recoverable: exiting now
```

#### 3. Get "target"

```bash
dramalife@server:~/temp $ dd if=quagga-1.2.4.tar.gz of=target.tgz bs=1 skip=3000000
dramalife@server:~/temp $ ls -al
total 32336
drwxrwxr-x  4 dramalife dramalife     4096 Oct 12 06:31 .
drwxr-xr-x 11 dramalife dramalife     4096 Oct 12 06:11 ..
-rwxrw-r--  1 dramalife dramalife  3000160 Oct 12 06:26 quagga-1.2.4.tar.gz
-rw-rw-r--  1 dramalife dramalife      160 Oct 12 06:00 source.tgz
-rw-rw-r--  1 dramalife dramalife      160 Oct 12 06:31 target.tgz
```

##### 3.1 Test "target"

```bash
dramalife@server:~/temp $ tar zxvf target.tgz 
source/
source/ss.txt
```
