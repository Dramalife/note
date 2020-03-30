# note "makefile" related file
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
# ;
#
# $ make --version
# GNU Make 4.1
# Built for x86_64-pc-linux-gnu
# Copyright (C) 1988-2014 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# This is free software: you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Ref : https://github.com/21cnbao/training/makefile/mul-dir-exam/Makefile ;
#
# Init : 2019.10.15;
# Update : 2019.11.15, add some TARGETs, remove "(*.c) > a.out".
# Update :
#



SRC_DIR   :=$(CURRENT_DIR)/
BUILD_DIR :=$(SRC_DIR)build/
OBJ_DIR   :=$(BUILD_DIR)obj/

SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(SRCS:.c=.o)
BUILD := $(OBJS:.o=.out)


.SECONDARY: $(OBJS) $(BUILD)

$(OBJS) : %.o:%.c
	@echo "CFLAGS : $(CFLAGS)"
	$(CC) -c $< -o $@ $(CFLAGS) $(DEF_MACROS)

$(BUILD) : %.out:%.o
	$(CC) $< -o $@ $(CFLAGS) $(DEF_MACROS)
	

###############################################################################
#			*.c > *.o  ,  *.o > *.out			      #
###############################################################################
# Separately compile  "c source" to objects, and link objects separately;
separately-complile-and-link : $(BUILD)
	@echo "SRCS: \n$(SRCS)"
	@echo "OBJS: \n$(OBJS)"
	@echo "BUILD: \n$(BUILD)"
	@echo "PATH \nSRC_DIR: \n$(SRC_DIR) \nOBJ_DIR: \n$(OBJ_DIR) \nBUILD_DIR: \n$(BUILD_DIR) \n"
	-mkdir $(BUILD_DIR)
	-mkdir $(OBJ_DIR)
	mv -f $(BUILD) $(BUILD_DIR)
	mv -f $(OBJS) $(OBJ_DIR)
part-out : separately-complile-and-link
###############################################################################


###############################################################################
#				*.c > *.o				      #
###############################################################################
# Separately compile "c source" to objects;
separately-complile-to-objects : $(OBJS)
	@echo "SRCS: \n$(SRCS)"
	@echo "OBJS: \n$(OBJS)"
	@echo "PATH \nSRC_DIR: \n$(SRC_DIR) \nOBJ_DIR: \n$(OBJ_DIR) \nBUILD_DIR: \n$(BUILD_DIR) \n"
	-mkdir $(BUILD_DIR)
	-mkdir $(OBJ_DIR)
	mv -f $(OBJS) $(OBJ_DIR)
part-objs : separately-complile-to-objects
###############################################################################


###############################################################################
#				*.c > *.o					#
###############################################################################
# Used by note/lib_dramalife/makefile
BUILD_ROOT=/tmp
DYNLIB_OBJ_PATH=/tmp
.dynamic-lib : .pre-dynamic-lib $(OBJS)
	mv -f $(OBJS) $(DYNLIB_OBJ_PATH)
.pre-dynamic-lib:
	@echo "BUILD_ROOT : $(BUILD_ROOT)"
	@echo "DYNLIB_OBJ_PATH : $(DYNLIB_OBJ_PATH)"
	@echo "CFLAGS: $(CFLAGS)"
###############################################################################

