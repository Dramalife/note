#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

/*
 * __INIT_THE_VAR__	: Initialize variable"gb" in this header file.(CH:)
 *	Define this macro(int gb = <x>;), GCC will report error:
 *	(CH:开启这个宏，头文件中会定义并初始化变量gb，此时GCC会报错)
 * 		GCC Error - multiple definition of `gb'
 *		(CH:重复定义变量gb)
 * __VAR_VAULE_ZERO__	: Initial vaule is 0.(CH:)
 *	Define this macro(int gb = 0;), GCC will place the var to BSS section, else DATA section.
 *	(CH:开启这个宏，头文件中会定义并初始化变量gb=0，GCC会把gb变量放到BSS段，初值不为0时放到DATA段)
 */
#ifdef __INIT_THE_VAR__
#ifdef __VAR_VAULE_ZERO__
int gb = 0;	// DEFINE(o), INIT(o), ZERO(o)
#else
int gb = 111;	// DEFINE(o), INIT(o), ZERO( )
#endif
#else
int gb;		// DEFINE(o), INIT( ), ZERO( )
#endif

extern void functionb();

#endif
