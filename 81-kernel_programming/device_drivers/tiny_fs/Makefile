# note "tinyfs" related makefile
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# $ make --version
# GNU Make 3.81
# Copyright (C) 2006  Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.
# There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.
# 
# This program built for i686-pc-linux-gnu
# 
#
# Init : 2019.09.06, COPY FROM https://github.com/brewHouses/tinyfs.git;
# Update :
#


obj-m := tinyfs.o

all :
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
    
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

