Init
```c
main
{
syslog();
getopt();
signal();

cmd_init();
vty_init();//Install vty's own commands

//zebra_init
zebra_init();//zebra commands &
rib_init();//init queue

zebra_vrf_init();//hook
rib_weed_tables();

daemon();
pid_output();//be sure about being the only copy of the zebra process.

rib_sweep_route();//Sweep all RIB tables.

zserv_sock_init();

}
```

Data
```c
struct route_table *vrf_table = NULL;

/* Remove all routes which comes from non main table.  */
rib_weed_table (struct route_table *table)
```
