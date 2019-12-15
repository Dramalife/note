PATH_ABS=../../../../../lib_dramalife/
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1



#DEF_MACROS +="-D DL_NOTE_UNION_PART_BUILD=1"
CFLAGS+=-Wall
# Add the directory dir to the list of directories to be searched for header files.(man 1 gcc)
CFLAGS+=-I$(PATH_ABS)/
CFLAGS+=-I$(PATH_ABS)/option_config_lib/

# TODO - no effect in user code
##DEF_MACROS +=-D DL_OPT_DETECT_ERROR_LEVEL=3

# libc-pthread
#CFLAGS+=-lpthread
# Path to objs of library source
LIB_OBJ_PATH=$(PATH_ABS)/option_config_lib/build/obj/
# Link name of Path
LIB_OBJ_LINKNAME=obj2
