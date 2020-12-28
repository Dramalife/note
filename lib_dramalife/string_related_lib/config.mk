######################################################START#####################
# Sample - config.mk (For Library & Demo)
# Update : 2020/10/14
# Update : 2020/10/15
# Update : 2020/10/20, Add config "DLLIB_USE_CUSTOM_DEFAULT"
################################################################################
# Header Files` Path
CFLAGS+=-I$(PATH_ABS)

# Library Path for Demo (compile & runtime)
#CFLAGS_DEMO+=-ldramalife -L$(PATH_ABS) -Wl,-rpath=$(PATH_ABS)

# Library Code compile switch, for mode-lib only.
CFLAGS_DYNLIB+=-D_DL_STRING_RELATED_LIB_LIB_ENABLE_
CFLAGS_DEMO+=  -D_DL_STRING_RELATED_LIB_LIB_ENABLE_

# Demo Code compile switch, for mode-demo only.
# Command "make demo_of_dynlib" or "make compile-files-to-one" will enable this automatically.
#CFLAGS_DEMO+=_DRAMALIFE_LIB_HAS_FUNC_MAIN_

# Extra CFLAGS SWITCH
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1

# Debug Print Switch - TODO
CFLAGS_DEMO+=  -D_DL_STRING_RELATED_LIB_DEBUG_ENABLED_
CFLAGS_DYNLIB+=-D_DL_STRING_RELATED_LIB_DEBUG_ENABLED_

#	# Extra Source File
#	EXTRA_GIT_FOLDERSTRING_RELATED_LIB:=note_sqlite3
#	
#	# TODO : "test" echo none !
#	#SOURCE_EXIST:=$(shell test -d $(EXTRA_GIT_FOLDERSTRING_RELATED_LIB))
#	SOURCE_EXIST:=$(shell ls $(EXTRA_GIT_FOLDERSTRING_RELATED_LIB))
#	
#	.dllib_get_source:
#	ifeq ("$(SOURCE_EXIST)","")
#		#git clone https://gitee.com/Dramalife/note_sqlite3.git --depth=1
#	endif
#		#ln -sf note_sqlite3/sqlite3.c .
#	
#	.dllib_clean_source:
#		#rm -rf $(EXTRA_GIT_FOLDERSTRING_RELATED_LIB)
#		#rm -rf sqlite3.c

# The "make demo_..." will call "make .dllib_demo_default" if DLLIB_USE_CUSTOM_DEFAULT is set to 1
#DLLIB_USE_CUSTOM_DEFAULT:=1
#.dllib_demo_default:
#	make -C . .compile-files-to-one

# Makefile Library
include $(PATH_ABS)/mk/multi_lib.mk
##########################################################END###################

