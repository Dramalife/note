# man gcc

## --sysroot=dir  
Use dir as the logical root directory for headers and libraries.  For example, if the compiler normally searches for headers in /usr/include and libraries in  
/usr/lib, it instead searches dir/usr/include and dir/usr/lib.  
  
If you use both this option and the -isysroot option, then the --sysroot option applies to libraries, but the -isysroot option applies to header files.  
  
The GNU linker (beginning with version 2.16) has the necessary support for this option.  If your linker does not support this option, the header file aspect of  
--sysroot still works, but the library aspect does not.  
  
使用dir作为标头和库的逻辑根目录。 例如，如果编译器通常在/ usr / include和/ usr / lib中的库中搜索头文件，则会搜索dir / usr / include和dir / usr / lib。  
如果同时使用此选项和-isysroot选项，则--sysroot选项适用于库，但-isysroot选项适用于头文件。  
GNU链接器（从版本2.16开始）对此选项具有必要的支持。 如果链接器不支持此选项，则--sysroot的头文件方面仍然有效，但库方面不行。  
  
