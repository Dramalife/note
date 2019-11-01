# internal : NETLINK_AUDIT

# auditd - The Linux Audit daemon
# auditctl - a utility to assist controlling the kernel's audit system
# ausearch - a tool to query audit daemon logs

# assist controlling the kernel's audit system
sudo auditctl -w /PATH/TO/FILE -p rwax -k YOURKEY

# query audit daemon logs
sudo ausearch -k YOURKEY
