/*
 * note "C - get type string of variable" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 *
 * This file is part of [note](https://github.com/Dramalife/note.git)
 *
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 *
 * $ uname -a
 * Linux iZ2zeeq1jai7e6qn7xqrnuZ 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1
 * 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 *
 * Init : Sun Dec 26 20:48:03 CST 2021
 *   Copy from ref url;
 *
 */

// Ref url:
// https://stackoverflow.com/questions/6280055/how-do-i-check-if-a-variable-is-of-a-certain-type-compare-two-types-in-c
// https://stackoverflow.com/questions/9804371/syntax-and-sample-usage-of-generic-in-c11/17290414#17290414
// http://www.robertgamble.net/2012/01/c11-generic-selections.html


#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define dl_typename(x) \
  _Generic((x),        /* Get the name of a type */          \
                                                                                  \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
      default: "other")
