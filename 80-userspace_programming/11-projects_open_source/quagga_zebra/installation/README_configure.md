Back to [README.md](/80-userspace_programming/11-projects_open_source/quagga_zebra/install_quagga/README.md)

#### 1 The Configure script and its options
Quagga has an excellent configure script which automatically detects most host configurations.  There are several additional configure options you can use to turn off IPv6 support, to disable the compilation of specific daemons, and to enable SNMP support. 

- --disable-ipv6

  Turn off IPv6 related features and daemons.  Quagga configure script automatically detects IPv6 stack.  But sometimes you might want to disable IPv6 support of Quagga. 

- --disable-zebra

  Do not build zebra daemon. 

- --disable-ripd

  Do not build ripd. 

- --disable-ripngd

  Do not build ripngd. 

- --disable-ospfd

  Do not build ospfd. 

- --disable-ospf6d

  Do not build ospf6d. 

- --disable-bgpd

  Do not build bgpd. 

- --disable-bgp-announce

  Make `bgpd` which does not make bgp announcements at all.  This feature is good for using `bgpd` as a BGP announcement listener. 

- --enable-netlink

  Force to enable GNU/Linux netlink interface.  Quagga configure script detects netlink interface by checking a header file.  When the header file does not match to the current running kernel, configure script will not turn on netlink support. 

- --enable-snmp

  Enable SNMP support.  By default, SNMP support is disabled. 

- --disable-opaque-lsa

  Disable support for Opaque LSAs (RFC2370) in ospfd. 

- --disable-ospfapi

  Disable support for OSPF-API, an API to interface directly with ospfd. OSPF-API is enabled if –enable-opaque-lsa is set. 

- --disable-ospfclient

  Disable building of the example OSPF-API client. 

- --disable-ospf-te

  Disable support for OSPF Traffic Engineering Extension (RFC3630) this requires support for Opaque LSAs. 

- --disable-ospf-ri

  Disable support for OSPF Router Information (RFC4970 & RFC5088) this requires support for Opaque LSAs and Traffic Engineering. 

- --enable-isisd

  Build isisd. 

- --enable-isis-topology

  Enable IS-IS topology generator. 

- --enable-isis-te

  Enable Traffic Engineering Extension for ISIS (RFC5305) 

- --enable-multipath=ARG

  Enable support for Equal Cost Multipath. ARG is the maximum number of ECMP paths to allow, set to 0 to allow unlimited number of paths. 

- --disable-rtadv

  Disable support IPV6 router advertisement in zebra. 

- --enable-gcc-rdynamic

  Pass the `-rdynamic` option to the linker driver.  This is in most cases neccessary for getting usable backtraces.  This option defaults to on if the compiler is detected as gcc, but giving an explicit enable/disable is suggested. 

- --enable-backtrace

  Controls backtrace support for the crash handlers. This is autodetected by default. Using the switch will enforce the requested behaviour, failing with an error if support is requested but not available.  On BSD systems, this needs libexecinfo, while on glibc support for this is part of libc itself. 

You may specify any combination of the above options to the configure script.  By default, the executables are placed in /usr/local/sbin and the configuration files in /usr/local/etc. The /usr/local/ installation prefix and other directories may be changed using the following  options to the configuration script. 

- --prefix=prefix

  Install architecture-independent files in prefix [/usr/local]. 

- --sysconfdir=dir

  Look for configuration files in dir [prefix/etc]. Note that sample configuration files will be installed here. 

- --localstatedir=dir

  Configure zebra to use dir for local state files, such as pid files and unix sockets. 

```
% ./configure --disable-ipv6
```

This command will configure zebra and the routing daemons. 



#### 2 Least-Privilege support
Additionally, you may configure zebra to drop its elevated privileges shortly after startup and switch to another user. The configure script will automatically try to configure this support. There are three configure options to control the behaviour of Quagga daemons. 

- --enable-user=user

  Switch to user ARG shortly after startup, and run as user ARG in normal operation. 

- --enable-group=group

  Switch real and effective group to group shortly after startup.  

- --enable-vty-group=group

  Create Unix Vty sockets (for use with vtysh) with group owndership set to group. This allows one to create a seperate group which is restricted to accessing only the Vty sockets, hence allowing one to delegate this group to individual users, or to run vtysh setgid to this group. 

The default user and group which will be configured is ’quagga’ if no user or group is specified. Note that this user or group requires write access to the local state directory (see –localstatedir) and requires at least read access, and write access if you wish to allow daemons to write out their configuration, to the configuration directory (see –sysconfdir). 

On systems which have the ’libcap’ capabilities manipulation library (currently only linux), the quagga system will retain only minimal capabilities required, further it will only raise these capabilities for brief periods. On systems without libcap, quagga will run as the user specified and only raise its uid back to uid 0 for brief periods. 



#### 3 Linux Notes
There are several options available only to GNU/Linux systems: [1](http://172.16.127.202/Linux-notes.html#FOOT1).  If you use GNU/Linux, make sure that the current kernel configuration is what you want.  Quagga will run with any kernel configuration but some recommendations do exist. 

- CONFIG_NETLINK

  Kernel/User netlink socket. This is a brand new feature which enables an advanced interface between the Linux kernel and zebra (see [Kernel Interface](http://172.16.127.202/Kernel-Interface.html#Kernel-Interface)). 

- CONFIG_RTNETLINK

  Routing messages. This makes it possible to receive netlink routing messages.  If you specify this option, `zebra` can detect routing information updates directly from the kernel (see [Kernel Interface](http://172.16.127.202/Kernel-Interface.html#Kernel-Interface)). 

- CONFIG_IP_MULTICAST

  IP: multicasting.   This option should be specified when you use `ripd` (see [RIP](http://172.16.127.202/RIP.html#RIP)) or `ospfd` (see [OSPFv2](http://172.16.127.202/OSPFv2.html#OSPFv2)) because these protocols use multicast. 

IPv6 support has been added in GNU/Linux kernel version 2.2.  If you try to use the Quagga IPv6 feature on a GNU/Linux kernel, please make sure the following libraries have been installed.  Please note that these libraries will not be needed when you uses GNU C library 2.1 or upper. 

- `inet6-apps`

  The `inet6-apps` package includes basic IPv6 related libraries such as `inet_ntop` and `inet_pton`.  Some basic IPv6 programs such as `ping`, `ftp`, and `inetd` are also included. The `inet-apps` can be found at [ftp://ftp.inner.net/pub/ipv6/](ftp://ftp.inner.net/pub/ipv6/). 

- `net-tools`

  The `net-tools` package provides an IPv6 enabled interface and routing utility.  It contains `ifconfig`, `route`, `netstat`, and other tools.  `net-tools` may be found at http://www.tazenda.demon.co.uk/phil/net-tools/. 

------

#### Footnotes

GNU/Linux has very flexible kernel configuration features