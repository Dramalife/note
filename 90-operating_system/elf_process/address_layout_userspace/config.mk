DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
PATH_ABS=../../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
CFLAGS+="-I$(PATH_ABS)"
#DEF_MACROS +="-lpthread"
