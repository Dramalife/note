/*****
 * Library Code 
 */
#ifdef _DL_DATASTRUCT_LIB_ENABLE_

//Debug print switch
#ifdef D_DLDS_DEBUG_ENABLED_
#else
#define printf(x,...)	do{}while(0)
#endif

#endif/*_DL_DATASTRUCT_LIB_ENABLE_*/



/*****
 * Demo/Sample Code 
 */
#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
#include "lib_dramalife.h"

//Debug print switch
#ifdef D_DLDS_DEBUG_ENABLED_
#else
#define printf(x,...)	do{}while(0)
#endif

int main(void)
{
	/* Test functions in header file */
	hlist_add_after(NULL,NULL);

	return 0;
}
#endif/*_DRAMALIFE_LIB_HAS_FUNC_MAIN_*/
