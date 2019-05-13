# man gcc

## --sysroot=dir  
Use dir as the logical root directory for headers and libraries.  For example, if the compiler normally searches for headers in /usr/include and libraries in  
/usr/lib, it instead searches dir/usr/include and dir/usr/lib.  
  
If you use both this option and the -isysroot option, then the --sysroot option applies to libraries, but the -isysroot option applies to header files.  
  
The GNU linker (beginning with version 2.16) has the necessary support for this option.  If your linker does not support this option, the header file aspect of  
--sysroot still works, but the library aspect does not.  
  
ʹ��dir��Ϊ��ͷ�Ϳ���߼���Ŀ¼�� ���磬���������ͨ����/ usr / include��/ usr / lib�еĿ�������ͷ�ļ����������dir / usr / include��dir / usr / lib��  
���ͬʱʹ�ô�ѡ���-isysrootѡ���--sysrootѡ�������ڿ⣬��-isysrootѡ��������ͷ�ļ���  
GNU���������Ӱ汾2.16��ʼ���Դ�ѡ����б�Ҫ��֧�֡� �����������֧�ִ�ѡ���--sysroot��ͷ�ļ�������Ȼ��Ч�����ⷽ�治�С�  
  
