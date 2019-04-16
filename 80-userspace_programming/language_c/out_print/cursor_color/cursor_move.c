#include<stdio.h>
#include"../../../../lib_dramalife/terminal_color_dramalife.h"

#define DEBUG_CURSOR	0
#define STATIC_CREATE	0
#define DYNAMIC_CREATE	1
#define DYNAMIC_ARRAY	1
#define ITEM_HAS_ATTRIBUTE	0

#define SP	"*"
#define L1	5
#define L2	10
#define L3	15

#define debug_out(x, format, arg...)	if(x & debug_switch){printf(format, ##arg);}

#define	SW_RESULT	0x80
#define SW_VARPNT	0x40
unsigned char debug_switch = 0x80;

#if ITEM_HAS_ATTRIBUTE
struct xdate_item
{
	int *cont_mem_len;
	char *content_x;
	unsigned char *cont_type;//FILL, NAME, CONTENT...., for auto inital//TODO
};
struct xdate_line
{
	int *item_num;
	struct xdate_item *item_x;
};
struct xdate_block
{
	int *line_num;
	struct xdate_line **line_x;
	char **outbufp;
};
#else
struct item_line
{
	char *ihead1;
	char *iname2;
	char *iitem3;
};
struct atarget
{
	struct item_line **target;
	char **outbufp;
};
#endif



struct item_line **format_print_create(int lines)
{
	int tmp;
	struct item_line **target = malloc(sizeof(struct item_line*));
	*target  = malloc( lines * sizeof(struct item_line));
	memset(	*target, 0, lines * sizeof(struct item_line));
	for(tmp = 0; tmp < lines; tmp++)
	{

		(*target + tmp)->ihead1 = malloc(L1 * sizeof(char));
		(*target + tmp)->iname2 = malloc(L2 * sizeof(char));
		(*target + tmp)->iitem3 = malloc(L3 * sizeof(char));
		memset(	(*target + tmp)->ihead1, 0, L1);
		memset(	(*target + tmp)->iname2, 0, L2);
		memset(	(*target + tmp)->iitem3, 0, L3);
	}
	return target;
}


struct atarget *format_print_create2(int lines)
{
	int tmp;
	struct atarget *att =  malloc(sizeof(struct atarget));

	att->target = malloc(sizeof(struct item_line*));
	*(att->target)  = malloc( lines * sizeof(struct item_line));
	memset(	*(att->target), 0, lines * sizeof(struct item_line));
	att->outbufp = malloc(sizeof(char *));
	*(att->outbufp)  = (char *)malloc( lines * 100 * sizeof(char));

	for(tmp = 0; tmp < lines; tmp++)
	{

		(*(att->target) + tmp)->ihead1 = malloc(L1 * sizeof(char));
		(*(att->target) + tmp)->iname2 = malloc(L2 * sizeof(char));
		(*(att->target) + tmp)->iitem3 = malloc(L3 * sizeof(char));
		memset(	(*(att->target) + tmp)->ihead1, 0, L1);
		memset(	(*(att->target) + tmp)->iname2, 0, L2);
		memset(	(*(att->target) + tmp)->iitem3, 0, L3);
	}
	return att;
}

// 	#######____________ buf 
//	___________________ total_len
//	_______		    content_len
//	#######		    cont1
//	#		    cont2
// require total_len = define_len(buf)
char *fill_content(int total_len, int content_len, char *buf, char *cont)
{
	int tmp;
	tmp = content_len;
	if( (total_len < content_len) 
			|| (content_len < 1) 
			//|| (total_len != len(cont)) //TODO
	  )
	{
		debug_out( SW_VARPNT ,CLRED"%s,%d,error \n"CNONE,__func__, __LINE__);
		while(1);
	}
memset(buf, 0, total_len);

	debug_out( SW_VARPNT ,CLRED"LINE:%d"CNONE "cont_len:%d,arg:%d,, buf-size:%d,len:%d,, totallen:%d,   \n",__LINE__, strlen(cont),content_len, 888, strlen(buf), total_len );

	if(1 == strlen(cont))
	{
		while(tmp--)
			strncat(buf, cont, 1);// **len
	}
	else
	{
		if(strlen(cont) > content_len)
		{
			strncpy(buf, cont, content_len);
		}
		else
		{
			for(tmp = content_len; tmp>= strlen(cont); tmp-=strlen(cont) )
			{
				strncat(buf, cont, strlen(cont));
			}
		}
	}

	tmp = total_len - strlen(buf);
	while(tmp--)
		strcat(buf, " ");//fill

}

void print_all(struct item_line *itl, int line)
{
	debug_out( SW_VARPNT ,CLRED"LINE:%d"CNONE  CLGREEN"L1:"CNONE"%s"  CLGREEN"L2:"CNONE"%s"  CLGREEN"L3:"CNONE"%s\n", line, itl->ihead1, itl->iname2, itl->iitem3);
	return;
}

void produce_line(struct item_line *itl, char *outbuf)
{
	int tmp;
	/*debug_out( SW_VARPNT ,"++%d,%d,%d,%d, \n",__LINE__, sizeof(itl->ihead1 ), sizeof(itl->iname2), sizeof(itl->iitem3));*/
	fill_content(L1, L1-2, itl->ihead1, SP);
	print_all(itl, __LINE__);
	debug_out( SW_VARPNT ,CLRED"LINE:%d,all"CNONE CLGREEN"["CNONE "%s" CLGREEN"]\n"CNONE,__LINE__, itl);

	print_all(itl, __LINE__);
	strcat(outbuf, itl->ihead1);
	strcat(outbuf, itl->iname2);
	strcat(outbuf, itl->iitem3);
	debug_out( SW_RESULT ,CLRED"LINE:%d,all"CNONE CLGREEN"["CNONE "%s" CLGREEN"]\n"CNONE,__LINE__, outbuf);
	return ;
}

void main(void)
{
#if DEBUG_CURSOR	 //pointer
	int *i;
	i = malloc(1 * sizeof(int));
	*i = 1;
	printf("+++++%d\n",*i);
#if 0 //pointer err!
	int **i_165c;
	int *tmp165c = malloc(1 * sizeof(int));
	i = & tmp165c;
	//**i_165c = 2;
	printf("+++++%d\n",**i_165c);
#else //pointer correct!
	int **i_165c;
	i_165c = malloc(sizeof(int*));
	*i_165c = malloc(sizeof(int));
	**i_165c = 2;
	printf("+++++%d\n",**i_165c);
#endif
#endif


#if STATIC_CREATE
	struct item_line *itl = malloc(sizeof(struct item_line));
	char *outbufp = malloc(100 * sizeof(char));
	memset(itl, 0, sizeof(struct item_line));
	memset(outbufp, 0, 100);

	itl->ihead1 = malloc( L1*sizeof(char) );
	itl->iname2 = malloc( L2*sizeof(char) );
	itl->iitem3 = malloc( L3*sizeof(char) );

	fill_content(L2, 4, itl->iname2, "nxxm");
	fill_content(L3, 4, itl->iitem3, "itxx");
	produce_line(itl, outbufp);
#endif

#if DYNAMIC_CREATE && (!DYNAMIC_CREATE)
	struct item_line **target = format_print_create(3);
	char *outbufp0 = malloc(100 * sizeof(char));
	char *outbufp1 = malloc(100 * sizeof(char));
	char *outbufp2 = malloc(100 * sizeof(char));

	fill_content(L2, 4, (*target + 0 )->iname2, "nx1m");
	fill_content(L3, 4, (*target + 0 )->iitem3, "it1x");
	fill_content(L2, 4, (*target + 1 )->iname2, "nx2m");
	fill_content(L3, 4, (*target + 1 )->iitem3, "it2x");
	fill_content(L2, 4, (*target + 2 )->iname2, "nx3m");
	fill_content(L3, 4, (*target + 2 )->iitem3, "it3x");
	produce_line((*target + 0 ),outbufp0 );
	produce_line((*target + 1 ),outbufp1 );
	produce_line((*target + 2 ),outbufp2 );
#elif DYNAMIC_CREATE && DYNAMIC_ARRAY //dynamic char arraY
	struct atarget *att;
	att = format_print_create2(3);

	fill_content(L2, 4, (*(att->target) + 0 )->iname2, "nx1m");
	fill_content(L3, 4, (*(att->target) + 0 )->iitem3, "it1x");
	fill_content(L2, 4, (*(att->target) + 1 )->iname2, "nx2m");
	fill_content(L3, 4, (*(att->target) + 1 )->iitem3, "it2x");
	fill_content(L2, 4, (*(att->target) + 2 )->iname2, "nx3m");
	fill_content(L3, 4, (*(att->target) + 2 )->iitem3, "it3x");
	produce_line( *(att->target) + 0 , *(att->outbufp) + 0 * 100);
	produce_line( *(att->target) + 1 , *(att->outbufp) + 1 * 100);
	produce_line( *(att->target) + 2 , *(att->outbufp) + 2 * 100);

	sleep(2);
	fill_content(L2, 4, (*(att->target) + 1 )->iname2, "haha");
	//produce_line( *(att->target) + 1 , *(att->outbufp) + 1 * 100);
#else
#error: DYNAMIC_ARRAY without DYNAMIC_CREATE is unuseful!
#endif

	//	MOVER(5);
	fflush(stdout);
	return;
}

/*
line--item--attributes

*/


