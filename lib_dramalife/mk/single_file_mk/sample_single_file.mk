#
# note "make" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# $ make --version
# TODO;
#
# update : 2019.05.13
# update : 2019.05.20 add gcc -v
# update : 2019.07.08 Add warning info, close autorun after compilation;
#			Comment out var of lib "LIB_C_DRAMALIFE" that 
#			can be installed by running 
#			"note/lib_dramalife/install_sh_h_to_root_dir.sh";
# update : 2019.07.11 Del '-I' option;
# update : 2019.08.23 Add "make --version";
#			Use lib "libMakefile.mk" ;
#
# Init : COPY FROM "sample_single_file.mk", DATE : TODO;
# Update 
#

# TODO : Update "PATH_ABS";
PATH_ABS=../
include $(PATH_ABS)/libMakefile.mk

PRE_SOURCE=source_pre$(PRE_COMP)
SRC=$(wildcard ./*.c)

all:
	rm -rvf ./*$(BIN_END)
	gcc -E $(SRC) >> $(PRE_SOURCE)
	gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -v -g


clean:
	rm -rvf ./*$(BIN_END) ./*$(PRE_COMP) ./*$(BIN_O)

.PHONY: clean
