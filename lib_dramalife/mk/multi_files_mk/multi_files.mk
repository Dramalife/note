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
# STEP 1 : Configure(create and edit "config.mk", sample below);
# STEP 2 : ln -s path/to/libMakefile.mk ./Makefile
# STEP 3 : Enjoy your self :)

#
# See the "NOTE/lib_dramalife/mk/config_mk" folder for examples of config.mk
#

# Path where the Makefile is
CURRENT_DIR:=$(shell pwd)
CONFIG_MK_DIR:=$(CURRENT_DIR)
PRE_SOURCE=source_pre$(PRE_COMP)

# Source Default - Current Directory.
SRCS := $(wildcard ./*.c)

# Flags that Explicitly or Implicitly used by makefile(s).
# make -C PATH CFLAGS="..."
CFLAGS:=
CFLAGS_DEMO=
CFLAGS_DYNLIB=

# Don`t use FLAGS added in "NOTE/lib_dramalife/libMakefile.mk" if NOT NULL, null-USE, notnull-NOUSE;
# It may be changed in "*.mk".
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=

# When you include "libMakefile_split.mk" in your "config.mk",
# "DEF_MACROS" will not work if running "make $(TARGET_SP)",
# "$(TARGET_SP)" are the TARGET(s) defined in "libMakefile_split.mk",
# BUT you can add your MACROS to "CFLAGS" as subsitute ;-(
DEF_MACROS:=

# Path of "libMakefile.mk"
PATH_ABS=$(HOME)/note/lib_dramalife/

# Folders in whitch files to be deleted.
EXTERA_FILES2DEL=$(CURRENT_DIR)/build

CC :=gcc
LD :=ld


# Default target
default:
	@echo "Usage: \nmake [TARGET] ! \n"


include $(CONFIG_MK_DIR)/config.mk
# pub_lib.mk
include $(PATH_ABS)/libMakefile.mk
include $(PATH_ABS)/mk/vim.mk
include $(PATH_ABS)/mk/format.mk


# Backup && Clean
clean:
	@echo "$(CURRENT_DIR)"
	-cp -rvf ./*$(BIN_END)	/tmp
	-cp -rvf ./*$(PRE_COMP) /tmp
	-cp -rvf ./*$(BIN_O) 	/tmp
	rm -rvf ./*$(BIN_END) ./*$(PRE_COMP) ./*$(BIN_O)
	-cp -rvf $(EXTERA_FILES2DEL) /tmp
	rm -rvf $(EXTERA_FILES2DEL)


.PHONY: default clean
