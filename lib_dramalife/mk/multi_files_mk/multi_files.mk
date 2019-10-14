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
# Init : FORK FROM "/lib_dramalife/mk/single_file_mk/sample_single_file.mk", 2019.10.14;
#

# TODO - USE : 
# STEP 0 : Change dir to path where your code is.
# STEP 1 : echo "PATH_ABS=RELATIVE/PATH/OF/NOTE-lib_dramalife/" > ./config.mk
# STEP 2 : ln -s path/to/libMakefile.mk ./Makefile
# STEP 3 : Enjoy your self :)

# Sample - config.mk
# PATH_ABS=../../../lib_dramalife/
# DEF_MACROS +="-D DL_NOTE_UNION_PART_BUILD=1"



CURRENT_DIR:=$(shell pwd)
CURRENT_DIR2:=$(shell pwd)/
PRE_SOURCE=source_pre$(PRE_COMP)

# Source Default - Current Directory.
#SRCS := $(wildcard $(CURRENT_DIR2)*.c)
SRCS := $(wildcard ./*.c)

# Flags that Explicitly or Implicitly used by makefile(s).
CFLAGS:=

# When you include "libMakefile_split.mk" in your "config.mk",
# "DEF_MACROS" will not work if running "make $(TARGET_SP)",
# "$(TARGET_SP)" are the TARGET(s) defined in "libMakefile_split.mk",
# BUT you can add your MACROS to "CFLAGS" as subsitute ;-(
DEF_MACROS:=

# Path of "libMakefile.mk"
PATH_ABS=../

# Folders in whitch files to be deleted.
EXTERA_FILES2DEL=$(CURRENT_DIR)/build

CC :=gcc
LD :=ld

include ./config.mk
include $(PATH_ABS)libMakefile.mk


# LD all to the target.
all:
	$(CC) -E $(SRCS) >> $(PRE_SOURCE)
	@echo "FLAGS : $(CFLAGS) ;"
	@echo "SRCS: \n$(SRCS)"
	$(CC) -o $(BIN_NAME)$(BIN_END) $(SRCS) $(CFLAGS) $(DEF_MACROS)

clean:
	@echo "$(CURRENT_DIR)"
	rm -rvf ./*$(BIN_END) ./*$(PRE_COMP) ./*$(BIN_O)
	rm -rvf $(EXTERA_FILES2DEL)

.PHONY: clean
