Zebra,U-boot代码中命令行命令的添加和原理

### content
|||
|--|--|
|0|zebra|
|1|u-boot|

#### reference

|no|key word|path|
|--|--|--|
|0|__attribute__|GNU C|

### zebra
#### #DEFUN
```
/* DEFUN for vty command interafce. Little bit hacky ;-). */
#define DEFUN(funcname, cmdname, cmdstr, helpstr) \
  int funcname (struct cmd_element *, struct vty *, int, char **); \
  struct cmd_element cmdname = \
  { \
    cmdstr, \
    funcname, \
    helpstr \
  }; \
  int funcname \
  (struct cmd_element *self, struct vty *vty, int argc, char **argv)
```
#### install element
```
install_element (SYSCONFIG_NODE, &cmdname);
```
#### analysis
|no|keyword|content|
|--|--|--|
|0|who|Dramalife|
|1|宏定义DEFUN|编译预处理阶段|
|2|cmd_str & func|通过install_element连接|
|3|添加新命令|a.DEFUN处定义;b.install_element连接cmd_str与func|
|4||hacky--hack?? :-)|

### u-boot
#### __attribute__((unsused,section(".u_boot_cmd")))
[attribute](https://github.com/Dramalife/note/blob/master/GNU_C/__attribute__.md)
CMD的安装：存放在section里面然后对这个section进行遍历
#### analysis
|no|keyword|content|
|--|--|--|
|0|who|Dramalife|
|1|宏定义U_BOOT_CMD|编译预处理阶段|
|2|cmd_str & func|通过attribute,对section.u_boot_cmd遍历|
|3|添加新命令|a.U_BOOT_CMD处定义;|
|4||GNU C|
