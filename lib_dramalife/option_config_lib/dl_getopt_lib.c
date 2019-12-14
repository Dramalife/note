/*
 * note "getopt" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 *
 * $ uname -a
 * Linux server 4.15.0-70-generic #79-Ubuntu SMP Tue Nov 12 10:36:11 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : 2019.12.13
 *	COPY FROM "man 3 getopt getopt()" :
 *	EXAMPLE
 *	getopt()
 *	 	The  following  trivial  example  program  uses  getopt()  to handle two program options: -n,\
 *		with no associated value; and -t val, which expects an associated value.
 * ;
 *
 * Update : 2019.12.14
 *	Using struct saving options and handlers ;
 * Update 
 *
 */

#include "dl_getopt_lib.h"

//pointer array
//array pointer
/* Local used functions */
static int dl_usr_model_check(struct dl_option *arg_opt);
static struct dl_option *dl_find_opt_by_name(struct dl_option *arg_ptr, const char arg_opt);

/* Core functions of "lib_dramalife_getopt" */

/* Finding (char)opt at (struct dl_option *)arg_ptr */
static struct dl_option *dl_find_opt_by_name(struct dl_option *arg_ptr, const char arg_opt)
{
	struct dl_option *result = arg_ptr;
	while( result->dlopt_name != 0  )
	{
		if( arg_opt == result->dlopt_name )
		{
			return result;
		}
		result++;
	}
	return NULL;
}

/*
 * ARG : A pointer point to struct [array] !
 */
static int dl_usr_model_check(struct dl_option *arg_opt)
{
	int err_cnt = 0;
	struct dl_option *ptr = NULL;
	ptr = arg_opt;
	while( ptr->dlopt_name != 0  )
	{
		/* Flag Illegality Check */
		if( 0/*see below*/
				|| DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_TYPE_INT_ARR) 
				|| DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_TYPE_CHAR_ARR) 
		  )
		{
			if( 0 == DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_EXIST) )
			{
				err_cnt++;
				ptr->dlopt_flag &= ~DL_OPT_ELEMENT_DATA_EXIST;
				printf("[%s,%d] FLAG ILLEGAL ! REPAIRED AUTOMATICALLY !! \n",__func__,__LINE__);
			}
		}

		ptr++;
	}
	printf("[%s,%d] error_sum(%d) \n",__func__,__LINE__,err_cnt);
	return err_cnt;
}

/* getopt of lib_dramalife_getopt */
int dl_getopt(int argc, char *argv[], struct dl_option (*dlopt)[])
{
	int opt = 0;
	int err_chk = 0;
	char dl_optstring[256];
	struct dl_option *ptr = NULL;

	/* Variable Init */
	ptr = *dlopt;//TODO
	memset(dl_optstring, 0, 256);

	printf("[%s,%d] argc(%d) \n",__func__,__LINE__, argc);
	if( 0 != (err_chk = dl_usr_model_check(ptr)) )
	{
		printf("[%s,%d] WARNING! \n",__func__,__LINE__);
	}

	while( ptr->dlopt_name != 0  )
	{
		printf("name(%c), ele_flag(%d) \n"
				,ptr->dlopt_name 
				,ptr->dlopt_flag
		      );
		strncat(dl_optstring, (const char *)&(ptr->dlopt_name), 1);
		if( DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_EXIST) )
		{
			strncat(dl_optstring, ":", 1);
		}
		ptr++;
	}
	printf("[%s,%d] optstring(%s) \n",__func__,__LINE__,dl_optstring);

	/* "n"  : no element, "./a.out -n"
	 * "t:" : have element, "./a.out -t 5"
	 * while ((opt = getopt(argc, argv, "nt:")) != -1) {}
	 */
	/*
	 * VAR_LIBC_GLOBAL : 	optarg - all arg
	 *			optind - index
	 *			optopt - error option
	 */
	while ((opt = getopt(argc, argv, dl_optstring)) != -1)
	{
		printf("opt(%c),optind(%d) \n",opt, optind );
		if( (ptr = dl_find_opt_by_name(dlopt, opt)) )
		{
			if( DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_EXIST) )
			{
				ptr->dlopt_data = (struct dl_option_data *)malloc(sizeof(struct dl_option_data));
				ptr->dlopt_flag |= DL_OPT_ELEMENT_DATA_NEED_FREE;

				if( DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_TYPE_INT_ARR) )
				{
					*(((struct dl_option_data *)(ptr->dlopt_data))->dloptd_int + 0) = atoi(optarg);
				}
			}
			if(NULL != ptr->dlopt_handler)
			{
				(*(ptr->dlopt_handler)) (ptr);
			}
		}
		else
		{
			printf("RECV OPT(%c) THAT WAS NOT REGISTERED ! \n",optopt);
		}
	}

	printf("optind=%d \n",optind);

	// TODO
	if (optind >= argc) {
		fprintf(stderr, "Expected argument after options\n");
		//exit(EXIT_FAILURE);
	}
	else
	{
		printf("name argument = %s\n", argv[optind]);
	}
	return optind;
}

/* clean function of dramalife_getopt */
void dl_getopt_freeall(struct dl_option (*dlopt)[])
{
	struct dl_option *ptr = *dlopt;//TODO
	while( ptr->dlopt_name != 0  )
	{
		if( DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_NEED_FREE) )
		{
			/* safe free */
			if(ptr->dlopt_data)
			{
				free(ptr->dlopt_data);
				ptr->dlopt_data = NULL;
			}
		}
		ptr++;
	}
	printf("[%s,%d] DL_GETOPT CLEAN DONE! \n",__func__,__LINE__);
}

