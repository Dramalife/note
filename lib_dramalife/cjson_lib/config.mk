######################################################START#####################
# Sample - config.mk (For Library & Demo)
# Update : 2020/10/14
######################################################START#####################
# Makefile Library
include $(PATH_ABS)/mk/multi_lib.mk

# Header Files` Path
CFLAGS+=-I$(PATH_ABS)

# Library Path for Demo (compile & runtime)
#CFLAGS_DEMO+=-ldramalife -L$(PATH_ABS) -Wl,-rpath=$(PATH_ABS)

# Library Code compile switch, for mode-lib only.
CFLAGS_DYNLIB+=-D_DL_CJSON_LIB_ENABLE_
CFLAGS_DEMO+=  -D_DL_CJSON_LIB_ENABLE_

# Demo Code compile switch, for mode-demo only.
# Command "make demo_of_dynlib" or "make compile-files-to-one" will enable this automatically.
#CFLAGS_DEMO+=_DRAMALIFE_LIB_HAS_FUNC_MAIN_

# Extra CFLAGS SWITCH
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1

# Debug Print Switch - TODO
CFLAGS_DEMO+=  -D_DLCJSON_DEBUG_ENABLED_
CFLAGS_DYNLIB+=-D_DLCJSON_DEBUG_ENABLED_

# Extra Source File
EXTRA_GIT_FOLDER666666:=cJSON

SOURCE_EXIST:=$(shell ls $(EXTRA_GIT_FOLDER666666))

.dllib_get_source:
ifeq ("$(SOURCE_EXIST)","")
	../exec_files/git_sparse_clone.sh cJSON https://gitee.com/Dramalife/tools_note.git
endif

.dllib_clean_source:
	echo "Clean $(EXTRA_GIT_FOLDER666666)..."
	-rm -rf $(EXTRA_GIT_FOLDER666666)
##########################################################END###################
