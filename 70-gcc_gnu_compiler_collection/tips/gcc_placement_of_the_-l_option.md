> \# note "gcc-option" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref Url : [jafon.tian](https://blog.csdn.net/JT_Notes/article/details/84346131)   
\#  
\# Sample code : [related_Sample_code](/80-userspace_programming/00-libc_sample/man3_dlfcn_dlopen/elf-loader)  
\#  
\# Init : 2019.08.29 ;  
\# Update   
\#  
  

### 1. man gcc

#### 1.1 man gcc -DESCRIPTION

For **the most** part, the order you use doesn't matter. ...

``` man
       You can mix options and other arguments.  For the most part, the order you use doesn't matter.  Order does matter when you use several options of
       the same kind; for example, if you specify -L more than once, the directories are searched in the order specified.  Also, the placement of the -l
       option is significant.
```


#### 1.2 man gcc -llibrary

It makes a difference **where** in the command you write this option;...

```man
       -llibrary
       -l library
           Search the library named library when linking.  (The second alternative with the library as a separate argument is only for POSIX compliance
           and is not recommended.)

>          It makes a difference where in the command you write this option; the linker searches and processes libraries and object files in the order
>          they are specified.  Thus, foo.o -lz bar.o searches library z after file foo.o but before bar.o.  If bar.o refers to functions in z, those
>          functions may not be loaded.

           The linker searches a standard list of directories for the library, which is actually a file named liblibrary.a.  The linker then uses this
           file as if it had been specified precisely by name.

           The directories searched include several standard system directories plus any that you specify with -L.

           Normally the files found this way are library files---archive files whose members are object files.  The linker handles an archive file by
           scanning through it for members which define symbols that have so far been referenced but not defined.  But if the file that is found is an
           ordinary object file, it is linked in the usual fashion.  The only difference between using an -l option and specifying a file name is that
           -l surrounds library with lib and .a and searches several directories.
```

