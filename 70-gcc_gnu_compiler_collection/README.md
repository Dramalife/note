> \# note "gcc" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.07.07 ;  
\# Update   
\#  


#### man gcc -- DESCRIPTION(part)
When you invoke GCC, it normally does preprocessing, compilation, assembly(汇编) and linking.  The "overall options" allow you to stop this process at an  
intermediate stage.  For example, the -c option says not to run the linker.  Then the output consists of object files output by the assembler.  

#### Stages
|Stage|Inputformat|Outputformat|
|--|--|--|
|preprocessing  |file.c|file.i|
|compilation    |file.i| |
|assembly(汇编) |file.s| |
|linking        |file.o|file.out|

#### Options(part)
|Option|Description|
|--|--|
|-E          |Preprocess only; do not compile, assemble or link|
|-S          |Compile only; do not assemble or link            |
|-c          |Compile and assemble, but do not link            |
|-o \<file\> |  Place the output into \<file\>                 |
|-v          |Display the programs invoked by the compiler     |
|-l library		 |Search the library named library when linking. |
|-llibrary		 |^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|
|**-I**dir		 |Add the directory dir to the list of directories to be searched for header files.(man 1 gcc) |
|**-L**dir		 |Add directory dir to the list of directories to be searched for -l.(man 1 gcc) |
| | |
| | |
|--sysroot=<directory>    |Use <directory> as the root directory for headers and libraries	|
|-print-search-dirs       |Display the directories in the compiler's search path		|

#### ERROR(s)

| | | |
|--|--|--|
| 1| gcc undefined reference -- placement of the "-l" option : [1.md](/70-gcc_gnu_compiler_collection/tips/gcc_placement_of_the_-l_option.md); [2.sample_code](/80-userspace_programming/00-libc_sample/man3_dlfcn_dlopen/elf-loader) | |
| | | |
| | | |
| | | |

