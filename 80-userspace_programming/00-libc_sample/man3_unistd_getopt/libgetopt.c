/* EXAMPLE
 * getopt()
 * 	The  following  trivial  example  program  uses  getopt()  to handle two program options: -n,\
 *	with no associated value; and -t val, which expects an associated value.
 */
 //pointer array
 //array pointer

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define DL_OPT_CHECK_FLAG(x,y)	(x&y)


struct dl_option
{
	char dlopt_name;
	void *dlopt_data;
	int (*dlopt_handler)(void *);
#define DL_OPT_ELEMENT_DATA_EXIST		0x80
#define DL_OPT_ELEMENT_DATA_NEED_FREE		0x40
#define DL_OPT_ELEMENT_DATA_TYPE_CHAR_ARR	0x20
#define DL_OPT_ELEMENT_DATA_TYPE_INT_ARR	0x10
	unsigned char dlopt_flag;	/* Have element? */
};
#ifndef	DL_OPTD_DATA_BYTE_SIZE
#define	DL_OPTD_DATA_BYTE_SIZE	8
#endif
struct dl_option_data
{
	unsigned char dloptd_flag;	/* type? */
	union{
		char dloptdu_string[	DL_OPTD_DATA_BYTE_SIZE			];
		int dloptdu_int[	DL_OPTD_DATA_BYTE_SIZE / sizeof(int)	];
	} dloptd_u;/*array pointer*/
#define dloptd_string	dloptd_u.dloptdu_string
#define dloptd_int	dloptd_u.dloptdu_int
};


/* SETP 3. */
int handler_opt_continuously(void *arg);
int handler_opt_timeval(void *arg);

/* STEP 2. */
struct dl_option options_demo[]=
{
	{'a', NULL, handler_opt_continuously	,0 				},
	{'b', NULL, handler_opt_timeval		,0 | DL_OPT_ELEMENT_DATA_EXIST | DL_OPT_ELEMENT_DATA_TYPE_INT_ARR	},
	{0x0, NULL, NULL			,0 				},
};

#define DL_OPT_HANDLER_PRINT_INFO(x)	do{							\
	struct dl_option *self = (struct dl_option *)x;						\
	if(self){										\
		printf("[%s,%d] SELF - name(%c),flag(0x%02X),havedata(%c),havehandler(%c). \n" 	\
				,__func__,__LINE__                                         	\
				,self->dlopt_name                                          	\
				,self->dlopt_flag                                          	\
				,self->dlopt_data?'Y':'N'                                  	\
				,self->dlopt_handler?'Y':'N'                               	\
				);                                                             	\
	}											\
}while(0)

/* Sample Function */
int handler_opt_continuously(void *arg)
{
	DL_OPT_HANDLER_PRINT_INFO(arg);
	return 0;
}
/* Sample Function */
int handler_opt_timeval(void *arg)
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
		printf("[%s,%d] data(%d) \n",__func__,__LINE__,*(data + 0));
	}

	return 0;
error:
	printf("[%s,%d] ERROR! \n",__func__,__LINE__);
	return -1;
}

struct dl_option *dl_find_opt_by_name(struct dl_option *arg_ptr, const char arg_opt)
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
int dl_usr_model_check(struct dl_option *arg_opt)
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

int main(int argc, char *argv[])
{
	/* STEP 1. */
	dl_getopt(argc, argv, &options_demo);

	dl_getopt_freeall(&options_demo);
	exit(EXIT_SUCCESS);
}

