# dlpi_dramalifepi - For interprocess socket communication
```
STATUS : STOPPED(2020.03.27)
```



## Olds
### Change Log(init ~ 2020.03.27)
```log
commit efcd14dc9811d2217f00308351912d25eccae331
Author: rpi_omv <dramalife@live.com>
Date:   Sat Aug 17 14:08:14 2019 +0000

    split file.

commit 150e5a1647216cf2c84106f6a7fb6b1856f443b6
Author: dramalife@rc_ubuntu_vdev_x86 <dramalife@live.com>
Date:   Fri Aug 16 19:47:09 2019 +0800

    add backtrace,

commit 272edd072878a2acb7c0f2aa8b4194249d45f40a
Author: dramalife@rc_ubuntu_vdev_x86 <dramalife@live.com>
Date:   Thu Aug 15 11:46:28 2019 +0800

    update

commit 09761841066a2dda803f00ec0916b9c567c05706
Author: dramalife@rc_ubuntu_vdev_x86 <dramalife@live.com>
Date:   Tue Aug 13 17:24:58 2019 +0800

    update datastruct

commit 59b4cbf79b9d32524451ec3862bbfd524a099fcc
Author: Dramalife <dramalife@live.com>
Date:   Sun Aug 11 13:38:29 2019 +0000

    new project dlpi_dramalifepi
```
### readme.txt
```bash
$ gcc --version
gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ uname -a
Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
```

```c
typedef struct dlpi_frame
{
char *des_sock_path;	//specific sock path
u8_t mechine_specific_code[2];	//specific mechine, not useful yet.
u8_t lll_type[2];	//(toDES|to_others|)
u8_t global_data_struct_code[2];	//16 bit.
void *buffer;	//(trans_to_datastruct|trans_to_DES_level)
}dlpi_frame;
```
