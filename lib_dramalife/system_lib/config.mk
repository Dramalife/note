PATH_ABS=../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
CFLAGS+="-I$(PATH_ABS)"
CFLAGS+="-D_DL_LIB_SYSTEM_HAS_MAIN_=1"
CFLAGS+="-D_DL_LIB_SYSTEM_DEBUG_EN_=1"
#DEF_MACROS +="-lpthread"
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
#EXTERA_FILES2DEL:=$(CURRENT_DIR)/build