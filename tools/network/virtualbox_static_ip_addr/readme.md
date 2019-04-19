##ubuntu 16.04
1. /etc/network/interfaces
```
./interfaces
```

2. /etc/NetworkManager/NetworkManager.conf
managed > true

3.  /etc/resolvconf/resolv.conf.d/base
```
nameserver 223.5.5.5
nameserver 223.6.6.6
```
resolvconf -u

4. /etc/init.d/networking restart
