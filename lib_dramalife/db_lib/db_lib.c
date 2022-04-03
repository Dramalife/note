#include "db_lib.h"

#include <stddef.h>


#ifdef _DL_DB_LIB_ENABLE_
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
#endif

#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
#include "lib_dramalife.h"

#include <stdio.h>
#include <stddef.h>

#if 1 //temp
#define SIZE_DEV_NAME_MAX       32
#endif

#define DLDB_TABLE_NAME	"dldev"


int main(void)
{
	int ret = 0;
	sqlite3 *db=NULL;

	/* Open/Create DB */
	if( 0 != (ret = dldb_open(DLDB_TYPE_SQLITE3, (void *)&db, "test.db")) ){
		printf("open db err, ret=%d!\n", ret);
	}

	/* Create Table */
	char *db_init_table = "CREATE TABLE " DLDB_TABLE_NAME "("
		"sn INT PRIMARY KEY"
		",name TEXT"// SIZE_DEV_NAME_MAX
		",ipaddr TEXT"
		",cpuusage TEXT"
		",memusage TEXT"
		",flashusage TEXT"
		");"
		;
	ret = dldb_exec(DLDB_TYPE_SQLITE3, (void *)&db, db_init_table);
	printf("ret=%d\n", ret);


	/* Del Item*/
	char *db_del_item = "delete from " DLDB_TABLE_NAME " where sn = 8 ;";
	ret = dldb_exec(DLDB_TYPE_SQLITE3, (void *)&db, db_del_item);
	printf("ret=%d\n", ret);

	/* Insert Item*/
	char *db_insert_data = "INSERT INTO " DLDB_TABLE_NAME " (sn,name) VALUES (NULL, 'testname');";
	ret = dldb_exec(DLDB_TYPE_SQLITE3, (void *)&db, db_insert_data);
	printf("ret=%d\n", ret);

	/* Select All */
#if 1
	int nrow=0;
	int ncolumn = 0;
	char *zErrMsg =NULL;
	char **azResult=NULL;
	char *sql="select *from " DLDB_TABLE_NAME ;
	sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
	printf("nrow=%d ncolumn=%d\n",nrow,ncolumn);

	// array len : rol + row*col

	printf("the result is:\n");
	for(int i=0;i<(nrow+1)*ncolumn;i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]?azResult[i]:"nullptr");
	}
#endif

}
#endif
