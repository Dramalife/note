> \# note "makefile-lib-doc" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Sample code : https://github.com/dramalife/note.git//80-userspace_programming/33-datastruct/struct;  
\#		commit:[4b0f238e6b7763ed1f42faa1e59f3715e2018bd4]  
\#  
\# Init : 2019.10.15;  
\# Update   
\#  
  


#### 1. make all (DL_NOTE_STRUCT_PART_BUILD=0)

```bash
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ make all >/dev/null
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ ./a_demo.out 
1,7,15
0,3,15
title : Language C
author: RUNOOB
subject: Programming
book_id: 123456
[main_structs_include_each_other,77] TODO 

```


#### 2. Change Flags

```bash
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ vi config.mk 
```

```diff
- CFLAGS +="-D DL_NOTE_STRUCT_PART_BUILD=0"
+ CFLAGS +="-D DL_NOTE_STRUCT_PART_BUILD=1"
```


### 3. make part-rename1015 (DL_NOTE_STRUCT_PART_BUILD=1)

```bash
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ make part-rename1015 >/dev/null
mkdir: cannot create directory ‘/home/dramalife/note/80-userspace_programming/33-datastruct/struct/build/’: File exists
make: [part-rename1015] Error 1 (ignored)
mkdir: cannot create directory ‘/home/dramalife/note/80-userspace_programming/33-datastruct/struct/build/obj/’: File exists
make: [part-rename1015] Error 1 (ignored)
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ ./build/
bit_fields.out                  init_var.out                    obj/                            struct.out                      structs_include_each_other.out
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ ./build/bit_fields.out 
1,7,15
0,3,15
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ ./build/init_var.out 
title : Language C
author: RUNOOB
subject: Programming
book_id: 123456
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ ./build/struct.out 
dramalife@server:~/note/80-userspace_programming/33-datastruct/struct $ ./build/structs_include_each_other.out 
[main,77] TODO 

```
