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

Linux chattr�������ڸı��ļ����ԡ�
Linux lsattr����������ʾ�ļ����ԡ�


### 2. Attributes

|OPT|CH|EN|
|--|--|--|
|a|���ļ���Ŀ¼����������;��		 | |
|b|�������ļ���Ŀ¼������ȡʱ�䡣      | |
|c|���ļ���Ŀ¼ѹ�����š�              | |
|d|���ļ���Ŀ¼�ų����㵹����֮�⡣      | |
|**i\***|������������ļ���Ŀ¼��          | |
|s|������ɾ���ļ���Ŀ¼��                | |
|S|��ʱ�����ļ���Ŀ¼��                  | |
|u|Ԥ������ɾ����			 | |


### 3. Sample

####  chattr +i

```bash
dramalife@ubuntu:~/note $ lsattr tools/fs/file_attribute.txt 
-------------e-- tools/fs/file_attribute.txt

dramalife@ubuntu:~/note $ sudo chattr +i tools/fs/file_attribute.txt
dramalife@ubuntu:~/note $ lsattr tools/fs/file_attribute.txt 
----i--------e-- tools/fs/file_attribute.txt

dramalife@ubuntu:~/note $ rm -f tools/fs/file_attribute.txt 
rm: cannot remove ��tools/fs/file_attribute.txt��: Operation not permitted

dramalife@ubuntu:~/note $ sudo rm -f tools/fs/file_attribute.txt 
rm: cannot remove ��tools/fs/file_attribute.txt��: Operation not permitted
```

