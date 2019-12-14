#include "dl_getopt_lib.h"

/* USER defined functions */
/* SETP 3. */
int handler_opt_continuously(void *arg);
int handler_opt_timeval(void *arg);
/* STEP 2. */
struct dl_option options_demo[]=
{
	{.dlopt_name = 'a', NULL, handler_opt_continuously	,0 				},
	{.dlopt_name = 'b', NULL, handler_opt_timeval		,0 | DL_OPT_ELEMENT_DATA_EXIST | DL_OPT_ELEMENT_DATA_TYPE_INT_ARR	},
	{.dlopt_name = 0x0, NULL, NULL				,0 				},
};
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

int main(int argc, char *argv[])
{
       /* STEP 1. */
       dl_getopt(argc, argv, &options_demo);

       dl_getopt_freeall(&options_demo);
       exit(EXIT_SUCCESS);
}

