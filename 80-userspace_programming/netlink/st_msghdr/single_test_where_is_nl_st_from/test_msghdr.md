
[gcc -v]
[gcc-include](/80-userspace_programming/gcc/include.md)  



In source files(*.c),"#include" include files from clearly path such as "../xxx.h" ,  
specific path given by "gcc -I" and file system path "/usr/include", but will   
never include files that from source files of kernel.  
  
在源文件（* .c）中，“#include”包括来自明确路径的文件，例如“../xxx.h”，  
“gcc -I”给出的特定路径和文件系统路径“/ usr / include”，但是永远不包含  
来自内核源文件的文件。  


In socket.h of source of kernel, exist 2 files related to netlink,"struct user_msghdr"
and "struct msghdr". And in netlink.h,which was in file system, exist 1 file related to
netlink,"struct msghdr" same as "struct user_msghdr" in kernel.



