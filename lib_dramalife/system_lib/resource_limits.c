/*
 *    GETRLIMIT(2)
 * 
 *    NAME
 *    getrlimit, setrlimit, prlimit - get/set resource limits
 * 
 *    SYNOPSIS
 * #include <sys/time.h>
 * #include <sys/resource.h>
 * 
 * int getrlimit(int resource, struct rlimit *rlim);
 * int setrlimit(int resource, const struct rlimit *rlim);
 * 
 * int prlimit(pid_t pid, int resource, const struct rlimit *new_limit,
 * struct rlimit *old_limit);
 */
#include <sys/time.h>
#include <sys/resource.h>

#include <stdio.h>

#include "system_lib.h"


/* SWITCH - Debug Print */
#if 1
#define DL_INFILE_DEBUG_PRINT_SW	1
#else
#undef DL_INFILE_DEBUG_PRINT_SW
#endif

/* SWITCH - Demo (func main()) */
#if 1
#define DL_INFILE_ADD_MAIN	1
#else
#undef DL_INFILE_ADD_MAIN
#endif


/* MACRO - Debug Print */
#ifdef DL_INFILE_DEBUG_PRINT_SW
#define dl_infile_debug(x,...)	do{printf(x,##__VA_ARGS__);}while(0)
#else
#define dl_infile_debug(x,...)	do{}while(0)
#endif

/* STRUCT - UNUSED ! */
#undef __JUST_ANALYSIS_CODE_o_O
#ifdef __JUST_ANALYSIS_CODE_o_O
struct rlimit
{
	/* The current (soft) limit.  */
	rlim_t rlim_cur;
	/* The hard limit.  */
	rlim_t rlim_max;
};
#endif

/* Infile used functions */
static int getrlimit_info(int line, int resource, struct rlimit *rlim);


static int getrlimit_info(int line, int resource, struct rlimit *rlim)
{
	if( 0 != getrlimit(resource, rlim))
	{
		perror("getrlimit");
		return line;
	}
	else
	{
		dl_infile_debug("hard:%ld \n",rlim->rlim_max);
		dl_infile_debug("curr:%ld \n",rlim->rlim_cur);
	}
	return 0;
}

int dl_set_coredump_unlimit(void)
{
	int ret = 0;
	struct rlimit glimit={0};
	struct rlimit slimit={0};

	/* Getting core limit */
	ret += getrlimit_info(__LINE__, RLIMIT_CORE, &glimit);

	slimit.rlim_max=RLIM_INFINITY;
	slimit.rlim_cur=RLIM_INFINITY;

	/* Setting self core limit */
	if( 0 != setrlimit(RLIMIT_CORE, &slimit) )
	{
		perror("setrlimit");
		ret +=__LINE__;
	}

	/* Getting core limit */
	ret += getrlimit_info(__LINE__, RLIMIT_CORE, &glimit);

	return ret;
}


#ifdef DL_INFILE_ADD_MAIN
int main(int argc, char **argv)
{
	int *ptr=NULL;

	dl_set_coredump_unlimit();

	*ptr = 1;
	return 0;
}
#endif

