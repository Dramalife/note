/*
 * note "string_related_lib" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 *
 * This file is part of [note](https://github.com/Dramalife/note.git)
 *
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Debian 6.3.0-18+deb9u1) 6.3.0 20170516
 * Copyright (C) 2016 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 *
 * $ uname -a
 * Linux orangepizero 4.19.62-sunxi #5.92 SMP Wed Jul 31 22:07:23 CEST 2019
 *armv7l GNU/Linux;
 *
 * Init : 2019.11.18-22:27;
 * Update
 *
 * 2020.12.28 Update
 *	Add func "_zpi_show_n_bytes";
 * 2021.12.26 Change
 * 	"_zpi_show_n_bytes" => "dl_print_n_bytes";
 *
 */

#include "string_related_lib.h"

#ifdef _DL_STRING_RELATED_LIB_LIB_ENABLE_
void dl_print_n_bytes(int (*print_func)(const char* format, ...),
                      const char* buff,
                      uint32_t len) {
  int index = 0;

  for (index = 0; index < len; index++) {
    print_func("%02x", *(buff + index) & 0xff);
  }

  print_func("\n");

  return;
}
#endif

#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
#define fmt "%20s is '%s'\n"
int main() {
  /* Print n bytes */
  char* temp_str = __func__;
  dl_print_n_bytes(printf, temp_str, strlen(temp_str));

  /* Get variable type (string) */
  size_t s;
  ptrdiff_t p;
  intmax_t i;
  int ai[3] = {0};
  return printf(fmt fmt fmt fmt fmt fmt fmt fmt,

                "size_t", dl_typename(s), "ptrdiff_t", dl_typename(p),
                "intmax_t", dl_typename(i), "character constant",
                dl_typename('0'), "0x7FFFFFFF", dl_typename(0x7FFFFFFF),
                "0xFFFFFFFF", dl_typename(0xFFFFFFFF), "0x7FFFFFFFU",
                dl_typename(0x7FFFFFFFU), "array of int", dl_typename(ai));
}
#endif
