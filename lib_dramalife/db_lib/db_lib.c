#include "db_lib.h"

#include <stddef.h>

/*****
 * @dltype	: ref DLTYPE_DB_0001;
 * @filename	: db file name;
 * @handle	:
 */
int dldb_open(int dltype, void *handle, const char *filename)
{
	int ret = 0;

	switch(dltype){
		case DLDB_TYPE_SQLITE3:
			{
				sqlite3 **ppdb = (sqlite3 **)handle;

				ret = sqlite3_open(filename, ppdb);
				if(ret){
					dprintf(2, "Can't open database: %s\n", sqlite3_errmsg(*ppdb));
					sqlite3_close(*ppdb);
				}
			}
			break;

		default:
			break;
	}

	return ret;
}
int dldb_exec(int dltype, void *handle, const char *cmd)
{
	sqlite3 **pdb = (sqlite3 **)handle;
	char *dl_errstr = NULL;

	if( 0 != sqlite3_exec(*pdb, cmd, NULL, NULL, &dl_errstr) ){
		printf("err string : %s\n", dl_errstr);
		sqlite3_free(dl_errstr);
	} 
}

// gcc sample.c ./sqlite3.o ./db_lib.c -I .. -lpthread -ldl -g
