
/* Debug print switch */
#define DEBUG_SWITCH	1

/* Print function */
#define debug_out(x,...)	do{if(DEBUG_SWITCH) printf("[%s,%d] ",__func__,__LINE__);printf(x,##__VA_ARGS__);}while(0)

#define GENERAL_BUFF_SIZE	1024

//
#undef ENABLE_USERNAME_HOSTNAME
//
#ifndef ENABLE_USERNAME_HOSTNAME
#define ENABLE_USERNAME_HOSTNAME	1
#endif

#include <errno.h>
#include <stddef.h>
#ifdef ENABLE_USERNAME_HOSTNAME
#include <pwd.h>
#endif


#define HISTORY_CONTENT_SIZE	64
struct list_st
{
	char content[HISTORY_CONTENT_SIZE];
	struct list_st *next;
} *history_head;

struct cmd_history_array_st
{
int used;
char content[HISTORY_CONTENT_SIZE];
};
struct cmd_history_array_st history_array[1024] = {0};

int init_history_list(struct list_st *head)
{
	head = (struct list_st *)malloc(1 * sizeof(struct list_st));
	memset(head->content, 0, sizeof(head->content));
	head->next = NULL;
	return head?0:-1;
}

int cmd_add_history(char *buff)
{
	struct list_st *ptr = NULL;
	struct list_st *new = NULL;

	ptr = history_head;

debug_out("%s,%d\n",__func__,__LINE__);////
	while( NULL != (ptr->next) )
	{
		debug_out("%s,%d\n",__func__,__LINE__);
		ptr = ptr->next;
	}

debug_out("%s,%d\n",__func__,__LINE__);
	new = (struct list_st *)malloc(1 * sizeof(struct list_st));
debug_out("%s,%d\n",__func__,__LINE__);
	strncpy(new->content, buff, sizeof(new->content));

	ptr->next = new;
	new->next = NULL;

debug_out("%s,%d\n",__func__,__LINE__);
	return 0;
}

int cmd_add_history_array(char *buff)
{
	int index = 0;
	while( 0 != history_array[index].used )
		index++;

	strncpy(history_array[index].content, buff, HISTORY_CONTENT_SIZE);
	history_array[index].used = 1;

	return 0;
}

int cmd_show_history(void)
{
	struct list_st *ptr = NULL;
	ptr = history_head;
	while(ptr->next)
	{
		ptr = ptr->next;
		debug_out("[history]%s\n",ptr->content);
	}
	return 0;
}

int cmd_show_history_array(void)
{
	int index = 0;
	while( 0!= history_array[index].used )
	{
		debug_out("-----%s\n",history_array[index].content);
		index++;
	}
	return 0;
}

/* Get line from stdin */
int get_command_line(char *buff)
{
	show_current_dir(buff);

	memset(buff, 0, GENERAL_BUFF_SIZE);
	gets(buff);
	if(strlen(buff))
	{
		cmd_add_history_array(buff);
		debug_out("(%s) \n",buff);
	}
	else
	{
		return 1;
	}
	return 0;
}
int show_current_dir(char *buff)
{
	char hostname[60] = {0};

	memset(buff, 0, GENERAL_BUFF_SIZE);
#ifdef ENABLE_USERNAME_HOSTNAME
	struct passwd *pwd = getpwuid(getuid());
	getcwd(buff, GENERAL_BUFF_SIZE);
	gethostname(hostname, sizeof(hostname));
	debug_out("[OS Shell]%s@%s:%s $", pwd->pw_name, hostname, buff);
#else
	getcwd(buff, GENERAL_BUFF_SIZE);
	debug_out(":%s $",buff);
#endif
	return 0;
}


/* main thread */
int main(int argc, char **argv)
{
	char *buff = NULL;
	
	/* init */
	buff = (char *)malloc(GENERAL_BUFF_SIZE * sizeof(char));

	if (NULL == buff)
	{
		debug_out("malloc error (%s)! \n",strerror(errno));
		exit(2);
	}
	if ( 0 != init_history_list(history_head) )
	{
		debug_out("init cmd_history failed (%s)! \n",strerror(errno));
		exit(2);
	}

	get_command_line(buff);
	get_command_line(buff);
	cmd_show_history_array();

	/* clean */
	free(buff);
	return 0;
}
