#
# note make related "makefile"
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
#
# update : 2019.05.13
# update : 2019.05.20 add gcc -v
# update : 2019.07.08 Add warning info, close autorun after compilation;
#			Comment out var of lib "LIB_C_DRAMALIFE" that 
#			can be installed by running 
#			"note/lib_dramalife/install_sh_h_to_root_dir.sh";
#

BIN_NAME=a_demo
BIN_END=.out
PRE_COMP=source.i
SRC=$(wildcard ./*.c)

all:
	rm -rvf ./*$(BIN_END)
	gcc -E $(SRC) >> $(PRE_COMP)
	gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -v

# "make: *** [all] Error 1" 
#./$(BIN_NAME)$(BIN_END)

clean:
	rm -rvf ./*$(BIN_END) ./$(PRE_COMP)

