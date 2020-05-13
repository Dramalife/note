/*
 * Init : 2020.04.08
 *	GET,SET:int,string;
 * Update: 2020.04.08
 *	Ref : https://blog.csdn.net/sky619351517/article/details/80726757
 *	Add : blob parse array(better way);
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
enum{
	ARRAY_MEM1,
	ARRAY_MEM2,
	__ARRAY_MEM_MAX,
};

static const struct blobmsg_policy dlsetarray_policy[__DLSET_MAX] = {
	[DLSET_ARRAY] = { .name = "array1", .type = BLOBMSG_TYPE_ARRAY },
};
static const struct blobmsg_policy array_member_policy[__ARRAY_MEM_MAX] = {
	[ARRAY_MEM1] = { .type = BLOBMSG_TYPE_STRING },
	[ARRAY_MEM2] = { .type = BLOBMSG_TYPE_STRING },
};

#define DLBUFFLEN128	128
struct dlst
{
	char arr[2][DLBUFFLEN128];
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
#if 0
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
#else
	/* Parse & Set data 
	 * Better way !
	 */
	struct blob_attr *member[__ARRAY_MEM_MAX];
	blobmsg_parse_array(array_member_policy, __ARRAY_MEM_MAX, member, blobmsg_data(tb[DLSET_ARRAY]), blob_len(tb[DLSET_ARRAY]));
	strncpy(dldata.arr[0],blobmsg_get_string(member[ARRAY_MEM1]), DLBUFFLEN128); 
	strncpy(dldata.arr[1],blobmsg_get_string(member[ARRAY_MEM2]), DLBUFFLEN128); 
#endif
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
