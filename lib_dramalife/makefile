###############################################################################
# https://github.com/dramalife/note.git
# Dramalife@live.com
#
# For lib_dramalife
#
# Init : 2020.03.29
#	not finished!
# Update : 2020.03.30
#	make dynlib success!
#
###############################################################################



#####
# Configuration for subdir make
#
SUBDIRS:=
SUBDIRS+=system_lib
SUBDIRS+=ipc_lib
SUBDIRS+=backtrace_lib
SUBDIRS+=gcc_related_lib
SUBDIRS+=option_config_lib
# SQLite3
SUBDIRS+=db_lib
SUBDIRS+=terminal_lib
SUBDIRS+=inet_lib



CFLAGS_ROOT="-fPIC -shared -I../"
DYNLIB_NAME:=lib_dramalife.so
DYNLIB_SLINK:=libdramalife.so


# Variables pass to subdir
BUILD_ROOT:=$(shell pwd)
DYNLIB_OBJ_PATH:="$(BUILD_ROOT)/.lib_dramalife_temp"

ACTION=make

all: download
	make action ACTION=make

action: .prepare
	make $(SUBDIRS) TARGET=$@ ACTION=$(ACTION)
ifeq ($(ACTION),make)
	$(CC) -o $(DYNLIB_NAME) $(DYNLIB_OBJ_PATH)/*.o -fPIC -shared -lpthread -ldl
	ln -sf $(DYNLIB_NAME) $(DYNLIB_SLINK)
endif

$(SUBDIRS): .print
	make .process TEMP_OBJ_PATH=$@/build/object/$@.o TEMP_TARGET=$@ \
	ACTION=$(ACTION)
	@echo "----------------------TARGET $@ DONE----------------------"

.process:
	@echo "***********************.process***********************"
ifeq ($(ACTION),make)
	make -C $(TEMP_TARGET) .dynamic-lib BUILD_ROOT=$(BUILD_ROOT) \
	DYNLIB_OBJ_PATH=$(DYNLIB_OBJ_PATH)
	CONFIG_MK_DIR=$(BUILD_ROOT)/$(TEMP_TARGET)
endif
ifeq ($(ACTION),clean)
	-make -C $(TEMP_TARGET) .dllib_clean_source BUILD_ROOT=$(BUILD_ROOT) \
	DYNLIB_OBJ_PATH=$(DYNLIB_OBJ_PATH)
	CONFIG_MK_DIR=$(BUILD_ROOT)/$(TEMP_TARGET)
endif
ifeq ($(ACTION),source)
	-make -C $(TEMP_TARGET) .dynamic-lib-download BUILD_ROOT=$(BUILD_ROOT) \
	DYNLIB_OBJ_PATH=$(DYNLIB_OBJ_PATH)
	CONFIG_MK_DIR=$(BUILD_ROOT)/$(TEMP_TARGET)
endif
.print:
	@echo "***********************.print*************************"
.prepare:
	rm -rf ./.lib_dramalife_temp
	mkdir ./.lib_dramalife_temp

download:
	make action ACTION=source

clean:
	-@rm -rvf $(DYNLIB_OBJ_PATH)
	-@rm -f $(DYNLIB_NAME)
	-@rm -f $(DYNLIB_SLINK)
	make action ACTION=clean

