BIN_NAME=a_demo

BIN_END=.out
BIN_O=.o
PRE_COMP=.i
DIS_ASSB=.ass
SHD_LIB=.so

ifndef DO_NOT_USE_CFLAGS_IN_LIBMAKEFILE
# Warning Options
CFLAGS += -Wall -Wextra -Wno-sign-compare -Wno-missing-field-initializers -Wundef -Wunused-parameter -Wunused-but-set-variable

# Dialect Options
CFLAGS += -Wno-deprecated-declarations

# C and Objective-C-only Warning Options
CFLAGS += -Wstrict-prototypes 

# Options to Request or Suppress Warnings
CFLAGS += -Werror

# Options for Code Generation Conventions
CFLAGS += -fno-common

# -Wno-format
CFLAGS += -Wformat

# Options for Debugging Your Program or GCC
CFLAGS += -g -O2

# -fno-strict-aliasing
# -ffreestanding
# -Wno-implicit-fallthrough
# -Wno-shift-negative-value
# -Wno-pointer-compare

#CFLAGS += -v
endif
