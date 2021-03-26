#include "get_path.h"

char *gch;
char *which(char *command, struct pathelement *p)
{
	char cmd[64];
	char *ch = NULL;
	int  found = 0;

	memset(cmd, 0, 64);

	printf("%s,%d , path_addr=%p.\n",__func__,__LINE__,p);

	while (p) {       
		snprintf(cmd, 64, "%s/%s", p->element, command);
		printf("CMD:%s\n", cmd);
		if (access(cmd, X_OK) == 0) {
			found = 1;
			break;
		}
		p = p->next;
	}
	if (found) {
		printf("ch_addr=%p\n", ch);
		ch = malloc(strlen(cmd)+1);
		printf("ch_addr=%p\n", ch);
		strncpy(ch, cmd, strlen(cmd));
		printf("ch_addr=%p\n", ch);

		/* TODO : return vaule err */
#if 1
		gch = ch;
#endif
		return ch;
	}
	else
		return (char *) NULL;
}
