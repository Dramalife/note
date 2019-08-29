> \# note "xl2tp" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref Url : https://www.jianshu.com/p/16ef268d8233  
\#  
\# Init : 2019.08.27;  
\# Update   
\#  
  

```bash
$ uname -a
Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
$ gcc --version
gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
$ bash --version
GNU bash, version 4.3.11(1)-release (i686-pc-linux-gnu)
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

This is free software; you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

```

# LNS/LAC config
doc/l2tpd.conf.sample

# PPP config
examples/ppp-options.xl2tpd

# CHAP secrets
examples/chapsecrets.sample

### ERRORS (running)

#### ERROR 1 "Unable to open /var/run/xl2tpd/l2tp-control for reading."

```bash
$ xl2tpd -c ~/note/l2tpd.conf_LNS_dramalife -s ~/note/chapsecrets.sample_dramalife -D
xl2tpd[1897]: Not looking for kernel SAref support.
xl2tpd[1897]: Using l2tp kernel support.
xl2tpd[1897]: open_controlfd: Unable to open /var/run/xl2tpd/l2tp-control for reading.

$ sudo mkdir /var/run/xl2tpd
$ sudo touch /var/run/xl2tpd/l2tp-control
```

