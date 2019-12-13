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


struct dl_option
{
	char dlopt_name;
#define DL_OPT_ELEMENT_NONE	0
#define DL_OPT_ELEMENT_HAVE	1
	unsigned char dlopt_flag;	/* Have element? */
	void *dlopt_data;
	int (*dlopt_handler)(void *);
};


int handler_aaaaa(void *arg);
int handler_bbbbb(void *arg);

struct dl_option options_demo[]=
{
	{'a', DL_OPT_ELEMENT_NONE, NULL, handler_aaaaa},
	{'b', DL_OPT_ELEMENT_HAVE, NULL, handler_bbbbb},
	{0x0, DL_OPT_ELEMENT_NONE, NULL, NULL},
};

int handler_aaaaa(void *arg)
{
	printf("[%s,%d] \n",__func__,__LINE__);
}
int handler_bbbbb(void *arg)
{
	printf("[%s,%d] \n",__func__,__LINE__);
}

struct dl_option *find_option(struct dl_option *arg_ptr, const char arg_opt)
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

int dl_getopt(int argc, char *argv[], struct dl_option (*dlopt)[])
{
	int flags, opt;
	int nsecs, tfnd;

	nsecs = 0;
	tfnd = 0;
	flags = 0;

	char dl_optstring[256];
	memset(dl_optstring, 0, 256);
	printf("[%s,%d] \n",__func__,__LINE__);

	//int index = 0;
	struct dl_option *ptr = *dlopt;
	//while( (*dlopt + index)->dlopt_name != 0  )
	while( ptr->dlopt_name != 0  )
	{
		printf("name(%c), ele_flag(%d) \n"
				//,(*dlopt + index)->dlopt_name 
				//,(*dlopt + index)->dlopt_flag
				,ptr->dlopt_name 
				,ptr->dlopt_flag
		      );

		//strncat(dl_optstring, (const char *)&((*dlopt + index)->dlopt_name), 1);
		strncat(dl_optstring, (const char *)&(ptr->dlopt_name), 1);

		//if( DL_OPT_ELEMENT_HAVE == (*dlopt + index)->dlopt_flag )
		if( DL_OPT_ELEMENT_HAVE == ptr->dlopt_flag )
		{
			strncat(dl_optstring, ":", 1);
		}

		//index++;
		ptr++;
	}
	printf("[%s,%d] optstring(%s) \n",__func__,__LINE__,dl_optstring);


	/* "n"  : no element, "./a.out -n"
	 * "t:" : have element, "./a.out -t 5"
	 * while ((opt = getopt(argc, argv, "nt:")) != -1) {}
	 */
	while ((opt = getopt(argc, argv, dl_optstring)) != -1)
	{
		printf("opt(%c) \n",opt );
#if 1
		if( ptr = find_option(dlopt, opt) )
		{
			if(NULL != ptr->dlopt_handler)
			{
				(*(ptr->dlopt_handler)) (ptr);
			}
		}
		else
		{
			printf("RECV OPT THAT WAS NOT REGISTERED ! \n");
		}
#else
		switch (opt) 
		{
			case 'n':
				flags = 1;
				break;
			case 't':
				nsecs = atoi(optarg);
				tfnd = 1;
				break;
			default: /* '?' */
				fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
						argv[0]);
				exit(EXIT_FAILURE);
		}
#endif
	}

	printf("optind=%d \n",optind);

	if (optind >= argc) {
		fprintf(stderr, "Expected argument after options\n");
		exit(EXIT_FAILURE);
	}

	printf("name argument = %s\n", argv[optind]);
}

int main(int argc, char *argv[])
{

	dl_getopt(argc, argv, &options_demo);

	exit(EXIT_SUCCESS);
}

