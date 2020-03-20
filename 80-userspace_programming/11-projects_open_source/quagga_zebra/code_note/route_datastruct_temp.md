```c
// zebra/rib.h

/* Routing table instance.  */
struct zebra_vrf
{
	/* Identifier. */
	vrf_id_t vrf_id;

	/* Routing table name.  */
	char *name;

	/* Description.  */
	char *desc;

	/* FIB identifier.  */
	u_char fib_id;

	/* Routing table.  */
	struct route_table *table[AFI_MAX][SAFI_MAX];

	/* Static route configuration.  */
	struct route_table *stable[AFI_MAX][SAFI_MAX];

#ifdef HAVE_NETLINK
	struct nlsock netlink;     /* kernel messages */
	struct nlsock netlink_cmd; /* command channel */
	struct thread *t_netlink;
#endif

	/* 2nd pointer type used primarily to quell a warning on
	 * ALL_LIST_ELEMENTS_RO
	 */
	struct list _rid_all_sorted_list;
	struct list _rid_lo_sorted_list;
	struct list *rid_all_sorted_list;
	struct list *rid_lo_sorted_list;
	struct prefix rid_user_assigned;

#if defined (HAVE_RTADV)
	struct rtadv rtadv;
#endif /* HAVE_RTADV */

	/* Recursive Nexthop table */
	struct route_table *rnh_table[AFI_MAX];
};

// zebra_vty.c
struct route_table *table;
table = zebra_vrf_table (AFI_IP6, SAFI_UNICAST, vrf_id);
```



```c
// lib/table.h
// struct route_node rn = NULL;

/*
 * Macro that defines all fields in a route node.
 */
#define ROUTE_NODE_FIELDS				\
	/* Actual prefix of this radix. */            \
struct prefix p;                              \
\
/* Tree link. */                              \
struct route_table *table;                    \
struct route_node *parent;                    \
struct route_node *link[2];                   \
\
/* Lock of this radix */                      \
unsigned int lock;                            \
\
/* Each node of route. */                     \
void *info;                                   \
\
/* Aggregation. */                            \
void *aggregate;


/* Each routing entry. */
struct route_node
{
	ROUTE_NODE_FIELDS

#define l_left   link[0]
#define l_right  link[1]
};

```
