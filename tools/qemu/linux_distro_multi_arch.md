## 0. Documents
[QEMU - HOME](https://www.qemu.org/)  
[Debian - QEMU IMG](https://people.debian.org/~aurel32/qemu/)  
[Blog - ethernet bridge](https://www.pianshen.com/article/83761630009/)  


## 1. Start up

### Errors

#### cannot set up guest memory 'mips_malta.ram': Cannot allocate memory
```bash
# ref : https://blog.csdn.net/szuhuanggang/article/details/88770938
sudo sysctl -a | grep overcommit
sudo sysctl vm.overcommit_memory=1
```

#### Could not initialize SDL(No available video device) - exiting
```bash
# Problem
$ qemu-system-x86_64 -hda debian_wheezy_amd64_standard.qcow2
## qemu-system-x86_64: warning: TCG doesn't support requested feature: CPUID.01H:ECX.vmx [bit 5]
## Could not initialize SDL(No available video device) - exiting

# Solve
# ref : https://chuiwenchiu.wordpress.com/2014/12/10/qemu-could-not-initialize-sdlno-available-video-device-exiting/
$ qemu-system-x86_64 -curses -hda debian_wheezy_amd64_standard.qcow2
```

### Performance
https://www.cnblogs.com/sunylat/p/6217538.html



### Run Debian wheezy mips on aarch64
```bash
# ref https://people.debian.org/~aurel32/qemu/amd64/
wget https://people.debian.org/~aurel32/qemu/mips/debian_wheezy_mips_standard.qcow2
wget https://people.debian.org/~aurel32/qemu/mips/vmlinux-3.2.0-4-5kc-malta

# Origin command - error
qemu-system-mips64 -M malta -kernel vmlinux-3.2.0-4-5kc-malta -hda debian_wheezy_mips_standard.qcow2 -append "root=/dev/sda1 console=tty0"

# Fix - No available video device
qemu-system-mips64 -M malta -kernel vmlinux-3.2.0-4-5kc-malta -hda debian_wheezy_mips_standard.qcow2 -append "root=/dev/sda1 console=tty0" -curses

# Specific net dev & mem size
qemu-system-mips64.exe -M malta -kernel vmlinux-3.2.0-4-5kc-malta -hda debian_wheezy_mips_standard.qcow2 -append "root=/dev/sda1 console=ttyS0"  -nographic --net nic -net tap,ifname=tap -m 2048m
```

### Run Debian wheezy x86_64 on aarch64
```bash
# download image
wget https://people.debian.org/~aurel32/qemu/amd64/debian_wheezy_amd64_standard.qcow2

# Origin command - error
qemu-system-x86_64 -hda debian_wheezy_amd64_standard.qcow2

# Fix - No available video device
qemu-system-x86_64 -hda debian_wheezy_amd64_standard.qcow2 -curses
# no-boot info
qemu-system-x86_64 -hda debian_wheezy_amd64_standard.qcow2 -nographic
```

### Bridge network interface
```bash
sudo apt-get install uml-utilities 
sudo vi /etc/network/interfaces
```
```bash
busybox brctl --help

```

#### Failed to open '/dev/net/tun' : No such file or directory
```
sudo mkdir -p /dev/net
sudo mknod /dev/net/tun c 10 200
sudo chmod 600 /dev/net/tun
```

```
sysctl -w net.ipv4.ip_forward=1
```

### Login
Debian 7 Default password
root/root

