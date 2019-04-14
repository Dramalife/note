ioctl在socket中的一些用法及示例

#### keywords
|no|key|
|--|--|
|0|ioctl|
|1|socket|
|2|mutex_lock|

```
函数 : ioctl(int fd, int request, void * arg)
定义 : <sys/ioctl.h>
功能 : 控制I/O设备, 提供了一种获得设备信息和向设备发送控制参数的手段.
参数 : int  fd      文件句柄. 用于socket时, 是socket套接字.
       int  request 函数定义的所有操作. 关于socket的操作, 定义在<linux/sockios.h>文件中.
       void *arg    指针的类型依赖于request参数.
```
#### userspace
```
/*run in userspace*/
int demo_get_from_kernel(char *name, char *value)
{
  struct usr_struct io_args;/*struct defined at linux/...*/
  int fd = -1, ret = 0;

  if(fd = socket(AF_INET,SOCK_STREAM, 0) < 0)
    return -1;

  memset(&io_args, 0, sizeof(struct usr_struct));

  io_args.cmd_CMD = CMD_ENV_GET;/CMD_ENV_GET defined at linux/.../
  strncpy(io_args.x.name, name, MAX_LEN);

  ret = ioctl(fd, SIOCGXXXXXX, &io_args);/*SIOCG(get)XXXXXX defined at linux/include/linux/sockxx.h*/
  close(fd);
  if(ret < 0)/*ioctl error*/
    return -1;
strncpy(value,io_args.x.value,MAX_LEN);
}

int demo_set_to_kernel(char *name, char *value)
{
  struct usr_struct io_args;/*struct defined at linux/...*/
  int fd = -1, ret = 0;

  if(fd = socket(AF_INET,SOCK_STREAM, 0) < 0)
    return -1;

  memset(&io_args, 0, sizeof(struct usr_struct));

  io_args.cmd_CMD = CMD_ENV_SET;/CMD_ENV_SET defined at linux/.../
  strncpy(io_args.x.name, name, MAX_LEN);
strncpy(io_args.x.value, value, MAX_LEN);
  ret = ioctl(fd, SIOCSXXXXXX, &io_args);/*SIOCS(set)XXXXXX defined at linux/include/linux/sockxx.h*/
  close(fd);
  if(ret < 0)/*ioctl error*/
    return -1;
}
```
#### kernelspace
```
/*run in kernelspace*/
static long sock_ioctl(struct file *file, unsigned cmd, unsigned long arg)
{
  void __user *argp = (void __user *)arg;

  switch(cmd)
  {
    case SIOCGXXXXXX:
    case SIOCSXXXXXX:
      mutex_lock(&mutex);
      err = ioctl_handler(cmd , argp);
      mutex_unlock(&mutex);
  }
}

int ioctl_handler(unsigned int cmd, vod __user *arg)
{
  struct usr_struct io_args;/*struct defined at linux/...*/
  int err = 0, cmd_CMD = 0;
  char *buf;

  switch(cmd)
  {
    case SIOCGXXXXXX:
    case SIOCSXXXXXX:
    {
      if(copy_from_user(&ioctl_args, arg, sizeof(struct usr_struct)) < 0)
      {
        return -EFAULT;
      }
      cmd_CMD = ioctl_args.cmd_CMD;

      switch(cmd_CMD)
      {
        case CMD_ENV_GET:
          buf = xxx_getenv(ioctl_args.x.name);
          if(buf != NULL)
          {
            strncpy(ioctl_args.x.value, buf, MAX_LEN);
          }
          break;
        case CMD_ENV_SET:
          xxx_setenv(ioctl_args.x.name,ioctl_args.x.value);
          break;
      }
    }
  }
}
```
