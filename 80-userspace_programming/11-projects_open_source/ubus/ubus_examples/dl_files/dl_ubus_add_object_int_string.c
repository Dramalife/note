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
	DLSET_ARG1,
	DLSET_ARG2,
	__DLSET_MAX
};

static const struct blobmsg_policy dlset_policy[__DLSET_MAX] = {
	[DLSET_ARG1] = { .name = "dlarg1", .type = BLOBMSG_TYPE_INT32 },
	[DLSET_ARG2] = { .name = "dlarg2", .type = BLOBMSG_TYPE_STRING },
};

#define DLBUFFLEN128	128
struct dlst
{
	uint32_t arg1;
	char arg2[DLBUFFLEN128];
}dldata;

static int test_dlset(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg)
{
	struct blob_attr *tb[__DLSET_MAX];
	char *s1;
	uint32_t num;

	blobmsg_parse(dlset_policy, __DLSET_MAX, tb, blob_data(msg), blob_len(msg));
	if (!tb[DLSET_ARG1] || !tb[DLSET_ARG2])
		return UBUS_STATUS_INVALID_ARGUMENT;

	num = blobmsg_get_u32(tb[DLSET_ARG1]);
	dldata.arg1 = num;/////
	s1 = blobmsg_get_string(tb[DLSET_ARG2]);
	strncpy(dldata.arg2, s1, DLBUFFLEN128);/////

	blob_buf_init(&b, 0);
	blobmsg_add_u32(&b, "rc", 1);
	ubus_send_reply(ctx, req, b.head);
#ifdef UBUS_SAMPLE_ADD_DRAMALIFE_SEND_EVENT
	ubus_send_event(ctx, __func__, b.head);
#endif

	return 0;
}

static int test_dlget(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg)
{
	/* Init buff */
	blob_buf_init(&b, 0);
	/* Data */
	blobmsg_add_u32(&b, "dlarg1", dldata.arg1);
	blobmsg_add_string(&b, "dlarg2", dldata.arg2);
	/* Send */
	ubus_send_reply(ctx, req, b.head);
	return 0;
}


DEF_UBUS_OBJ_RAMDOM(
		dl_obj,"dlobj",
		UBUS_METHOD_NOARG("dlget", test_dlget),
		UBUS_METHOD	 ("dlset", test_dlset, dlset_policy)
		);

int dl_add_ubus_object_int_string(struct ubus_context *ctx)
{
	int ret = 0;

	ret += ubus_add_object(ctx, &dl_obj);

	return ret;
};
