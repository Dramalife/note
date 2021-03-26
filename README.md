![GitHub top language](https://img.shields.io/github/languages/top/Dramalife/note.svg?color=green&logo=Linux&logoColor=black)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Dramalife/note.svg?color=blue)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/Dramalife/note.svg)
![C/C++ CI](https://github.com/Dramalife/note/workflows/C/C++%20CI/badge.svg)


# NOTE
Dramalife\`s note  

## 1 About
### 1.1 Favorite
[- Markdown grammar](/tools/coding/markdown.md), [editor : Typora](https://typora.io/)  
[- Linux source code online](https://elixir.bootlin.com/linux/latest/source)  
[- kernelnewbies.org - kernel changelog](https://kernelnewbies.org)  
[- RFC Search online](https://www.rfc-editor.org/search/rfc_search.php)  
[- Majordomo lists at VGER.KERNEL.ORG](http://vger.kernel.org/vger-lists.html)  
[- FREE SOFTWARE DIRECTORY](https://directory.fsf.org/wiki/GNU)  
[- StackOverFlow.com](https://stackoverflow.com/)  
[- sunxi wiki](http://linux-sunxi.org/Main_Page)  
[- gcc-linaro](https://releases.linaro.org/components/toolchain/binaries/)  
[- GNU Mirror-tsinghua](https://mirrors.tuna.tsinghua.edu.cn/gnu/)  
[- linux-kernel(aliyun-mirror)](http://mirrors.aliyun.com/linux-kernel/)  
[- Armbian_release_mirror_tsinghua](https://mirrors.tuna.tsinghua.edu.cn/armbian-releases/)  
[- Linux C(userspace) API Ref (pku_arranged)](http://net.pku.edu.cn/~yhf/linux_c/)  
[- 码云极速下载](https://gitee.com/organizations/mirrors/projects)  

### 1.2 Directories
| Directory			 | Introduction				|
|--|--|
| 50-books			 |					|
| 70-gcc_gnu_compiler_collection | GCC related				|
| 80-userspace_programming       | userspace code			|
| 81-kernel_programming          | kernelspace code			|
| 90-operating_system            | OS related				|
| lib_dramalife                  | C libraries of dramalife		|
| LICENSE                        | license				|
| --personal                     | personal configuration files		|
| README.md                      | readme				|
| tools                          | tools for coding, diagnose ...	|

### 1.3 Clone
```bash
git clone https://github.com/Dramalife/note.git --depth=1
```

## 2 Programming
### 2.1 NEW
|no|date|content|
|--|--|--|
|00|2019.01.09|Linux C Signal;fork();zombie thread;|
|01|2019.01.21|TCP/IP|
|02|2019.01.21|CLI,u-boot,zebra\(quagga\)|
|03|2019.01.21|[GNU C:__attribute__](/70-gcc_gnu_compiler_collection/gnu_c_attribute)|
|04|2019.01.28|[ioctl,socket](/81-kernel_programming/network/socket/)|
|05|2019.03.14|[process&thread \- sync&com](/coding_thread)|
|06|2019.05.09|[compile(gcc),include](/80-userspace_programming/gcc)|
|07|2019.05.08|[netlink,userspace&](/80-userspace_programming/netlink)|
|08|2019.06.20|[lsof(list open files),strace(syscall_strace) at /tools](/tools)|
|09|2019.07.07|[lib.so-shared library(create lib, link, load, make lib executable)](/70-gcc_gnu_compiler_collection/dynamic_exec_libx_so) |
|0A|2019.08.23|[gcc-make-opensource](/tools/gcc), [70-gcc_gnu_compiler_collection](/70-gcc_gnu_compiler_collection) |
|0B|2019.10.31|[inotify](/80-userspace_programming/inotify)-Gather filesystem usage statistics; |
|0C|2019.12.23|[pthread_sync](/80-userspace_programming/thread_sync)-mutex,condition variable; |
|0D|2019|[glibc_sample](/80-userspace_programming/00-libc_sample), [mylib](/lib_dramalife); |
|0E|2019|IPC :: [ipc&mylib_ipc](/80-userspace_programming/ipc), [ipc_old](/80-userspace_programming/thread_process/31-com_process) |
|0F|2020.01.05|[I/O - signal/multiplexing](/80-userspace_programming/io) |
|10|2020.04.19|[kerberos(network security)](/80-userspace_programming/network/network_security/kerberos_sample) TODO:encrypt,auth |
|11|2020.04.26|[simple shell(named - mysh)](/80-userspace_programming/11-projects_open_source/my_shell_2020) Bug:pipe,job control;|
|12|2020.05.10|[program protection (todo - opensource)](/80-userspace_programming/11-projects_open_source/program_protection)|
|  | | |

### 2.2 RECALL
|no|date|content|
|--|--|--|
|0|2019.01.22|git,svn : shell;git:web|
|0|2019.01.22|vim hot key|
|0|2019.02.23|zebra module communication|
|0|2019.09 19|[endian](/80-userspace_programming/endian_check) |
|0|2019.10.31|[show_cmdline_of_pid_and_ppid](/80-userspace_programming/pid_ppid) |
| | | |

### 2.3 TODO List
[move_to_README_list.md](/README_list.md)

## 3 Hardware
### 3.1 Development Boards
|No|Name|Date|Details|
|--|--|--|--|
|0|GEC 51 MCU|2016.08.17||
|1|Arduino UNO|2016.10.16||
|2|Arduino MEGA 2560|2017.05.03||
|-|AIO-3399J| |Drivers:DP83867,LTC2941,|
|-|STM32F107VCT6| |ethernet,NB-Iot/GSM|
|3|Raspberry Pi 3B |2018.07|Arm v7|
|4|[Orange Pi Zero](http://www.orangepi.cn/orangepizero/index_cn.html) |2018.12.27<br>2020.10.29 +1<br>2020.11.09 +1 |SoC:sunxi(Allwinner H2),Architecture:Cortex-A7,Instruction Set:ARMv7;|
|5|[Banana Pi BPI-R2](http://wiki.banana-pi.org/Banana_Pi_BPI-R2) |2020.01.10 |SoC:MediaTek MT7623N,Architecture:Cortex-A7,Introduction Set:ARMv7; RAM:2GB,EMMC:8GB; 5\*Gigabit Ethernet,2\*SATA,1\*PCIE,2\*USB3.0;|
|6|[ROC-RK3328-CC](http://wiki.t-firefly.com/zh_CN/ROC-RK3328-CC/intro.html)|2020.04.04 |SoC:RK3328,Architecture:Cortex-A53,Introduction Set:ARMv8;|
|7|[Banana Pi BPI-R1](http://wiki.banana-pi.org/Banana_Pi_BPI-R1) |2020.05.12 +2 |SoC:sunxi(Allwinner A20),Architecture:ARM Cortex -A7 Dual-Core,Introduction Set:ARMv7; RAM:1GB; 5\*Gigabit Ethernet,1\*SATA;|
|8|[Orange Pi One](http://www.orangepi.cn/orangepione/index_cn.html) |2020.11.09 +2 |SoC:sunxi(Allwinner H3),Architecture:Cortex-A7,Introduction Set:ARMv7; RAM:512MB;|
|9|[Nano Pi M4](http://wiki.friendlyarm.com/wiki/index.php/NanoPi_M4/zh)|2021.01.27 +2 |SoC:RK3399,Architecture:Cortex-A72+Cortex-A53,Introduction Set:ARMv8; RAM:2GB,EMMC:16GB; 1\*Gigabit Ethernet,4\*USB3.0(hub);|

### 3.2 Devices
|No|Name|Date|Details|
|--|--|--|--|
| 0|TFT LCD(ili9486) |2019.07.24- | drivers/staging/fbtft/fb\_ili9486.c|

## 4. Others
<div align=right>
  <img src="http://www.gnu.org/graphics/heckert_gnu.transp.small.png" width="10%">
  <img src="https://www.kernel.org/theme/images/logos/tux.png" width="10%">  
  <img src="https://strace.io/Straus.png" width="10%">  
  <img src="https://github.com/favicon.ico" width="10%">
  <img src="https://avatars0.githubusercontent.com/u/15922037?s=200&v=4" width="10%">  
</div>
  
  
<div align=right>
  <img src="https://busybox.net/images/busybox1.png" width="10%">
  <img src="https://www.vim.org/images/vim_header.gif" width="10%">
  <img src="https://www.linux-sunxi.org/images/c/c5/Logo-155x155.png" width="10%" alt="sunxi">
</div>


<div align=right>
  <img src="http://www.tcpdump.org/images/logo.png" width="10%" alt="tcmdump">
</div>
  
    

EOF
