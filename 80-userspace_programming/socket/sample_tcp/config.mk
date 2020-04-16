include $(PATH_ABS)/mk/multi_lib.mk
# Flags used by all(dyblib & app/demo)
CFLAGS+="-I$(PATH_ABS)"
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
