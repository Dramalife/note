#include "zpi.h"

int zpi_pack2buff()
{
}

static int check_transport_type(int t1, int t2)
{
	int ret = 0;

	if( t1==t2 )
	{
		ret = 0;
	}
	else
	{
		dprintf(2, "[%s,%d] ERROR : ZNP Frame!\n", __func__,__LINE__);
		ret = 1;
	}
	return ret;
}
static int check_general_len(struct zpi_frame_general *gen)
{
	int ret = 0;

	if( gen->len>=0 && gen->len<=250 )
	{
		ret = 0;
	}
	else
	{
		dprintf(2, "[%s,%d] ERROR : ZNP Frame!\n", __func__,__LINE__);
		ret = 1;
	}

	return ret;
}
static int check_general_cmd(struct zpi_frame_general *gen)
{
	int ret = 0;
	uint8_t cmd_type, cmd_sub;

	cmd_type = gen->cmd[0] >> 5;
	cmd_sub = gen->cmd[0] & 0x1f;

	if( cmd_type >= CMD_TYPE_MAX__ )
	{
		dprintf(2, "[%s,%d] ERROR : ZNP Frame!\n", __func__,__LINE__);
		ret+=__LINE__;
	}
	if( cmd_sub >= CMD_SUB_MAX__ )
	{
		dprintf(2, "[%s,%d] ERROR : ZNP Frame!\n", __func__,__LINE__);
		ret+=__LINE__;
	}

	return ret;
}
static int check_transport_fcs(struct zpi_frame_st *st)
{
	int ret = 0;
	uint8_t cacun;
	uint8_t len = 0;
	char *gen = NULL;

	st->fcs = st->fix 
		+ sizeof(st->fix->sof)
		+ sizeof(st->fix->gen.len)
		+ sizeof(st->fix->gen.cmd)
		+ st->fix->gen.len ;

	len = st->fix->gen.len;
	gen = &st->fix->gen;

	while(len--)
	{
		cacun ^= *gen++;
	}

	if( cacun == st->fcs )
	{
		ret = 0;
	}
	else
	{
		dprintf(2, "[%s,%d] ERROR : ZNP Frame!\n", __func__,__LINE__);
		ret = -1;
	}

	return ret;
}

int zpi_unpack2st(const char *buff, struct zpi_frame_st *st)
{
	char tmp[] = {0xfe};
	buff = tmp;

	st->fix = (struct zpi_transport_uart *)buff;

	/* Check Frame */
	if( 0
			|| check_transport_type(ZPI_FRAME_UART_SOF, st->fix->sof) 
			|| check_general_len(&st->fix->gen)
			|| check_general_cmd(&st->fix->gen)
			|| check_transport_fcs(st)
	  )
	{
		return -1;
	}




}


int uart_general_transport()
{
}
