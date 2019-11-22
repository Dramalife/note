PATH_ABS=../../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
CFLAGS+="-I$(PATH_ABS)"
#DEF_MACROS +="-lpthread"
