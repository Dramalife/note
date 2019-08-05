## SET IP

### SET IPV6 ADDRESS (quagga-1.2.4)
|STEP NO. |CMD or FUNC |SOURCE |
|--|--|--|
| 0|"ipv6 address X:X::X:X/M"	|./zebra/interface.c +2400 |
| 1|ipv6_address_install	|./zebra/interface.c +2448 |
| 2|>if_prefix_add_ipv6		|.zebra/ioctl.c +453       |
| 3|>if_ioctl_ipv6		|.zebra/ioctl.c +84        |

