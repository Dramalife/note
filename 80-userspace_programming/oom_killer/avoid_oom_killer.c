/*
 * note "oom killer(Out Of Memory)" related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-66-generic #75-Ubuntu SMP Tue Oct 1 05:24:09 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux;
 * 
 * Ref : https://github.com/linux-audit/audit-userspace.git
 *	 	--branch=v2.8.2;
 *	 	src/auditd.c +326 : static void avoid_oom_killer(void);
 * 
 * Init : 2019.11.01, TODO:test! ;
 * Update 
 *
 */



#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


static void avoid_oom_killer(void)
{
	int oomfd, len, rc;
	char *score = NULL;

	/* New kernels use different technique */            
	if ((oomfd = open("/proc/self/oom_score_adj",
					O_NOFOLLOW | O_WRONLY)) >= 0) { 
		score = "-1000";
	} else if ((oomfd = open("/proc/self/oom_adj",
					O_NOFOLLOW | O_WRONLY)) >= 0) { 
		score = "-17";
	} else {
		//audit_msg(LOG_NOTICE, "Cannot open out of memory adjuster");
		printf("Cannot open out of memory adjuster");
		return;
	}    

	len = strlen(score);
	rc = write(oomfd, score, len);
	if (rc != len) 
	{
		//audit_msg(LOG_NOTICE, "Unable to adjust out of memory score");
		printf("Unable to adjust out of memory score");
	}

	close(oomfd);
}

int main(void)
{
	avoid_oom_killer();

	while(1)
	{

	}

	return 0;
}

