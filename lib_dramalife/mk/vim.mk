# note "vim - ctags & cscope" related file
# Copyright (C) 2019 Dramalife <dramalife@live.com>
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# 
# $ gcc --version
# gcc (Debian 8.3.0-6) 8.3.0
# Copyright (C) 2018 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# 
# ;
# 
# $ uname -a
# Linux bananapir2 4.19.189-mt7623 #21.05.1 SMP Thu May 6 20:37:31 UTC 2021 armv7l GNU/Linux
# ;
# 
# Init : Sun Aug  8 21:02:52 CST 2021
#  * ;
# Update : Sun Aug  8 21:02:52 CST 2021
#  
# Update
# 
# 


vim: .ctags .cscope
.ctags:
	ctags -R
.clean_tags:
	-rm tags
.cscope:
	find . -name "*.h" > cscope.files
	find . -name "*.c" >> cscope.files
	cscope -bkq -i ./cscope.files
.clean_cscope:
	-rm -rf ./cscope*
clean_vim: .clean_tags .clean_cscope

