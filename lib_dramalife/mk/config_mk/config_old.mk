######################################################START#####################
# TODO : OUTDATED !! Sample - config.mk (split make multi files)
######################################################START#####################
# Using default(multi_files.mk) if not set.
#PATH_ABS=../../../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
# Flags used by all(dyblib & app/demo)
CFLAGS+="-I$(PATH_ABS)"
# Flags used only by app/demo.
#CFLAGS_DEMO+=-ldramalife -L$(PATH_ABS) -Wl,-rpath=$(PATH_ABS)
#DEF_MACROS +="-lpthread"
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=0
#EXTERA_FILES2DEL:=$(CURRENT_DIR)/build
##########################################################END###################
