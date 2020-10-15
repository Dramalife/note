# 
#  [note](github.com/dramalife/note.git)
#  Dramalife@live.com
#  Init : 2020.03.04
# Update : 2020.03.17
#	Add target - test_old_app__new_dynlib.
#	Update all targets - Using variables.
# Update : 2020.03.20
#	Version of dynlib !
#	Change target name : test_old_app__new_dynlib -> test2_old_app__new_dynlib 
#	Add target - test3_found_wrong_dynlib
# Update : 2020.10.15
#	Change terminal color lib to "lib_dramalife.sh - dlterm_5002.sh";
# 


#include ../../../lib_dramalife/print_lib/dramalife_terminal_color.sh
include ../../../lib_dramalife/terminal_lib/dlterm_5002.sh

###########################################
APP_NAME:=app.out
LIBXXX:=libxxx.so
LIBYYY:=libyyy.so
LIBYYY_VERSION:=libyyy.so.1.0.0


###########################################
CFLAG_NOVAR:=-U_LIB_USE_VAR_DEFINED_BY_APP
CFLAG_VAR:=-D_LIB_USE_VAR_DEFINED_BY_APP


###########################################
LDFLAG:=		-Wl,-rpath=.

# Link option "--as-needed"
LDFLAG_ASNEEDED:=	-Wl,-rpath=. -Wl,--as-needed


###########################################
LIBFLAGS:=
LIBFLAGS_U:=-lrt -Xlinker --unresolved-symbols=report-all


###########################################
LIBS:=			-lxxx -lrt

# The wrong order of option of linker was used when compiling the app.
# (NOTE:The dynlib used at this time did not specify the "-lrt" option at compile time)
LIBS_ORDERr:=		-lrt -lxxx

# The "-lrt" option was not specified when compiling the app.
# (NOTE:The dynlib used at this time did not specify the "-lrt" option at compile time)
LIBS_NOLRT:=		-lxxx



###########################################
# Normal compile
###########################################
all : dynlib_ok app_ok
app_ok:
	@echo "Making $(APP_NAME) ..."
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG)		$(LIBS)		$(CFLAG_NOVAR)
dynlib_ok:
	@echo "Making $(LIBXXX) ..."
	gcc -o $(LIBXXX) libxxx.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_NOVAR)
dynlib_report_unresolved_symbols:
	@echo "Making $(LIBXXX) ... :: LIBFLAGS_U"
	gcc -o $(LIBXXX) libxxx.c -fPIC -shared		$(LIBFLAGS_U)	$(CFLAG_VAR) 

clean:
	@echo "Clean all"
	rm -rvf ./*.out ./*.so ./*.so.*
	rm -rvf /tmp/libyyy.so


###########################################
# Err1 : [compile]./libxxx.so: undefined reference to `shm_open'
###########################################
# 1.1 Target - no "-lrt"
app_compile_err_lrt:
	@echo "Testing - lrt"
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG)		$(LIBS_NOLRT)	$(CFLAG_NOVAR)
# 1.2 Target - add "-Wl,--as-needed"
app_compile_err_asneeded:
	@echo "Testing - as-needed"
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG_ASNEEDED)	$(LIBS_NOLRT)	$(CFLAG_NOVAR)
# 1.3 Target - order of dynlib_ok
app_compile_err_order_dynlib:
	@echo "Testing - lib oredr"
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG)		$(LIBS_ORDERr)	$(CFLAG_NOVAR)


###########################################
# Err2 : [runtime]/$(APP_NAME): symbol lookup error: ./libxxx.so: undefined symbol: var_a
###########################################
# 2.1
test2_old_app__new_dynlib : dynlib_ok   app_ok   .test2_compile_new_dynlib
	@echo "Run app manually !"
# OBJS
test2_compile_new_app:
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG)		$(LIBS)		$(CFLAG_VAR)
.test2_compile_new_dynlib:
	@echo "Testing - new $(LIBXXX)"
	gcc -o $(LIBXXX) libxxx.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_VAR)


###########################################
# Err3 : [compile]./libxxx.so: undefined reference to `func_in_libyyy'
###########################################
test3_found_wrong_dynlib: .test3_print_info  .test3_compile_dynlibs_all  .test3_compile_app  
.test3_print_info:
	@echo $(DLTERM_YELLOW)"NOTE:"$(DLTERM_NONE)		
	@echo $(DLTERM_YELLOW)"********************"$(DLTERM_NONE)	
	@echo $(DLTERM_LGREEN)"$(APP_NAME)"$(DLTERM_NONE)" requires two dynamic libraries "$(DLTERM_LGREEN)"$(LIBXXX)"$(DLTERM_NONE)" and "	\
	$(DLTERM_LGREEN)"$(LIBYYY)"$(DLTERM_NONE)" (of the correct version),"
	@echo "But after compiling the correct version of "$(DLTERM_LGREEN)"$(LIBYYY_VERSION)"$(DLTERM_NONE)", I didn't rename it to "$(DLTERM_LGREEN)"$(LIBYYY)"$(DLTERM_NONE)","
	@echo "Worse, there is a wrong version of "$(DLTERM_LGREEN)"$(LIBYYY)"$(DLTERM_NONE)" in the default search directory of the dynamic library."
	@echo "The solution to the problem is to execute this command: ln -s "$(DLTERM_LGREEN)"$(LIBYYY_VERSION)"$(DLTERM_NONE) $(DLTERM_LGREEN)"$(LIBYYY)"$(DLTERM_NONE)" ."
	@echo $(DLTERM_YELLOW)"********************"$(DLTERM_NONE)
	@echo "Error like : ./libxxx.so: undefined reference to \`func_in_libyyy'"
	@echo "nm libyyy.so.1.0.0 | grep func_in_libyyy"
	@echo "00000518 T func_in_libyyy"
	@echo $(DLTERM_YELLOW)"********************"$(DLTERM_NONE)
.test3_compile_app:
	@echo "Making $(APP_NAME) ..."
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG)	$(LIBS)	-lyyy $(CFLAG_NOVAR) -L/tmp/
.test3_compile_dynlibs_all: .test3_compile_dynlibyyy2
	@echo "Making dynlibs all ..."
.test3_compile_dynlibyyy2: .test3_compile_libxxx
	@echo "Making libyyy *2 ..."
	gcc -o $(LIBYYY_VERSION)    libyyy.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_NOVAR)
	@echo "Copy a copy of "$(DLTERM_LGREEN)"$(LIBYYY)"$(DLTERM_NONE)" as the wrong version of library "$(DLTERM_LGREEN)"$(LIBYYY)"$(DLTERM_NONE)
	cp $(LIBXXX) /tmp/$(LIBYYY)
.test3_compile_libxxx:
	@echo "Making $(LIBXXX) ..."
	gcc -o $(LIBXXX) libxxx.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_NOVAR) -D_LIBXXX_USING_LIBYYY

