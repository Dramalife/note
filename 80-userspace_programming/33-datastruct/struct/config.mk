PATH_ABS:=../../../lib_dramalife/
#SRCS := $(wildcard $(CURRENT_DIR)*.c)
EXTERA_FILES2DEL:=./build/* ./obj/*
include $(PATH_ABS)libMakefile_split.mk
CFLAGS +="-D XXX=1"
