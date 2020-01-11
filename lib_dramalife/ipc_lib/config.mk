PATH_ABS=../../lib_dramalife/
include $(PATH_ABS)/mk/multi_files_mk/lib_split_make.mk
CFLAGS+=-I..
CFLAGS+=-DDRAMALIFE_NOTE_IPC_LIB_PIPE_C_DEBUG_SW=1
