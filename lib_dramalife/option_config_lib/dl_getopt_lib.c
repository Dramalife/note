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

//#include "dl_getopt_lib.h"
#include "option_config_lib.h"

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

	DL_OPT_SHOW_VERSION(__func__,__LINE__,argc);

	if( 0 != (err_chk = dl_usr_model_check(ptr)) )
	{
		printf("[%s,%d] WARNING! \n",__func__,__LINE__);
	}

#if DL_OPT_DETECT_ETTOR_CHECK(DL_OPT_DETECT_ERROR_LEVEL3_DISTINGUISH)
	strncat(dl_optstring, ":", 1);
#endif
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
		printf("opt(%c),optind(%d),optarg(%s) \n",opt, optind, optarg?optarg:"NULL" );

		/* ARG : opt, optarg */
		/* man 3 getopt
		 * optstring is a string containing the legitimate option characters.  \
		 * If such a character is followed by a colon (':'), the option requires an argument, \
		 * so getopt() places a pointer to the following text in the same argv-element, \
		 * or the text of the following argv-element, in optarg.  
		 * Two colons mean an option takes an optional arg; \
		 * if there  is  text in  the current argv-element (i.e., in the same word as \
		 * the option name itself, for example, "-oarg"), then it is returned in optarg, \
		 * otherwise optarg is set to zero.  This is a GNU extension.  \
		 * If optstring contains W followed by a semicolon, then -W foo is \
		 * treated as the long option --foo.  (The -W option is reserved by POSIX.2 for implemen?
		 * tation extensions.)  This behavior is a GNU extension, not available with 
		 * libraries before glibc 2.
		 */
		/* ex.1
		 * optstring : "T:"
		 * commandline : ./a.out -T
		 * then vaule of variable "opt" is "?"
		 * vaule of pointer variable "optarg" is NULL
		 */
		/* man 3 getopt
		 * While processing the option list, getopt() can detect two kinds of errors: \
		 *	(1) an option character that was not specified in optstring and \
		 *	(2) a missing option argument (i.e., an option at the end of the command line \
		 *	without an expected argument).  Such errors are handled and reported as follows:
		 * o	By default, getopt() prints an error message on standard error, 
		 *	places the erroneous option character in optopt, and returns '?' as the function result.
		 * o	If the caller has set the global variable opterr to zero, then getopt() \
		 *	does not print an error message.  The caller can determine that there was an error \
		 *	by testing whether the function return value is '?'.  (By default, opterr has a nonzero value.)
		 * o	If the first character (following any optional '+' or '-' described above) of optstring is \
		 *	a colon (':'), then getopt() likewise does not print an error message.  In addition, \
		 *	it returns ':' instead of '?' to indicate a missing option argument.  \
		 *	This allows the caller to distinguish the two different types of errors.
		 *
		 * MACRO of "dramalife getopt lib" - DL_OPT_DETECT_ERROR_LEVEL
		 * o1 : default				MACRO - DL_OPT_DETECT_ERROR_LEVEL1_DEFAULT
		 * o2 : disable error printing		MACRO - DL_OPT_DETECT_ERROR_LEVEL2_NO_PRINT_ERR
		 * o3 : distinguish the 2 errors	MACRO - DL_OPT_DETECT_ERROR_LEVEL3_DISTINGUISH
		 */
		if( '?' == opt )
		{
#if DL_OPT_DETECT_ETTOR_CHECK(DL_OPT_DETECT_ERROR_LEVEL3_DISTINGUISH)
			//TODO - handler_option_unregistered
			printf("Recv OPTOPT(%c) OPT(%c) that was UNREGISTERED ! \n",optopt,opt);
#else
			printf("Recv OPTOPT(%c) OPT(%c) that was UNREGISTERED or INCOMPLETE! \n",optopt,opt);
#endif
		}
#if DL_OPT_DETECT_ETTOR_CHECK(DL_OPT_DETECT_ERROR_LEVEL3_DISTINGUISH)
		else if( ':' == opt )
		{
			//TODO - handler_option_incomplete
			printf("Recv OPTOPT(%c) OPT(%c) that was INCOMPLETE! \n",optopt,opt);
		}
#endif
		else if( (ptr = dl_find_opt_by_name(dlopt, opt)) )
		{
			printf("[%s,%d] opt(%c) \n",__func__,__LINE__,opt);
			if( DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_EXIST) )	/* EXPECTED data */
			{
				if( NULL != optarg )
				{
					ptr->dlopt_data = (struct dl_option_data *)malloc(sizeof(struct dl_option_data));
					ptr->dlopt_flag |= DL_OPT_ELEMENT_DATA_NEED_FREE;

					if( DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_TYPE_INT_ARR) )
					{
						*(((struct dl_option_data *)(ptr->dlopt_data))->dloptd_int + 0) = atoi(optarg);
						//TODO - (index + 1)
					}
					if( DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_TYPE_CHAR_ARR) )
					{
						//TODO
					}
				}
				else
				{
					printf("[%s,%d]  Option (%c) expected data, but given none! \n", __func__,__LINE__,opt);
				}
			}
			if(NULL != ptr->dlopt_handler)
			{
				(*(ptr->dlopt_handler)) (ptr);
			}
		}
		else/* TODO - Maybe never enter? */
		{
			printf("Recv OPT(%c) that was UNREGISTERED or INCOMPLETE! \n",optopt);
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


/***********************************************
 * DEMO
 ***********************************************/
#ifdef _DL_GET_OPT_LIB_HAS_DEMO_
#include "../gcc_related_lib/gcc_related_show.h"
int handler_getint(void *arg);
int handler_manuall_run(void *arg);
struct dl_option options_mc[]=
{
	{.dlopt_name = 'm', NULL, handler_manuall_run   ,0                              },  
	{.dlopt_name = 't', NULL, handler_getint                ,0 | DL_OPT_ELEMENT_DATA_EXIST | DL_OPT_ELEMENT_DATA_TYPE_INT_ARR       },  
	{.dlopt_name = 'T', NULL, handler_getint                ,0 | DL_OPT_ELEMENT_DATA_EXIST | DL_OPT_ELEMENT_DATA_TYPE_INT_ARR       },  
	{.dlopt_name = 0x0, NULL, NULL                          ,0                              },  
};
int handler_manuall_run(void *arg)
{
	DL_OPT_HANDLER_PRINT_INFO(arg);
	return 0;
}
/* Sample Function */
int handler_getint(void *arg)
{
	DL_OPT_HANDLER_PRINT_INFO(arg);

	int *data = NULL;
	struct dl_option *ptr = (struct dl_option *)arg;
	if( 1/*SEE BELOW*/
			&& DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_EXIST)
			&& DL_OPT_CHECK_FLAG(ptr->dlopt_flag, DL_OPT_ELEMENT_DATA_TYPE_INT_ARR)
	  )
	{
		data = ((struct dl_option_data *)(ptr->dlopt_data))->dloptd_int;
	}

	if( NULL == data )
	{
		goto error;
	}
	else
	{
		if( ptr->dlopt_name == 't' )
		{
			printf("[%s,%d] %d \n",__func__,__LINE__, *data);
		}
		else if( ptr->dlopt_name == 'T' )
		{
			printf("[%s,%d] %d \n",__func__,__LINE__, *data);
		}
		else
		{
			printf("[%s,%d] data(%d) \n",__func__,__LINE__,*(data + 0));
		}
	}

	return 0;
error:
	printf("[%s,%d] ERROR! \n",__func__,__LINE__);
	return -1;
}

int main(int argc, char **argv)
{
	MAKE_GCC_HAPPY(argc);
	MAKE_GCC_HAPPY(argv);

	dl_getopt(argc, argv, &options_mc);
	dl_getopt_freeall(&options_mc);

	return 0;
}
#endif

