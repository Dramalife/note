#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <glob.h>

#define MAX_PATH 1024

#define SIZE_STACK_LS_ARRAY_MEMBER	128
char stack_ls_array[26][SIZE_STACK_LS_ARRAY_MEMBER] = {0};
int stack_ls_index = 0;


void show_dir(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "%s:can not open %s\n", __func__, dir);
		return;
	}
	
#if JUST_FOR_REF______ && 0
	struct dirent {
		ino_t          d_ino;      
		off_t          d_off;       
		unsigned short d_reclen;    /* Length of this record */
		unsigned char  d_type;      
		char           d_name[256]; /* Null-terminated filename */
	};
#endif
	while ((dp = readdir(dfd)) != NULL) {
		if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0))
			continue;
		if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name)) {
			fprintf(stderr, "%s: name %s %s too long\n", __func__, dir, dp->d_name);
		} else {
			sprintf(name, "%s/%s", dir, dp->d_name);

			sprintf(stack_ls_array[stack_ls_index++],"%s/%s", dir, dp->d_name);
			if(stack_ls_index >= sizeof(stack_ls_array))
				stack_ls_index = 0;

			if( fcn )
			{
				(*fcn)(name);
			}
		}
	}
	closedir(dfd);
}

void show_files(char *name)
{
	printf("%s\n", name?name:"nullptr");
}



int glob_main(int argc, char *argv[])
{
	glob_t  paths;
	int     csource;
	char    **p;

	char *wildc = NULL;
	p = argv;

	while( *p)
	{
		if( strchr(*p, (int)'*') )
		{
			wildc = *p;
		}
		*p++;
	}

	if( wildc )
	{
		printf("wildc=(%s)\n", wildc);
		csource = glob(wildc, 0, NULL, &paths);

		if (csource == 0) {
			for (p = paths.gl_pathv; *p != NULL; ++p)
			{
				//printf("===%s\n",*p);
				if( 0 == fork() )
				{
					execlp(argv[0], argv[0], *p, (char *)0);
				}
			}

			globfree(&paths);
		}

		return 0;
	}

	return 2;
}
int dl_process_wildcard(char **des)
{
	return glob_main(0, des);
}

void show_file_or_dir_ls_dir_no_recursion(char *name)
{
	struct stat file_status;
	if (stat(name, &file_status) != 0) {
		fprintf(stderr, "%s:can not access to %s\n", __func__, name);
		return;
	}
	if ((file_status.st_mode & S_IFMT) == S_IFDIR) {
		//show_dir(name, show_file_or_dir_ls);
	}
	//printf("%8ld %s\n", file_status.st_size, name);
	//sprintf(stack_ls_array[stack_ls_index++], "%8ld %s", file_status.st_size, name);
	
}
void show_file_or_dir_ls(char *name)
{
	struct stat file_status;

	printf("ls_name = (%s)\n", name);

	if (stat(name, &file_status) != 0) {
		fprintf(stderr, "%s:can not access to %s\n", __func__, name);
		return;
	}
	if ((file_status.st_mode & S_IFMT) == S_IFDIR) {
		show_dir(name, show_file_or_dir_ls_dir_no_recursion);
	}
	//printf("%8ld %s\n", file_status.st_size, name);

	while(stack_ls_index>=0)
	{
		
			printf("%s\n", stack_ls_array[stack_ls_index]);
		stack_ls_index--;
	}
	stack_ls_index = 0;
}

void show_file_or_dir(char *name)
{
	struct stat file_status;
	if (stat(name, &file_status) != 0) {
		fprintf(stderr, "%s:can not access to %s\n", __func__, name);
		return;
	}
	if ((file_status.st_mode & S_IFMT) == S_IFDIR) {
		show_dir(name, show_file_or_dir);
	}
	printf("%8ld %s\n", file_status.st_size, name);
}


//#define MAIN_FUNC_CALL	show_file_or_dir
#define MAIN_FUNC_CALL	show_file_or_dir_ls
int simple_ls_main(int argc, char *argv[])
{
	if (argc == 1)
		MAIN_FUNC_CALL(".");
	else 
		while (--argc > 0)
			MAIN_FUNC_CALL(*++argv);
	return 0;
}
