Back to [README.md](/80-userspace_programming/11-projects_open_source/quagga_zebra/install_quagga/README.md)

Installing the software to your system consists of copying the compiled programs and supporting files to a standard location. After the installation process has completed, these files have been copied from your work directory to /usr/local/bin, and /usr/local/etc. 

To install the Quagga suite, issue the following command at your shell prompt: `make install`. 

```
%
% make install
%
```

Quagga daemons have their own terminal interface or VTY.  After installation, you have to setup each beast’s port number to connect to them.  Please add the following entries to /etc/services. 

```
zebrasrv      2600/tcp		  # zebra service
zebra         2601/tcp		  # zebra vty
ripd          2602/tcp		  # RIPd vty
ripngd        2603/tcp		  # RIPngd vty
ospfd         2604/tcp		  # OSPFd vty
bgpd          2605/tcp		  # BGPd vty
ospf6d        2606/tcp		  # OSPF6d vty
ospfapi       2607/tcp		  # ospfapi
isisd         2608/tcp		  # ISISd vty
pimd          2611/tcp		  # PIMd vty
nhrpd         2612/tcp		  # nhrpd vty
```

If you use a FreeBSD newer than 2.2.8, the above entries are already added to /etc/services so there is no need to add it. If you specify a port number when starting the daemon, these entries may not be needed. 

You may need to make changes to the config files in /etc/quagga/*.conf. See [Config Commands](http://172.16.127.202/Config-Commands.html#Config-Commands). 