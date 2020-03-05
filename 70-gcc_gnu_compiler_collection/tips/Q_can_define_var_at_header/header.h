#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#if 0
/* compile successfully */
int gb;
#else
/* GCC Error - multiple definition of `gb' */
int gb = 0;
#endif

extern void functionb();

#endif
