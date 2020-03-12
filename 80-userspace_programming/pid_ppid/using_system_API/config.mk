PATH_ABS=../../../lib_dramalife/
include $(PATH_ABS)/mk/multi_lib.mk
CFLAGS+="-I$(PATH_ABS)"
#DEF_MACROS +="-lpthread"
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1

# For pid_ppid.c only, to clean files created when program running.
EXTERA_FILES2DEL=./1.log
