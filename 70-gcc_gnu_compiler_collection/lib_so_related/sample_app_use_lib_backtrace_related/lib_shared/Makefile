#
# note "gcc shared library" related file
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
# Init : 2019.08.23, include,;
# Update :
#
#
#	gcc -shared $(SRC) -o lib$(LIBNAME_DL).so
#

include ../../../../lib_dramalife/libMakefile.mk

SRC=$(wildcard ./*.c)

LIBNAME_DL=backtrace_funcs

all:
	gcc -c $(SRC) 
	gcc ./*$(BIN_O) -shared -o lib$(LIBNAME_DL)$(SHD_LIB)


clean:
	rm -rvf ./*$(SHD_LIB) ./*$(BIN_O)
.PHONY: clean
