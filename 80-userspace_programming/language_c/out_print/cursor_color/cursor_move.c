#include<stdio.h>
#include"../../../../lib_dramalife/terminal_color_dramalife.h"

#define SP	"*"
#define L1	5
#define L2	10
#define L3	15

#define debug_out(x, format, arg...)	if(x & debug_switch){printf(format, ##arg);}

#define	SW_RESULT	0x80
#define SW_VARPNT	0x40
unsigned char debug_switch = 0x80;

struct item_line
{
	char *ihead1;
	char *iname2;
	char *iitem3;
};

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
#if 1
#else
	strncat(itl->iname2, "name", L2);
	print_all(itl, __LINE__);
	strncat(itl->iitem3, "value", L3);
	print_all(itl, __LINE__);
#endif
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

//	MOVER(5);

	fflush(stdout);
	//debug_out( SW_VARPNT ,"\n");
	return;
}

