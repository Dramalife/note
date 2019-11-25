/*
 * note "strcmp" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 \
 *	UTC 2015 i686 i686 i686 GNU/Linux;
 * 
 * Init : 2019.11.25;
 * Update 
 *
 */


//	520	00	CAT Telecom					x.IMSI_ISP_SUPPORT_OPERATIONAL
//	520	01	Advanced Info Service				x.IMSI_ISP_SUPPORT_NOTOPERATIONAL
//	520	02	CAT Telecom					x.IMSI_ISP_SUPPORT_NOTOPERATIONAL
//	520	03	Advanced Wireless Network Company Ltd.		x.IMSI_ISP_SUPPORT_OPERATIONAL
//	520	04	True Move H Universal Communication Company Ltd.x.IMSI_ISP_SUPPORT_OPERATIONAL
//	520	05	DTAC TriNet Company Ltd.			x.IMSI_ISP_SUPPORT_OPERATIONAL
//	520	09	Royal Thai Police				x.IMSI_ISP_SUPPORT_OPERATIONAL
//	520	15	TOT Public Company Limited			x.IMSI_ISP_SUPPORT_OPERATIONAL
//	520	18	Total Access Communications Public Company Ltd.	x.IMSI_ISP_SUPPORT_OPERATIONAL
//	520	20	ACeS						x.IMSI_ISP_SUPPORT_UNKNOWN
//	520	23	Digital Phone Company Ltd.			x.IMSI_ISP_SUPPORT_NOTOPERATIONAL
//	520	25	True Corporation				x.IMSI_ISP_SUPPORT_NOTOPERATIONAL
//	520	47	TOT Public Company Limited			x.IMSI_ISP_SUPPORT_OPERATIONAL

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define STRLEN_MCC	4
#define STRLEN_MNC	3
#define STRLEN_IMSI_CHECK	(STRLEN_MCC + STRLEN_MNC -2)
#define STRLEN_IMSI_ALLOC	(STRLEN_MCC + STRLEN_MNC)
#define STRLEN_ISP	128
struct st_imsi
{
	char mcc[STRLEN_MCC];
	char mnc[STRLEN_MNC];
};
struct st_imsi_isp_match_dramalife
{
	struct st_imsi imsi_d;
	char isp_d[STRLEN_ISP];
#define IMSI_ISP_SUPPORT_OPERATIONAL	0x01
#define IMSI_ISP_SUPPORT_NOTOPERATIONAL	0x02
#define IMSI_ISP_SUPPORT_UNKNOWN	0x04
	unsigned char operid_d;
	unsigned char support_d;
};


struct st_imsi_isp_match_dramalife st_d[]=
{
	{ {"520","00"}, "CAT Telecom"						 ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
	{ {"520","01"}, "Advanced Info Service"                                  ,	0,	IMSI_ISP_SUPPORT_NOTOPERATIONAL},
	{ {"520","02"}, "CAT Telecom"                                            ,	0,	IMSI_ISP_SUPPORT_NOTOPERATIONAL},
	{ {"520","03"}, "Advanced Wireless Network Company Ltd."                 ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
	{ {"520","04"}, "True Move H Universal Communication Company Ltd."       ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
	{ {"520","05"}, "DTAC TriNet Company Ltd."                               ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
	{ {"520","09"}, "Royal Thai Police"                                      ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
	{ {"520","15"}, "TOT Public Company Limited"                             ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
	{ {"520","18"}, "Total Access Communications Public Company Ltd."        ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
	{ {"520","20"}, "ACeS"                                                   ,	0,	IMSI_ISP_SUPPORT_UNKNOWN       },
	{ {"520","23"}, "Digital Phone Company Ltd."                             ,	0,	IMSI_ISP_SUPPORT_NOTOPERATIONAL},
	{ {"520","25"}, "True Corporation"                                       ,	0,	IMSI_ISP_SUPPORT_NOTOPERATIONAL},
	{ {"520","47"}, "TOT Public Company Limited"				 ,	0,	IMSI_ISP_SUPPORT_OPERATIONAL   },
};

struct card
{
	char imsi[128];
	int opr;
};

void check_sample(struct st_imsi_isp_match_dramalife *st/*, struct card *card*/)
{
	struct st_imsi_isp_match_dramalife *st_p = st;
	char *tmp = (char *)malloc(sizeof(char)*STRLEN_IMSI_ALLOC );
	struct card card_d;
	memset(&card_d, 0, sizeof(struct card));
	strcpy(card_d.imsi, "12345");
	struct card *card = &card_d;

	while( strlen(st_p->imsi_d.mcc) && strlen(st_p->imsi_d.mnc) )
	{
		if(IMSI_ISP_SUPPORT_OPERATIONAL != st_p->support_d)
			goto while_next;

		memset(tmp, 0, STRLEN_IMSI_ALLOC);
		strncat(tmp, st_p->imsi_d.mcc, STRLEN_MCC);
		strncat(tmp, st_p->imsi_d.mnc, STRLEN_MNC);
		printf("[%s,%d]"
				"TEMPLE imsi(%s),isp(%-60s),opr_id(%d),support(%d)"
				"CARD(%s)"
				" \n"
				,__func__,__LINE__
				,tmp
				,st_p->isp_d
				,st_p->operid_d
				,st_p->support_d
				,card->imsi
		      );
		if( !strncmp(card->imsi, tmp, STRLEN_IMSI_CHECK) )
		{
			printf("matched! \n");
		}
while_next:
		st_p++;
	}

	free(tmp);
}

int main(void)
{
	check_sample(st_d);
	return 0;
}
