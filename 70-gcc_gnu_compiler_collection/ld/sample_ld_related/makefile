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
# 



###########################################
APP_NAME:=app.out
LIB_NAME:=libxxx.so
LIB_VNAME:=libxxx.so.1.0.0


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
	@echo "Making $(LIB_NAME) ..."
	gcc -o $(LIB_NAME) libxxx.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_NOVAR)
dynlib_report_unresolved_symbols:
	@echo "Making $(LIB_NAME) ... :: LIBFLAGS_U"
	gcc -o $(LIB_NAME) libxxx.c -fPIC -shared		$(LIBFLAGS_U)	$(CFLAG_VAR) 

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
	@echo "Testing - new libxxx.so"
	gcc -o libxxx.so libxxx.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_VAR)

###########################################
# Err3 : [compile]./libxxx.so: undefined reference to `func_in_libyyy'
###########################################
test3_found_wrong_dynlib: .test3_print_info  .test3_compile_dynlibs_all  .test3_compile_app  
.test3_print_info:
	@echo "NOTE:\n********************"
	@echo "$(APP_NAME) requires two dynamic libraries $(LIB_NAME) and libyyy.so (of the correct version),"
	@echo "But after compiling the correct version of libyyy.so.1.x.x, I didn't rename it to libyyy.so,"
	@echo "And, the default search dir has the WRONG VERSION LIB !!!"
	@echo "Worse, there is a wrong version of libyyy in the default search directory of the dynamic library"
	@echo "so, ln -s libyyy.so.1.x.x libyyy.so !!!!"
	@echo "********************"
.test3_compile_app:
	@echo "Making $(APP_NAME) ..."
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG)	$(LIBS)	-lyyy	$(CFLAG_NOVAR) -L/tmp/
.test3_compile_dynlibs_all: .test3_compile_dynlibyyy2
	@echo "Making dynlibs all ..."
.test3_compile_dynlibyyy2:dynlib_ok
	@echo "Making libyyy *2 ..."
	gcc -o libyyy.so.1.0.0    libyyy.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_NOVAR)
	cp libxxx.so /tmp/libyyy.so

