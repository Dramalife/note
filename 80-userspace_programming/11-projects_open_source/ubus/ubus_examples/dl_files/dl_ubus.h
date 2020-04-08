/*****************/
#define DEF_UBUS_OBJ(vobj,vobj_type,vobj_methods,vname,...);\
static const struct ubus_method vobj_methods[] = \
{\
	__VA_ARGS__\
};\
static struct ubus_object_type vobj_type =\
UBUS_OBJECT_TYPE(vname, vobj_methods);\
static struct ubus_object vobj = {\
	.name = vname,\
	.type = &vobj_type,\
	.methods = vobj_methods,\
	.n_methods = ARRAY_SIZE(vobj_methods),\
};
/*****************/
#define DEF_UBUS_OBJ_RAMDOM(vobj,vname,...);\
static const struct ubus_method vobj##_methods[] = \
{\
	__VA_ARGS__\
};\
static struct ubus_object_type vobj##_type =\
UBUS_OBJECT_TYPE(vname, vobj##_methods);\
static struct ubus_object vobj = {\
	.name = vname,\
	.type = &vobj##_type,\
	.methods = vobj##_methods,\
	.n_methods = ARRAY_SIZE(vobj##_methods),\
};
