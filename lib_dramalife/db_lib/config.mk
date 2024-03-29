DLLIB_USE_CUSTOM_DEFAULT:=1
# Makefile Library
include $(PATH_ABS)/mk/multi_lib.mk

# Header Files` Path
CFLAGS+=-I$(PATH_ABS)

# Library Path for Demo (compile & runtime)
CFLAGS_DEMO+=-ldramalife -L$(PATH_ABS) -Wl,-rpath=$(PATH_ABS)

# Library Code compile switch, for mode-lib only.
CFLAGS_DYNLIB+=-D_DL_DB_LIB_ENABLE_

# Demo Code compile switch, for mode-demo only.
# Command "make demo_of_dynlib" will enable this automatically.
#CFLAGS_DEMO+=_DRAMALIFE_LIB_HAS_FUNC_MAIN_

# Extra CFLAGS SWITCH
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1

# Debug Print Switch - TODO
CFLAGS_DEMO+=-D_DLDB_DEBUG_ENABLED_
CFLAGS_DEMO+=-lpthread
CFLAGS_DEMO+=-ldl
#CFLAGS_DYNLIB+=-D_DLDB_DEBUG_ENABLED_


# Extra Source File
SOURCE_EXIST:=$(shell test -d note_sqlite3)
.dllib_get_source:
ifeq ("$(SOURCE_EXIST)","")
	git clone https://gitee.com/Dramalife/note_sqlite3.git --depth=1
endif
	ln -sf note_sqlite3/sqlite3.c .
	ln -sf note_sqlite3/sqlite3.h .
.dllib_clean_source:
	rm -rf note_sqlite3
	rm -rf sqlite3.c
	rm -rf sqlite3.h
