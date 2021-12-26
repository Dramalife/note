#class_define.cpp
#friend.cpp
#inheritance.cpp


# Constructor & Destructor -- Basic + Smart Pointer -- Normal Case
contor_destor:
	g++ -o constructor_destructor.out \
	constructor_destructor.cpp \
	-fsanitize=address -fno-omit-frame-pointer

# Constructor & Destructor -- Basic + Smart Pointer -- Mem Leak Case
contor_destor_smart_pointer_err:
	g++ -o constructor_destructor_smart_pointer_err.out \
	constructor_destructor.cpp \
	-DTEST_SMART_POINTER_ERR \
	-fsanitize=address -fno-omit-frame-pointer


clean_all:
	-mv ./*.out /tmp/

format:
	$(HOME)/note/lib_dramalife/exec_files/format_c_cpp.sh
