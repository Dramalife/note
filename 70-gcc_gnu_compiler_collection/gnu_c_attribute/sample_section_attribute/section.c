#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

typedef void (*init_call)(void);

#define _init __attribute__((unused, section(".myinit")))
#define DECLARE_INIT(func) init_call _fn_##func _init = func

static void A_init(void)
{
	write(1, "A_init\n", sizeof("A_init\n"));
}
DECLARE_INIT(A_init);

static void B_init(void)
{
	printf("B_init\n");
}
DECLARE_INIT(B_init);

static void C_init(void)
{
	printf("C_init\n");
}
DECLARE_INIT(C_init);
/*
 * DECLARE_INIT like below:
 *  static init_call _fn_A_init __attribute__((unused, section(".myinit"))) = A_init;
 *  static init_call _fn_C_init __attribute__((unused, section(".myinit"))) = C_init;
 *  static init_call _fn_B_init __attribute__((unused, section(".myinit"))) = B_init;
 */

/* Add your init func(s) like this: */
static void D_init(void)
{
	printf("DDDDD_init\n");
}
DECLARE_INIT(D_init);

