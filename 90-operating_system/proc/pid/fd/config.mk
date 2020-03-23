PATH_ABS=../../../../lib_dramalife/
#
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=0
CFLAGS+=-Wall
#
# Add the directory dir to the list of directories to be searched for header files.(man 1 gcc)
CFLAGS+=-I$(PATH_ABS)/
#
# libc-pthread
#CFLAGS+=-lpthread
#
# Path to objs of library source && Link name of Path
LIB_OBJ_PATH=$(PATH_ABS)/ipc_lib/build/obj/
LIB_OBJ_LINKNAME=obj2
