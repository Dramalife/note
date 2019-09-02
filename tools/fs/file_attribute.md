> \# note "file-attribute" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref Url : https://www.runoob.com/linux/linux-comm-lsattr.html  
\#  
\# Init : 2019.09.02;  
\# Update   
\#  
  

### 1. Backgrounds

Linux chattr命令用于改变文件属性。
Linux lsattr命令用于显示文件属性。


### 2. Attributes

|OPT|CH|EN|
|--|--|--|
|a|让文件或目录仅供附加用途。		 | |
|b|不更新文件或目录的最后存取时间。      | |
|c|将文件或目录压缩后存放。              | |
|d|将文件或目录排除在倾倒操作之外。      | |
|**i\***|不得任意更动文件或目录。          | |
|s|保密性删除文件或目录。                | |
|S|即时更新文件或目录。                  | |
|u|预防意外删除。			 | |


### 3. Sample

####  chattr +i

```bash
dramalife@ubuntu:~/note $ lsattr tools/fs/file_attribute.txt 
-------------e-- tools/fs/file_attribute.txt

dramalife@ubuntu:~/note $ sudo chattr +i tools/fs/file_attribute.txt
dramalife@ubuntu:~/note $ lsattr tools/fs/file_attribute.txt 
----i--------e-- tools/fs/file_attribute.txt

dramalife@ubuntu:~/note $ rm -f tools/fs/file_attribute.txt 
rm: cannot remove ‘tools/fs/file_attribute.txt’: Operation not permitted

dramalife@ubuntu:~/note $ sudo rm -f tools/fs/file_attribute.txt 
rm: cannot remove ‘tools/fs/file_attribute.txt’: Operation not permitted
```

