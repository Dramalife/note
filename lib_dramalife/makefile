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



# Configuration for subdir make
SUBDIRS=system_lib\
	ipc_lib\
	backtrace_lib\
	gcc_related_lib\
	option_config_lib

CFLAGS_ROOT="-fPIC -shared -I../"
DYNLIB_NAME:=lib_dramalife.so
DYNLIB_SLINK:=libdramalife.so


# Variables pass to subdir
BUILD_ROOT:=$(shell pwd)
DYNLIB_OBJ_PATH:="$(BUILD_ROOT)/.lib_dramalife_temp"


all: .prepare
	make $(SUBDIRS) TARGET=$@
	$(CC) -o $(DYNLIB_NAME) $(DYNLIB_OBJ_PATH)/*.o -fPIC -shared
	ln -sf $(DYNLIB_NAME) $(DYNLIB_SLINK)

$(SUBDIRS): .print
	make .process TEMP_OBJ_PATH=$@/build/object/$@.o TEMP_TARGET=$@
	@echo "----------------------TARGET $@ DONE----------------------"

.process:
	@echo "***********************.process***********************"
	make -C $(TEMP_TARGET) .dynamic-lib BUILD_ROOT=$(BUILD_ROOT) \
	DYNLIB_OBJ_PATH=$(DYNLIB_OBJ_PATH)
	CONFIG_MK_DIR=$(BUILD_ROOT)/$(TEMP_TARGET)
.print:
	@echo "***********************.print*************************"
.prepare:
	rm -rf ./.lib_dramalife_temp
	mkdir ./.lib_dramalife_temp

clean:
	-@rm -rvf $(DYNLIB_OBJ_PATH)
	-@rm -f $(DYNLIB_NAME)
	-@rm -f $(DYNLIB_SLINK)
