PATH_ABS=../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
CFLAGS+="-I$(PATH_ABS)"
CFLAGS+="-D_DL_GET_OPT_LIB_HAS_DEMO_"
DEF_MACROS +="-lpthread"
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
