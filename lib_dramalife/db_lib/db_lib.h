#ifndef _LIB_DRAMALIFE_DB_LIB_H_
#define _LIB_DRAMALIFE_DB_LIB_H_

#include "./sqlite3.h"

/****
 * DLTYPE_DB_0001
 */
enum{
	DLDB_TYPE_SQLITE3 = 0,
};

extern int dldb_open(int dltype, void *handle, const char *filename);
extern int dldb_exec(int dltype, void *handle, const char *cmd);
#endif
