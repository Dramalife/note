PATH_ABS=../../../../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
CFLAGS+="-I$(PATH_ABS)"
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
#DEF_MACROS +="-lpthread"
