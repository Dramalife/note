

##### CLI
./zebra/interface.c
```c
DEFUN (ipv6_address,
       ipv6_address_cmd,
       "ipv6 address X:X::X:X/M",
       "Interface IPv6 config commands\n"
       "Set the IP address of an interface\n"
       "IPv6 address (e.g. 3ffe:506::1/48)\n")
{
  return ipv6_address_install (vty, vty->index, argv[0], NULL, NULL, 0);
}
```

##### ipv6_address_install
./zebra/interface.c
```c
static int
ipv6_address_install (struct vty *vty, struct interface *ifp,
                      const char *addr_str, const char *peer_str,
                      const char *label, int secondary)
{
  struct zebra_if *if_data;
  struct prefix_ipv6 cp;
  struct connected *ifc;
  struct prefix_ipv6 *p;
  int ret;

  if_data = ifp->info;

  ret = str2prefix_ipv6 (addr_str, &cp);
  if (ret <= 0)
    {
      vty_out (vty, "%% Malformed address %s", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ifc = connected_check (ifp, (struct prefix *) &cp);
  if (! ifc)
    {
      ifc = connected_new ();
      ifc->ifp = ifp;

      /* Address. */
      p = prefix_ipv6_new ();
      *p = cp;
      ifc->address = (struct prefix *) p;

      /* Secondary. */
      if (secondary)
        SET_FLAG (ifc->flags, ZEBRA_IFA_SECONDARY);

      /* Label. */
      if (label)
        ifc->label = XSTRDUP (MTYPE_CONNECTED_LABEL, label);

      /* Add to linked list. */
      listnode_add (ifp->connected, ifc);
    }

  /* This address is configured from zebra. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED))
    SET_FLAG (ifc->conf, ZEBRA_IFC_CONFIGURED);

  /* In case of this route need to install kernel. */
  if (! CHECK_FLAG (ifc->conf, ZEBRA_IFC_QUEUED)
      && CHECK_FLAG (ifp->status, ZEBRA_INTERFACE_ACTIVE)
      && !(if_data && if_data->shutdown == IF_ZEBRA_SHUTDOWN_ON))
    {
      /* Some system need to up the interface to set IP address. */
      if (! if_is_up (ifp))
        {
          if_set_flags (ifp, IFF_UP | IFF_RUNNING);
          if_refresh (ifp);
        }

      ret = if_prefix_add_ipv6 (ifp, ifc);

      if (ret < 0)
        {
          vty_out (vty, "%% Can't set interface IP address: %s.%s",
                   safe_strerror(errno), VTY_NEWLINE);
          return CMD_WARNING;
        }

      SET_FLAG (ifc->conf, ZEBRA_IFC_QUEUED);
      /* The address will be advertised to zebra clients when the notification
       * from the kernel has been received. */
    }

  return CMD_SUCCESS;
}
```

zebra/ioctl.c
#####
```c
/* Interface's address add/delete functions. */
int
if_prefix_add_ipv6 (struct interface *ifp, struct connected *ifc)
{
  int ret;
  struct prefix_ipv6 *p;
  struct in6_ifreq ifreq;

  p = (struct prefix_ipv6 *) ifc->address;

  memset (&ifreq, 0, sizeof (struct in6_ifreq));

  memcpy (&ifreq.ifr6_addr, &p->prefix, sizeof (struct in6_addr));
  ifreq.ifr6_ifindex = ifp->ifindex;
  ifreq.ifr6_prefixlen = p->prefixlen;

  ret = if_ioctl_ipv6 (SIOCSIFADDR, (caddr_t) &ifreq);

  return ret;
}
```
