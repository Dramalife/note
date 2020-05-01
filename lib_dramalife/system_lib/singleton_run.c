/*
 * note "program singleton run" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Fri May  1 17:02:04 CST 2020
 *  * ;
 * Update : Fri May  1 17:02:04 CST 2020
 *  
 * Update
 *
 */



#include "lib_dramalife.h"


/* SWITCH - Debug Print */
#ifdef _DLSYS_DEBUG_ENABLED_
#define debugout(x,...)	do{printf("[%s,%s,%d] ",__FILE__,__func__,__LINE__);printf(x,##__VA_ARGS__);}while(0)
#else
#define debugout(x,...)	do{}while(0)
#endif


#ifdef _DL_SYSTEM_LIB_ENABLE_
/* 
 * return == 0 : There is currently no other running copies of this program
 * INPUT : [fixed] file path, [fixed] func name, [dyn] id_numa & id_numb;
 */
int dl_sys_check_singleton(int id_numa, int id_numb)
{
	FILE *fp;
	int pid;
	char buff[256];

	char pid_file_path[128];
#define PID_FILE_PATH_LEN	sizeof(pid_file_path)
	memset(pid_file_path, 0, PID_FILE_PATH_LEN);
	snprintf(pid_file_path, PID_FILE_PATH_LEN, "%s/%s%d", DL_SYS_SINGLETON_RUN_PID_PATH, __func__, id_numa<<8 | id_numb );

	if( access(pid_file_path, F_OK) == 0 )
	{
		if( NULL == (fp = fopen(pid_file_path, "r")) )
		{
			debugout("%s \n",strerror(errno));
		}
		else
		{
			if( EOF == fscanf(fp, "%d", &pid) )
			{
				debugout("%s \n", strerror(errno));
				return 3;
			}
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "/proc/%d/status" ,pid);
			if( access(buff, F_OK) == 0 )
			{
				fclose(fp);
				debugout("ERROR pid(%d) already run! \n", pid);
			}
			else
			{
				fclose(fp);
				remove(pid_file_path);
				fp = fopen(pid_file_path, "w");
				memset(buff, 0, sizeof(buff));
				sprintf(buff, "%d", getpid());
				fwrite(buff, strlen(buff), 1, fp);
				fclose(fp);
				debugout("run(%d) ... \n", getpid());
				return 0;
			}
		}
	}
	else
	{
		if( NULL == (fp = fopen(pid_file_path, "w")) )
		{
			debugout("fopen failed! file(%s), reason(%s)! \n", pid_file_path, strerror(errno));
		}
		else
		{
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "%d", getpid());
			fwrite(buff, strlen(buff), 1, fp);
			fclose(fp);
			debugout("first run(%d) ... \n", getpid());
			return 0;
		}
	}
	return 1;
}
#endif

#ifdef _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(void)
{
	if(1 == dl_sys_check_singleton_ha(__LINE__))
		exit(1);

	sleep(10);
	return 0;
}
#endif

