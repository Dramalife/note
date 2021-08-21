# note "format" related file
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
# Init : Sun Aug  8 21:25:54 CST 2021
#  * ;
# Update : Sun Aug  8 21:25:54 CST 2021
#  
# Update
# 
# 

format: .format_c
.format_c:
	find -P . -name "*.h" | xargs clang-format -style="Chromium" -i
	find -P . -name "*.c" | xargs clang-format -style="Chromium" -i

