/*
 * Init : 2020.04.08
 *	GET,SET:int,string;
 * Update:
 *
 */


#include <unistd.h>
#include <signal.h>
#include <libubox/blobmsg_json.h>
#include "libubus.h"
#include "dl_ubus.h"


/* VARIABLES - STATIC*/
static struct blob_buf b;

enum{
	DLSET_ARRAY,
	__DLSET_MAX
};

static const struct blobmsg_policy dlsetarray_policy[__DLSET_MAX] = {
	[DLSET_ARRAY] = { .name = "array1", .type = BLOBMSG_TYPE_ARRAY },
};

#define DLBUFFLEN128	128
struct dlst
{
	uint32_t arr[2][DLBUFFLEN128];
}dldata;

static int test_dlset_array(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg)
{
	struct blob_attr *tb[__DLSET_MAX];
	char *s1;
	uint32_t num;

	blobmsg_parse(dlsetarray_policy, __DLSET_MAX, tb, blob_data(msg), blob_len(msg));
	if (0/*below*/
	||!tb[DLSET_ARRAY]
	)
		return UBUS_STATUS_INVALID_ARGUMENT;
	/* Init buff */
	blob_buf_init(&b, 0);
	/* Parse & Set data */
	struct blob_attr *attr = NULL;
	size_t len = 0;
	size_t index = 0;
	blobmsg_for_each_attr(attr, tb[DLSET_ARRAY], len)
	{
		if(blobmsg_type(attr) != BLOBMSG_TYPE_STRING)
			continue;
		strncpy(dldata.arr[index], blobmsg_data(attr), DLBUFFLEN128);
		index++;
		if(index >= 2)
			break;
	}
	/* Send */
	ubus_send_reply(ctx, req, b.head);

	return 0;
}

static int test_dlget_array(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg)
{
	/* Init buff */
	blob_buf_init(&b, 0);
	/* Data */
	void *a = blobmsg_open_array(&b, "array1");
	int index = 0;
	for(index = 0; index < 2; index++)
	{
		blobmsg_add_string(&b, "", dldata.arr[index]);
	}
	blobmsg_close_array(&b, a);
	/* Send */
	ubus_send_reply(ctx, req, b.head);
	return 0;
}


DEF_UBUS_OBJ_RAMDOM(
		dl_obj,"dlobj.array",
		UBUS_METHOD_NOARG("dlgetarray", test_dlget_array),
		UBUS_METHOD	 ("dlsetarray", test_dlset_array, dlsetarray_policy)
		);

int dl_add_ubus_object_array(struct ubus_context *ctx)
{
	int ret = 0;

	ret += ubus_add_object(ctx, &dl_obj);

	return ret;
};
