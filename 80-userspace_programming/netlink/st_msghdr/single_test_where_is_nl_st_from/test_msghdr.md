
[gcc -v]
[gcc-include](/80-userspace_programming/gcc/include.md)  



In source files(*.c),"#include" include files from clearly path such as "../xxx.h" ,  
specific path given by "gcc -I" and file system path "/usr/include", but will   
never include files that from source files of kernel.  
  
��Դ�ļ���* .c���У���#include������������ȷ·�����ļ������硰../xxx.h����  
��gcc -I���������ض�·�����ļ�ϵͳ·����/ usr / include����������Զ������  
�����ں�Դ�ļ����ļ���  


In socket.h of source of kernel, exist 2 files related to netlink,"struct user_msghdr"
and "struct msghdr". And in netlink.h,which was in file system, exist 1 file related to
netlink,"struct msghdr" same as "struct user_msghdr" in kernel.



