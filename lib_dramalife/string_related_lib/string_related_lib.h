#ifndef DRAMALIFE_STRING_RELATED_LIB_H
#define DRAMALIFE_STRING_RELATED_LIB_H

#include <stdint.h>

#include "get_type_str_of_variable.h"

#define dl_show_n_bytes(b, l) dl_print_n_bytes(printf, b, l)
#define zpi_show_n_bytes(b, l) dl_print_n_bytes(printf, b, l)
#define _zpi_show_n_bytes dl_print_n_bytes

/****
 * Use the "@print_func" function to print the first "@len" bytes of the memory
 * pointed to by the pointer "@buff".
 *
 * ARG0	@print_func	: Func used when printing buffer. ex. printf;
 * ARG1 @buff		: Buffer to be printed
 * ARG2 @len		: Length of buffer to be printed
 *
 * RETURN:
 *	VOID;
 *
 */
extern void dl_print_n_bytes(int (*print_func)(const char* format, ...),
                             const char* buff,
                             uint32_t len);

#endif
