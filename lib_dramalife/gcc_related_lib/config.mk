PATH_ABS=../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
CFLAGS+="-I$(PATH_ABS)"
CFLAGS+="-D_DL_GCC_RELATED_SHOW_HAS_MAIN_"
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
#EXTERA_FILES2DEL:=$(CURRENT_DIR)/build