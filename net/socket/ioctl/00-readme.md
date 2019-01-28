### Loopback

### userspace
```
//userspace
void loopback_agxxx_test(int skip; int type, struct factxxx_test_cfg_s *factxxx_test);
int mmm_factxxx_test(struct factxxx_test_cfg_s *data);

factxxx_test.loopback_agxxx_time = agxxx_info.loopback_agxxx_time/2;
loopback_agxxx_test(skip, TYPE , &factxxx_test);
////////////////////
mmm_factxxx_test(factxxx_test);
////////////////////
fd = socket(AF_INET, SOCK_STREAM, 0);
ioctl(fd, SIOXXXX, %io_args);
memcpy(data, &(io_args.xxx),sizeof(factxxx_test_cfg_s));//TODO: to learn;
```

### kernel
```
//linux/net/socket.c
sock_ioctl
{
case SIOXXXX:/**/
  ioctl_handler(cmd,argp);
}

//kernel/xxx/platform/common/plat.c
int ioctl_handler(unsigned int cmd,void __user *arg)
{
  struct ioctl_args io_args;
  switch(cmd)
  case FACTORY:
    iflist_test(&(io_args.xxx));
}

//kernel/xxx/platform/common/factxxx.c
int iflist_test(struct factxxx_test_cfg_s *factxxx_test)
{
  kernel_thread(test_wan, &packet_info,CLONE_KERNEL);//TODO: to learn;
}
int test_wan(void *data)
{
  memcpy(packet_info,(struct packet_info_s *)data);
  ndo_start_xmit(skb,dev);//TODO: to learn;
}
```

### Dramalife

```
//trace "SIOXXXX"
//kernel/include/linux/sockxx.h
#define SIOCBRDELBR 0x8888 /*remove bridge device*/
/*
桥接口,EoIP等的具体实现可能也在kernelspace
*/
```

Tks(H):47 61 6F  58 75
