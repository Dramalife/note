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

#include "lib_dramalife.h"
//#include "system_lib.h"


/* SWITCH - Debug Print */
#ifdef _DLSYS_DEBUG_ENABLED_
#define dl_infile_debug(x,...)	do{\
	printf("[dl_syslib] ");\
	printf(x,##__VA_ARGS__);\
}while(0)
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


#ifdef _DL_SYSTEM_LIB_ENABLE_
/* Infile used functions */
static int dlstatic_getrlimit_info(int line, int resource, struct rlimit *rlim)
{
	if( 0 != getrlimit(resource, rlim))
	{
		dl_infile_debug("[%s,%d] ERROR getrlimit (%s)!", 
				__func__,__LINE__,
				strerror(errno)?strerror(errno):"null"/* Compatible with uClibc */
			       );
		return line;
	}
	else
	{
		dl_gcc_print_name_vaule(rlim->rlim_max, dl_infile_debug);
		dl_gcc_print_name_vaule(rlim->rlim_cur, dl_infile_debug);
	}
	return 0;
}

int dl_set_coredump_unlimit(void)
{
	int ret = 0;
	struct rlimit glimit={0};
	struct rlimit slimit={0};

	/* Getting core limit */
	ret += dlstatic_getrlimit_info(__LINE__, RLIMIT_CORE, &glimit);

	slimit.rlim_max=RLIM_INFINITY;
	slimit.rlim_cur=RLIM_INFINITY;

	/* Setting self core limit */
	if( 0 != setrlimit(RLIMIT_CORE, &slimit) )
	{
		perror("setrlimit");
		ret +=__LINE__;
	}

	/* Getting core limit */
	ret += dlstatic_getrlimit_info(__LINE__, RLIMIT_CORE, &glimit);

	return ret;
}
#endif


#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(int argc, char **argv)
{
	int *ptr=NULL;

	MAKE_GCC_HAPPY(argc);
	MAKE_GCC_HAPPY(argv);

	dl_infile_debug("Demo call lib_func start... \n");
	dl_set_coredump_unlimit();
	dl_infile_debug("Demo call lib_func end... \n");

	*ptr = 1;
	return 0;
}
#endif

