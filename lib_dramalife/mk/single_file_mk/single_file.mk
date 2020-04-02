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
# GNU Make 4.1
# Built for arm-unknown-linux-gnueabihf
# Copyright (C) 1988-2014 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# This is free software: you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
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
# Update : 2019.09.06, "symbol_libk + config.mk" mode;  
#
# Update : 2019.10.14, RENAMED FROM "sample_single_file.mk";
#
# Update : 2019.11.13, 	Add target "all-with-lib-objs";
#			Rename "make all" and "make clean" to 
#				"make all-normal" and "make clean-all-normal";
#

# TODO - USE : 
# STEP 0 : Change dir to path where your code is.
# STEP 1 : Create configuration file named "config.mk", reference sample below ;-)
# STEP 2 : ln -s path/to/libMakefile.mk ./Makefile
# STEP 3 : Enjoy your self :)

################################################################
# Sample - config.mk(Single/multi file >> a.out)	       #
################################################################
#PATH_ABS=../../../lib_dramalife/
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=0
#CFLAGS+=-Wall
################################################################

################################################################
# Sample - config.mk(Single/multi file and lib-objs >> a.out)  #
################################################################
#PATH_ABS=../../../lib_dramalife/
##
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=0
#CFLAGS+=-Wall
##
## Add the directory dir to the list of directories to be searched for header files.(man 1 gcc)
#CFLAGS+=-I$(PATH_ABS)/
##
## libc-pthread
##CFLAGS+=-lpthread
##
## Path to objs of library source && Link name of Path
#LIB_OBJ_PATH=$(PATH_ABS)/libc_with_print_lib/build/obj/
#LIB_OBJ_LINKNAME=obj2
################################################################

CURRENT_DIR:=$(shell pwd)
CONFIG_MK_DIR:=$(CURRENT_DIR)
PRE_SOURCE=source_pre$(PRE_COMP)

# Source Default - Current Directory.
SRCS := $(wildcard ./*.c)

# Flags that Explicitly or Implicitly used by makefile(s).
CFLAGS:=

# Don`t use FLAGS added in "NOTE/lib_dramalife/libMakefile.mk" if NOT NULL, null-USE, notnull-NOUSE;
# It may be changed in "*.mk".
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=

CC :=gcc
LD :=ld

# When you include "libMakefile_split.mk" in your "config.mk",
# "DEF_MACROS" will not work if running "make $(TARGET_SP)",
# "$(TARGET_SP)" are the TARGET(s) defined in "libMakefile_split.mk",
# BUT you can add your MACROS to "CFLAGS" as subsitute ;-(
DEF_MACROS:=

# Path of "libMakefile.mk"
PATH_ABS=../

# Path of library objs
LIB_OBJ_PATH:=
# Name of symbollink linking to LIB_OBJ_PATH
LIB_OBJ_LINKNAME:=obj2

# Folders in whitch files to be deleted.
EXTERA_FILES2DEL=$(CURRENT_DIR)/build

include $(CONFIG_MK_DIR)/config.mk
include $(PATH_ABS)libMakefile.mk

##################[Defaults]####################
# Default target
warning-this-makefile:
	@echo "\nUSAGE: make (clean-)all-TARGET !!!"
	@echo "make all-normal:"		" normally make;"
	@echo "make all-with-lib-objs:"	" link with other objs;"
# TODO : Hide "all" and "clean" when type TAB after "make";
.SECONDARY+=all
#all:	warning-this-makefile
all-:	warning-this-makefile
#clean:	warning-this-makefile
clean-:	warning-this-makefile
################################################

###############[all-with-lib-objs]###############
SRC_DIR   :=$(CURRENT_DIR)/
BUILD_DIR :=$(SRC_DIR)build/
OBJ_DIR   :=$(BUILD_DIR)obj/

SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(SRCS:.c=.o)

.SECONDARY+= $(OBJS) $(BUILD)

$(OBJS) : %.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEF_MACROS)

# [TARGET] : Linking with other objs
all-with-lib-objs:$(OBJS)
	-mkdir $(BUILD_DIR)
	-mkdir $(OBJ_DIR)
	mv -f $(OBJS) $(OBJ_DIR)
	@echo "\nLIB_LINK: \n$(LIB_OBJ_LINKNAME) \nBUILD_DIR: \n$(BUILD_DIR)"
	-ln -sfv $(SRC_DIR)/$(LIB_OBJ_PATH) $(BUILD_DIR)/$(LIB_OBJ_LINKNAME)
	$(CC) -o $(BUILD_DIR)$(BIN_NAME)$(BIN_DNAME)  $(BUILD_DIR)$(LIB_OBJ_LINKNAME)/*.o  $(OBJ_DIR)/*.o  $(CFLAGS)  $(DEF_MACROS)
clean-all-with-lib-objs:
	rm -f $(BUILD_DIR)$(LIB_OBJ_LINKNAME)
	rm -f $(BUILD_DIR)$(BIN_NAME)$(BIN_DNAME)
	rm -rf $(OBJ_DIR)/*
	rm -rvf ./*$(BIN_DNAME) ./*$(PRE_COMP) ./*$(BIN_O)
	-rmdir $(OBJ_DIR)
	-rmdir $(BUILD_DIR)
################################################

###################[normal]#####################
# [TARGET] LD all to the target.
all-normal:
	$(CC) -E $(SRCS) >> $(PRE_SOURCE) $(CFLAGS)
	@echo "FLAGS : $(CFLAGS) ;"
	@echo "SRCS: \n$(SRCS)"
	$(CC) -o $(BIN_NAME)$(BIN_DNAME) $(SRCS) $(CFLAGS) $(DEF_MACROS)

clean-all-normal:
	@echo "$(CURRENT_DIR)"
	rm -rvf ./*$(BIN_DNAME) ./*$(PRE_COMP) ./*$(BIN_O)
	rm -rvf $(EXTERA_FILES2DEL)

all-normal-create-obj: clean-all-normal-create-obj  $(OBJS)
	@echo "BUILDING..."
	$(CC) -E $(SRCS) >> $(PRE_SOURCE)
	@echo "FLAGS : $(CFLAGS) ;"
	@echo "SRCS: \n$(SRCS)"
	$(CC) -o $(BIN_NAME)$(BIN_DNAME) $(OBJS) $(CFLAGS) $(DEF_MACROS)

clean-all-normal-create-obj:
	@echo "CLEANING..."
	rm -rvf ./*$(BIN_DNAME) ./*$(PRE_COMP) ./*$(BIN_O)
	rm -rvf $(EXTERA_FILES2DEL)
################################################

.PHONY: warning-this-makefile
#.PHONY: all
.PHONY: all-
#.PHONY: clean
.PHONY: clean-
.PHONY: clean-all-normal
.PHONY: clean-all-with-lib-objs
