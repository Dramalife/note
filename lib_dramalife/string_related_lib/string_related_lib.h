#ifndef DRAMALIFE_STRING_RELATED_LIB_H
#define DRAMALIFE_STRING_RELATED_LIB_H


#include <stdint.h>


#define zpi_show_n_bytes(f, ...) _zpi_show_n_bytes(printf, f, ##__VA_ARGS__)


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
extern void 
_zpi_show_n_bytes(
		int (*print_func)(const char *format, ...), 
		const char *buff, 
		uint32_t len
		);



#endif
