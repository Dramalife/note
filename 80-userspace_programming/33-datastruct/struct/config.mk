PATH_ABS:=../../../lib_dramalife/
#SRCS := $(wildcard $(CURRENT_DIR)*.c)
EXTERA_FILES2DEL:=./build/* ./obj/*
include $(PATH_ABS)mk/multi_files_mk/lib_split_make.mk
CFLAGS +="-D XXX=1"
