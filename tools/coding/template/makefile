all :
	make -C ../../../lib_dramalife/ipc_lib/ clean
	make -C ../../../lib_dramalife/ipc_lib/ separately-complile-to-objects
	gcc template_for_c.c -I ~/note/lib_dramalife/ ~/note/lib_dramalife/ipc_lib/build/obj/ipc_lib_pipe.o
