![GitHub top language](https://img.shields.io/github/languages/top/Dramalife/note.svg?color=green&logo=Linux&logoColor=black)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Dramalife/note.svg?color=blue)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/Dramalife/note.svg)


# NOTE
Dramalife\`s note  
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


### Clone

```bash
git clone https://github.com/Dramalife/note.git --depth=1
```

### NEW
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
|  | | |
|  | | |

### RECALL
|no|date|content|
|--|--|--|
|0|2019.01.22|git,svn : shell;git:web|
|0|2019.01.22|vim快捷键|
|0|2019.02.23|zebra module communication|
|0|2019.09 19|[endian](/80-userspace_programming/endian_check) |
| | | |
| | | |

### TODO List
|No|Status|Item|Path|Add-Finish|
|--|--|--|--|--|
|0 |HALT|EoIP(usr,kernel)|[EoIP](/81-kernel_programming/network/ip_protocal/eoip/),[rfc3378](/50-books/rfc_ref/rfc3378.txt)|20190122-20190125(socket_ioctl)-|
| ^|HALT |l2tp(protocol) |[50_note](/50-books/00-note/l2tp_layer_two_tunneling_protocol/) |2019.08.13-08.28(compile&run)-2019.09.17(halt)- |
| ^|PLAN     |pppd |[50_note](/50-books/00-note/l2tp_layer_two_tunneling_protocol/) |2019.08.28- |
|1 |DOING|4g(9507_driver)|[4g](/81-kernel_programming/network/4g_cell)|20190122-|
|2 |DOING|vim|[vim](/tools_coding/vim)|20190122-Updating-|
|3 |TODO|framebuffer & i2c| - |201811xx-|
|  |DONE|gcc attribute(section)|[gcc attribute-section](/70-gcc_gnu_compiler_collection/gnu_c_attribute)|2019.01.21-2019.07.09|
|4 |**TODO**|mutex_lock| - |20190130-|
|5 |TODO|Relationship of Shell,Stdio and Process| - |20190211-|
|  |DONE|git using on command line interface|[git](/tools/coding/git/)|2019.03.28|
|  |DONE|git compile|[git-make](/tools/gcc/git_compile.sh)|2019.06.18|
|6 |**DOING**|kernel-net driver & protocol| - |2019.03.30-|
|7 |PLAN|if_down,if_up,link_up| |2019.05.06- |
|8 |HALT|quagga(zebra)|[1.source code](/tools/get_quagga-1_2_4.sh), |2019.05.04-2019.07.24- |
|9 |TODO|SSH密钥| [ssh_key](/tools/ssh_key.md)| |
|10|DONE|link list|[link_list.c](80-userspace_programming/33-datastruct/link_list/link_list.c) |2019.06.26-2019.07.05 |
| ^|HALT|link_list(char device Module) | - |2019.07.05-2019.07.24- |
|12|DONE|backtrace,objdump |[backtrace_objdump](/70-gcc_gnu_compiler_collection/backtrace/) |2019.07.06-2019.07.24 |
|13|HALT|Socket sample | [sock_spi_i2c_gpio](/50-books/00-note/sock_spi_i2c_gpio/) |2019.07.07-2019.09.17(halt)- |
| ^|**DOING**|             ^| [dlpi_socket](/80-userspace_programming/com_unix_sock/dlpi_dramalifepi/) |2019.08.11-(keep)- |
|14|CANCLED|libdramalife:auto allocate COLOR | |2019.07.08-2019.07.09|
|15|PLAN |elf-loader(Barry Song) |[elf-loader](/80-userspace_programming/00-libc_sample/man3_dlfcn_dlopen/elf-loader) |2019.08.29- |
|16|PLAN |ABI/EABI |[note-ABI/EABI](/90-operating_system/ABI) |2019.09.09PAUSE- |
|17|HALT|fs(filesystem,tinyfs) |[tiny_fs](/81-kernel_programming/device_drivers/tiny_fs) |2019.09.06-(keep)-2019.09.17(halt,>network)- |
|18|**DOING**|Netlink/netlink(userspace) | |2019.11.01- |
|19|**DOING**|igmpproxy |[multicast & igmpproxy](/81-kernel_programming/networks/ip_internet_protocol/multicast); |2019.12- |
|20|**DOING**|inotify |STAGE-reading source code,[IBM:inotify-sample](https://www.ibm.com/developerworks/cn/linux/l-inotify/) |2020.01.17- |
| | | | | |
| | | | | |
| | | | | |
| | | | | |
| | | | | |

### Boards
|No|Name|Date|Details|
|--|--|--|--|
|0|GEC 51 MCU|2016.08.17||
|1|Arduino UNO|2016.10.16||
|2|Arduino MEGA 2560|2017.05.03||
| |AIO-3399J| |Drivers:DP83867,LTC2941,|
| |STM32F107VCT6|ethernet,NB-Iot/GSM|
|3|Raspberry Pi 3B |2018.07|Arm v7|
|4|Orange Pi Zero |2018.12.27|SoC:sunxi,Architecture:Cortex-A7,Instruction Set:Arm v7;|
|5|Banana Pi R2 |2020.01.10 |MTK7623N;Arm v7; RAM:2GB,EMMC:8GB; 5\*Gigabit Ethernet,2\*SATA,1\*PCIE,2\*USB3.0;|
| | | | |
| | | | |
| | | | |

### Devices
|No|Name|Date|Details|
|--|--|--|--|
| 0|TFT LCD(ili9486) |2019.07.24- | drivers/staging/fbtft/fb\_ili9486.c|
| | | | |

### Directories
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

### Games  

Upload and include files in github,funny!

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
