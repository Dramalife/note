#include<stdio.h>
#include"../../../lib_dramalife/terminal_color_dramalife.h"

#define SP	"*"
#define L1	5
#define L2	10
#define I1	15
struct item_line
{
	char hone[L1];
	char hname[L2];
	char item1[I1];
};

char *fill_content(int total_len, int content_len, char *buf, char *cont)
{
	int tmp;
	tmp = content_len;
	printf("cont_len:%d,arg:%d,, buf-size:%d,len:%d,, totallen:%d,   \n",strlen(cont),content_len, sizeof(buf), strlen(buf), total_len );
	if(1 == strlen(cont))
	{
		while(tmp--)
			strncat(buf, cont, 1);// **len
	}
	else
	{
		while( (sizeof(buf) - strlen(buf)) >= strlen(cont))
		{
			strncat(buf, cont, strlen(cont));
		}
	}

	tmp = total_len - strlen(buf);
	while(tmp--)
		strcat(buf, " ");//fill

}

void produce_line(struct item_line *itl, char *outbuf)
{
	int tmp;
	memset(outbuf, 0, sizeof(outbuf));
	printf("++%d,%d,%d,%d, \n",__LINE__,
			sizeof(itl->hone ),
			sizeof(itl->hname),
			sizeof(itl->item1));
	fill_content(L1, L1, itl->hone, SP);
	printf("++###%d__%s__%s__%s__ \n", __LINE__, itl->hone, itl->hname, itl->item1);
#if 1
	fill_content(L2, L2, itl->hname, "nxxm");
	printf("++###%d__%s__%s__%s__ \n", __LINE__, itl->hone, itl->hname, itl->item1);
	fill_content(I1, I1, itl->item1, "itxx");
	printf("++###%d__%s__%s__%s__ \n", __LINE__, itl->hone, itl->hname, itl->item1);
#else
	strncat(itl->hname, "name", L2);
	printf("++###%d__%s__%s__%s__ \n", __LINE__, itl->hone, itl->hname, itl->item1);
	strncat(itl->item1, "value", I1);
	printf("++###%d__%s__%s__%s__ \n", __LINE__, itl->hone, itl->hname, itl->item1);
#endif
	printf("all___%s___\n",itl);

	printf("++###%d__%s__%s__%s__ \n", __LINE__, itl->hone, itl->hname, itl->item1);
	strcat(outbuf, itl->hone);
	strcat(outbuf, itl->hname);
	strcat(outbuf, itl->item1);
	printf("______%s____\n", outbuf);
	return ;
}

void main(void)
{
	struct item_line *itl = malloc(sizeof(struct item_line));
	memset(itl, 0, sizeof(struct item_line));
	char *outbufp = malloc(100 * sizeof(char));
	produce_line(itl, outbufp);


//	printf("12345678");
//	fflush(stdout);
//	sleep(1);
//	printf("\r");
//	MOVER(5);
//	printf("G");

	fflush(stdout);
	//printf("\n");
	return;
}



