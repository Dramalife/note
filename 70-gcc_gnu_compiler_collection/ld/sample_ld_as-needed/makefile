# 
#  [note](github.com/dramalife/note.git)
#  Dramalife@live.com
#  Init : 2020.03.04
# Update : 2020.03.17
#	Add target - test_old_app__new_dynlib.
#	Update all targets - Using variables.
# 



###########################################
APP_NAME:=app.out


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
	@echo "Making libxxx.so ..."
	gcc -o libxxx.so libxxx.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_NOVAR)
dynlib_report_unresolved_symbols:
	@echo "Making libxxx.so ... :: LIBFLAGS_U"
	gcc -o libxxx.so libxxx.c -fPIC -shared		$(LIBFLAGS_U)	$(CFLAG_VAR) 
clean:
	@echo "Clean all"
	rm -rvf ./*.out ./*.so


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
test_old_app__new_dynlib : dynlib_ok   app_ok   .dynlib_test_var_define
	@echo "Run app manually !"
# OBJS
.app____test_var_define:
	gcc -o $(APP_NAME) app.c -L. $(LDFLAG)		$(LIBS)		$(CFLAG_VAR)
.dynlib_test_var_define:
	@echo "Testing - new libxxx.so"
	gcc -o libxxx.so libxxx.c -fPIC -shared		$(LIBFLAGS)	$(CFLAG_VAR)

