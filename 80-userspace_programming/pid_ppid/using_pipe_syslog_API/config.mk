PATH_ABS=../../../lib_dramalife/
DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1
#CFLAGS+=-Wall

## Add the directory dir to the list of directories to be searched for header files.(man 1 gcc)
CFLAGS+=-I$(PATH_ABS)/

## libc-pthread
##CFLAGS+=-lpthread

## Path to objs of library source
LIB_OBJ_PATH=$(PATH_ABS)/ipc_lib/build/obj/
## Link name of Path
LIB_OBJ_LINKNAME=obj2


# Using lib_dramalife by default
CFLAGS+=-D_THIS_PROG_USING_LIB_DRAMALIFE
