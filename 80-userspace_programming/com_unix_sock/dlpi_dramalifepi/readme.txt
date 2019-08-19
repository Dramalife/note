<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
$ gcc --version
gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ uname -a
Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux



<<<<<<< HEAD
=======
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3

typedef struct dlpi_frame
{
char *des_sock_path;	//specific sock path
u8_t mechine_specific_code[2];	//specific mechine, not useful yet.
u8_t lll_type[2];	//(toDES|to_others|)
u8_t global_data_struct_code[2];	//16 bit.
void *buffer;	//(trans_to_datastruct|trans_to_DES_level)
}dlpi_frame;

<<<<<<< HEAD

=======
<<<<<<< HEAD
=======

>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
