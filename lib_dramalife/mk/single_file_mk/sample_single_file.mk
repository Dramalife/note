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
# Update : 2019.09.06, "symbol_libk + config.mk" mode;  
#

# TODO - USE : 
# STEP 0 : Change dir to path where your code is.
# STEP 1 : echo "PATH_ABS=RELATIVE/PATH/OF/NOTE-lib_dramalife/" > ./config.mk
# STEP 2 : ln -s path/to/libMakefile.mk ./Makefile
# STEP 3 : Enjoy your self :)

# Sample - config.mk
# PATH_ABS=../../../lib_dramalife/
# DEF_MACROS +="-D DL_NOTE_UNION_PART_BUILD=1"


CFLAGS:=
PATH_ABS=../
DEF_MACROS:=

#SRC_DIR :=./src
#BUILD_DIR :=./build
#OBJ_DIR :=$(BUILD_DIR)/obj
SRC_DIR :=.
BUILD_DIR :=.
OBJ_DIR :=.

CC :=gcc
LD :=ld

include ./config.mk
include $(PATH_ABS)libMakefile.mk

PRE_SOURCE=source_pre$(PRE_COMP)
SRCS := $(wildcard ./*.c)
OBJS := $(SRCS:./%.c=./%.o)
BUILD := $(OBJS:./%.o=./%)
#SRCS := $(wildcard $(SRC_DIR)/*.c)
#OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#BUILD := $(OBJS:$(OBJ_DIR)/%.o=$(BUILD_DIR)/%.out)
.SECONDARY: $(OBJS)

# LD all to the target.
all:
	rm -rvf ./*$(BIN_END)
	gcc -E $(SRCS) >> $(PRE_SOURCE)
	@echo "FLAGS : $(CFLAGS) ;"
	gcc -o $(BIN_NAME)$(BIN_END) $(SRCS) $(CFLAGS) $(DEF_MACROS)

# Ref : https://blog.csdn.net/jinhangdev/article/details/80581408
all-part: $(BUILD)
	@$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo + $(CC) $<
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@$(BUILD_DIR)/%: $(OBJ_DIR)/%.o
	@echo + $(LD) $@
	@mkdir -p $(BUILD_DIR)
	@$(LD) -o $@ $<

.PHONY: all-part clean

clean:
	rm -rvf ./*$(BIN_END) ./*$(PRE_COMP) ./*$(BIN_O)

