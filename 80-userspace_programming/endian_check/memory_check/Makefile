# note "endian" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
#
# Init : 2019.09 19 ;
# Update :
#

# Description
# Simple Makefile;

SOURCE1=endian_char_array
OUT1=char
SOURCE2=endian_int_byte
OUT2=int

CC := gcc

all:
	$(CC) -o $(OUT1).out $(SOURCE1).c
	$(CC) -o $(OUT2).out $(SOURCE2).c
ass:
	objdump -dx $(OUT1).out > $(OUT1).ass
	objdump -dx $(OUT2).out > $(OUT2).ass

clean :
	rm -rvf ./*.o ./*.out ./*.ass
.PHONY: clean


