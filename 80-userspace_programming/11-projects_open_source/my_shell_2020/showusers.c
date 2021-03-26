/* file: showusers.c
   Ben Miller, for cisc361

   This is just a tiny main() to show how to get utmpx entries and printout
   info about logged-in users with entries.  Read some man pages to find out
   how these functions work more...
 */
#include <utmpx.h>
#include <stdio.h>
#include "dl_port.h"

#if 0
int main()
{
	struct utmpx *up;

	setutxent();			/* start at beginning */
	while (up = getutxent())	/* get an entry */
	{
		if ( up->ut_type == USER_PROCESS )	/* only care about users */
		{
			printf("%s has logged on %s from %s\n", up->ut_user, up->ut_line, up ->ut_host);
		}
	}
	return 0;
} /* main() */
#endif


/* In-file used MACRO */
#define SIZE_WATCHUSER_NAME_LEN	64


struct st_watchuser
{
	int refresh;
	char name[SIZE_WATCHUSER_NAME_LEN];
	char line[SIZE_WATCHUSER_NAME_LEN];
	struct st_watchuser *next;
};

struct st_builtin_watchuser
{
	char name[GENERAL_BUFF_SIZE];
	struct st_builtin_watchuser *next;
};


#define dosome()	do{ \
	if( 0 == strncmp(name, h->name, strlen(name)) && 0 == strncmp(line, h->line, strlen(line)) )	\
	{												\
		if(0) printf("%s,%d, cnt=%d,h->cnt=%d. \n",__func__,__LINE__, cnt, h->refresh);		\
		h->refresh = cnt;									\
		return 1;	\
	}	\
}while(0)
static int check_exist_or_insert(struct st_watchuser *h, const char *name, const char *line, int cnt)
{
	while(h->next)
	{
		/* Skip Header */
		h = h->next;
		dosome();
	}

	struct st_watchuser *new = (struct st_watchuser *)malloc(sizeof(struct st_watchuser));
	memset(new->name, 0, SIZE_WATCHUSER_NAME_LEN);
	memset(new->line, 0, SIZE_WATCHUSER_NAME_LEN);
	new->refresh = cnt;		//
	new->next = NULL;
	h->next = new;

	strncpy(new->name, name, strlen(name));
	strncpy(new->line, line, strlen(line));
	return 0;
}
static int check_if_logout(struct st_watchuser *h, int cnt, int cntbefore)
{
	struct st_watchuser *prev = h;
	while(h->next)
	{
		/* Skip Header */
		h = h->next;
		do{
			if( h->refresh > cntbefore )
			{
				if(0) printf("%s still online! \n", h->line);
				h->refresh = cnt;
			}
			else
			{
				printf("\n%s has logged out %s\n", h->name, h->line);

				/* Del it */
				prev->next = h->next;
				free(h);

			}
		}while(0);
		prev = h;
	}
	return 0;
}

/*****
 * RETURN :
 *	0 : care(found)
 */
static check_if_watchuser_care(char *name, struct st_builtin_watchuser *care)
{
	while(care->next)
	{
		care = care->next;
		if( 0 == strncmp(name, care->name, strlen(name)) )
		{
			return 0;
		}
	}

	return 2;
}

/*****
 * Usage : (CMD)
 * $ ./a.out <USERNAME>
 *
 * Usage : (API)
 * struct st_builtin_watchuser g_head;
 * watchuser_main(2, &g_head);
 */
#define WATCHUSER_MAIN_USE_AS_API_THREAD	1
#define WATCHUSER_MAIN_USE_AS_API_PROCESS	2
#define WATCHUSER_MAIN_USE_AS_CMD_CMDLINE	3
#define WATCHUSER_MAIN_USE_MODE	WATCHUSER_MAIN_USE_AS_API_THREAD

#if WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_API_THREAD
int watchuser_main(void *watch)	// API - thread
#elif WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_API_PROCESS
int watchuser_main(int argc, void *watch)	// API - process
#elif WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_CMD_CMDLINE
int main(int argc, char **argv)		// CMD (command line)
#else
#error HERE!!
#endif
{
	printf("%s,%d Start..\n", __func__,__LINE__);
/* In-func used MACRO */
#define WATCHUSER_MAIN_ARGC_MODE_CMD	(2)
#define WATCHUSER_MAIN_ARGC_MODE_API	(-2)
	struct utmpx *up;
	int watchuser_cnt = 0;
	struct st_watchuser *watchuser_headp;

	if( 0
#if WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_CMD_CMDLINE
			|| WATCHUSER_MAIN_ARGC_MODE_CMD != argc // CMD mode
#elif WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_API_PROCESS
			|| WATCHUSER_MAIN_ARGC_MODE_API != argc // API - process  mode
#endif
	  )
	{
		return 2;
	}
#if WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_API_PROCESS || WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_API_THREAD
	struct st_builtin_watchuser *watch_head = (struct st_builtin_watchuser *)watch;
#endif

	watchuser_headp = (struct st_watchuser *)malloc(sizeof(struct st_watchuser));
	memset(watchuser_headp->name, 0, SIZE_WATCHUSER_NAME_LEN);
	memset(watchuser_headp->line, 0, SIZE_WATCHUSER_NAME_LEN);
	watchuser_headp->refresh = 0;
	watchuser_headp->next = NULL;


	int ret = -1;
	int flag_inloop = 0;
	int watchuser_cnt_before = 0;
	struct st_watchuser *wp = watchuser_headp;
	while(1)
	{
		setutxent();			/* start at beginning */
		watchuser_cnt_before = watchuser_cnt;
		while (up = getutxent())	/* get an entry */
		{
			if ( up->ut_type == USER_PROCESS )	/* only care about users */
			{
				if( 0
#if WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_CMD_CMDLINE
						|| 0 == strncmp(argv[1], up->ut_user) 
#elif WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_API_PROCESS || WATCHUSER_MAIN_USE_MODE == WATCHUSER_MAIN_USE_AS_API_THREAD
						|| 0 == check_if_watchuser_care(up->ut_user, watch_head) 
#endif
				  )
					flag_inloop = 1;

				if( 1 == flag_inloop )
				{
					ret = check_exist_or_insert(watchuser_headp, up->ut_user, up->ut_line, ++watchuser_cnt);
					switch(ret)
					{
						case 0:
							printf("\n%s has logged on %s from %s\n", up->ut_user, up->ut_line, up ->ut_host);
							break;
						default:
							break;
					}
				}
			}
		}

		/*****
		 * Extra Credit (5 points)
		 * Also have your thread notify when the users being watched log off of a tty. 
		 */
		 if( 1 == flag_inloop)
		 {
			 check_if_logout(watchuser_headp, watchuser_cnt, watchuser_cnt_before);
		 }

		sleep(3);
		flag_inloop = 0;
	}

	return 0;
}

