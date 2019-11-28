PATH_ABS:=../../../lib_dramalife/
EXTERA_FILES2DEL:=./build/*

include $(PATH_ABS)mk/multi_files_mk/lib_split_make_bh.mk

# Usage : make separately-complile-and-link
CFLAGS +="-D DL_NOTE_STRUCT_PART_BUILD=1"
