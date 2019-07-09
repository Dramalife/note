/*
   FILE : section.c

   note gcc attribute-section related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   COPY & MODIFY FROM:
   https://mp.weixin.qq.com/s?__biz=MzAwMDUwNDgxOA==&mid=2652663356&
   idx=1&sn=779762953029c0e0946c22ef2bb0b754&chksm=810f28a1b678a1b74
   7520ba3ee47c9ed2e8ccb89ac27075e2d069237c13974aa43537bff4fba&
   mpshare=1&scene=1&srcid=0111Ys4k5rkBto22dLokVT5A&pass_ticket=
   bGNWMdGEbb0307Tm%2Ba%2FzAKZjWKsImCYqUlDUYPZYkLgU061qPsHFESXlJj%
   2Fyx3VM#rd
*/
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

typedef void (*INIT_CALL)(void);

#define __init __attribute__((unused, section(".myinit")))
#define SECTION_INIT_ADD(func) INIT_CALL _FUNC_##func __init = func

static void module_a_init_func(void)
{
	printf("RUN:%s,%d \n",__func__, __LINE__);
}
SECTION_INIT_ADD(module_a_init_func);

static void module_b_init_func(void)
{
	printf("RUN:%s,%d \n",__func__, __LINE__);
}
SECTION_INIT_ADD(module_b_init_func);

static void module_c_init_func(void)
{
	printf("RUN:%s,%d \n",__func__, __LINE__);
}
SECTION_INIT_ADD(module_c_init_func);

/* Add your init func(s) like this: */
static void module_d_init_func(void)
{
	printf("RUN:%s,%d \n",__func__, __LINE__);
}
SECTION_INIT_ADD(module_d_init_func);

