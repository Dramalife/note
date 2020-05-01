# Makefile Library
include $(PATH_ABS)/mk/multi_lib.mk

# Header Files` Path
CFLAGS+=-I$(PATH_ABS)

# Library Path for Demo (compile & runtime)
CFLAGS_DEMO+=-ldramalife -L$(PATH_ABS) -Wl,-rpath=$(PATH_ABS)

# Library Code compile switch, for mode-lib only.
CFLAGS_DYNLIB+=-D_DL_TERMINAL_LIB_ENABLE_

# Demo Code compile switch, for mode-demo only.
# Command "make demo_of_dynlib" will enable this automatically.
#CFLAGS_DEMO+=_DRAMALIFE_LIB_HAS_FUNC_MAIN_

# Extra CFLAGS SWITCH
#DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE:=1

# Debug Print Switch - TODO
CFLAGS_DEMO+=-D_DLTERMINAL_DEBUG_ENABLED_
CFLAGS_DYNLIB+=-D_DLTERMINAL_DEBUG_ENABLED_
