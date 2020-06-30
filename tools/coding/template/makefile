all_with_so:
	make -C ../../../lib_dramalife
	gcc template_for_c.c \
	-I ~/note/lib_dramalife/ \
	-ldramalife \
	-L ~/note/lib_dramalife/ \
	-Wl,-rpath=/home/dramalife/note/lib_dramalife


all :
	make -C ../../../lib_dramalife/ipc_lib/ clean
	make -C ../../../lib_dramalife/ipc_lib/ separately-complile-to-objects
	gcc template_for_c.c -I ~/note/lib_dramalife/ ~/note/lib_dramalife/ipc_lib/build/obj/ipc_lib_pipe.o
