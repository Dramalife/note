## 0. Words

#### octets
a group of eight people or things, in particular.


## 1. MESSAGE

### 1.0 limits
(rfc2131 +555)
   The 'options' field is now variable length. A DHCP client must be
   prepared to receive DHCP messages with an 'options' field of at least
   length 312 octets.  This requirement implies that a DHCP client must
   be prepared to receive a message of up to **576** octets, the minimum IP
   datagram size an IP host must be prepared to accept [3].

### 1.1 format
```
(rfc2131 +455)
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     op (1)    |   htype (1)   |   hlen (1)    |   hops (1)    |
   +---------------+---------------+---------------+---------------+
   |                            xid (4)                            |
   +-------------------------------+-------------------------------+
   |           secs (2)            |           flags (2)           |
   +-------------------------------+-------------------------------+
   |                          ciaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          yiaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          siaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          giaddr  (4)                          |
   +---------------------------------------------------------------+
   |                                                               |
   |                          chaddr  (16)                         |
   |                                                               |
   |                                                               |
   +---------------------------------------------------------------+
   |                                                               |
   |                          sname   (64)                         |
   +---------------------------------------------------------------+
   |                                                               |
   |                          file    (128)                        |
   +---------------------------------------------------------------+
   |                                                               |
   |                          options (variable)                   |
   +---------------------------------------------------------------+

                  Figure 1:  Format of a DHCP message
```

### 1.2 fields
```
(rfc2131 +519)
   FIELD      OCTETS       DESCRIPTION
   -----      ------       -----------

   op            1  Message op code / message type.
                    1 = BOOTREQUEST, 2 = BOOTREPLY
   htype         1  Hardware address type, see ARP section in "Assigned
                    Numbers" rfc2131; e.g., '1' = 10mb ethernet.
   hlen          1  Hardware address length (e.g.  '6' for 10mb
                    ethernet).
   hops          1  Client sets to zero, optionally used by relay agents
                    when booting via a relay agent.
   xid           4  Transaction ID, a random number chosen by the
                    client, used by the client and server to associate
                    messages and responses between a client and a
                    server.
   secs          2  Filled in by client, seconds elapsed since client
                    began address acquisition or renewal process.
   flags         2  Flags (see figure 2).
   ciaddr        4  Client IP address; only filled in if client is in
                    BOUND, RENEW or REBINDING state and can respond
                    to ARP requests.
   yiaddr        4  'your' (client) IP address.
   siaddr        4  IP address of next server to use in bootstrap;
                    returned in DHCPOFFER, DHCPACK by server.
   giaddr        4  Relay agent IP address, used in booting via a
                    relay agent.
   chaddr       16  Client hardware address.
   sname        64  Optional server host name, null terminated string.
   file        128  Boot file name, null terminated string; "generic"
                    name or null in DHCPDISCOVER, fully qualified
                    directory-path name in DHCPOFFER.
   options     var  Optional parameters field.  See the options
                    documents for a list of defined options.

           Table 1:  Description of fields in a DHCP message
```
### 1.3 types
```
   Message         Use
   -------         ---

   DHCPDISCOVER -  Client broadcast to locate available servers.

   DHCPOFFER    -  Server to client in response to DHCPDISCOVER with
                   offer of configuration parameters.

   DHCPREQUEST  -  Client message to servers either (a) requesting
                   offered parameters from one server and implicitly
                   declining offers from all others, (b) confirming
                   correctness of previously allocated address after,
                   e.g., system reboot, or (c) extending the lease on a
                   particular network address.

   DHCPACK      -  Server to client with configuration parameters,
                   including committed network address.

   DHCPNAK      -  Server to client indicating client's notion of network
                   address is incorrect (e.g., client has moved to new
                   subnet) or client's lease as expired

   DHCPDECLINE  -  Client to server indicating network address is already
                   in use.

   DHCPRELEASE  -  Client to server relinquishing network address and
                   cancelling remaining lease.

   DHCPINFORM   -  Client to server, asking only for local configuration
                   parameters; client already has externally configured
                   network address.

                          Table 2:  DHCP messages
```

### 1.4 alloacting address
```
                Server          Client          Server
            (not selected)                    (selected)

                  v               v               v
                  |               |               |
                  |     Begins initialization     |
                  |               |               |
                  | _____________/|\____________  |
                  |/DHCPDISCOVER | DHCPDISCOVER  \|
                  |               |               |
              Determines          |          Determines
             configuration        |         configuration
                  |               |               |
                  |\             |  ____________/ |
                  | \________    | /DHCPOFFER     |
                  | DHCPOFFER\   |/               |
                  |           \  |                |
                  |       Collects replies        |
                  |             \|                |
                  |     Selects configuration     |
                  |               |               |
                  | _____________/|\____________  |
                  |/ DHCPREQUEST  |  DHCPREQUEST\ |
                  |               |               |
                  |               |     Commits configuration
                  |               |               |
                  |               | _____________/|
                  |               |/ DHCPACK      |
                  |               |               |
                  |    Initialization complete    |
                  |               |               |
                  .               .               .
                  .               .               .
                  |               |               |
                  |      Graceful shutdown        |
                  |               |               |
                  |               |\ ____________ |
                  |               | DHCPRELEASE  \|
                  |               |               |
                  |               |        Discards lease
                  |               |               |
                  v               v               v
     Figure 3: Timeline diagram of messages exchanged between DHCP
               client and servers when allocating a new network address
```
### 1.5 reusing address
```
(rfc2131 +973)
                Server          Client          Server

                  v               v               v
                  |                |               |
                  |              Begins            |
                  |          initialization        |
                  |                |               |
                  |                /|\             |
                  |   _________ __/ | \__________  |
                  | /DHCPREQU EST  |  DHCPREQUEST\ |
                  |/               |              \|
                  |                |               |
               Locates             |            Locates
            configuration          |         configuration
                  |                |               |
                  |\               |              /|
                  | \              |  ___________/ |
                  |  \             | /  DHCPACK    |
                  |   \ _______    |/              |
                  |     DHCPACK\   |               |
                  |          Initialization        |
                  |             complete           |
                  |               \|               |
                  |                |               |
                  |           (Subsequent          |
                  |             DHCPACKS           |
                  |             ignored)           |
                  |                |               |
                  |                |               |
                  v                v               v

     Figure 4: Timeline diagram of messages exchanged between DHCP
               client and servers when reusing a previously allocated
               network address
```

### 1.6 message fields - server

```
(rfc2131 +1537)
Field      DHCPOFFER            DHCPACK             DHCPNAK
-----      ---------            -------             -------
'op'       BOOTREPLY            BOOTREPLY           BOOTREPLY
'htype'    (From "Assigned Numbers" rfc2131)
'hlen'     (Hardware address length in octets)
'hops'     0                    0                   0
'xid'      'xid' from client    'xid' from client   'xid' from client
           DHCPDISCOVER         DHCPREQUEST         DHCPREQUEST
           message              message             message
'secs'     0                    0                   0
'ciaddr'   0                    'ciaddr' from       0
                                DHCPREQUEST or 0
'yiaddr'   IP address offered   IP address          0
           to client            assigned to client
'siaddr'   IP address of next   IP address of next  0
           bootstrap server     bootstrap server
'flags'    'flags' from         'flags' from        'flags' from
           client DHCPDISCOVER  client DHCPREQUEST  client DHCPREQUEST
           message              message             message
'giaddr'   'giaddr' from        'giaddr' from       'giaddr' from
           client DHCPDISCOVER  client DHCPREQUEST  client DHCPREQUEST
           message              message             message
'chaddr'   'chaddr' from        'chaddr' from       'chaddr' from
           client DHCPDISCOVER  client DHCPREQUEST  client DHCPREQUEST
           message              message             message
'sname'    Server host name     Server host name    (unused)
           or options           or options
'file'     Client boot file     Client boot file    (unused)
           name or options      name or options
'options'  options              options


Option                    DHCPOFFER    DHCPACK            DHCPNAK
------                    ---------    -------            -------
Requested IP address      MUST NOT     MUST NOT           MUST NOT
IP address lease time     MUST         MUST (DHCPREQUEST) MUST NOT
                                       MUST NOT (DHCPINFORM)
Use 'file'/'sname' fields MAY          MAY                MUST NOT
DHCP message type         DHCPOFFER    DHCPACK            DHCPNAK
Parameter request list    MUST NOT     MUST NOT           MUST NOT
Message                   SHOULD       SHOULD             SHOULD
Client identifier         MUST NOT     MUST NOT           MAY
Vendor class identifier   MAY          MAY                MAY
Server identifier         MUST         MUST               MUST
Maximum message size      MUST NOT     MUST NOT           MUST NOT
All others                MAY          MAY                MUST NOT

           Table 3:  Fields and options used by DHCP servers
```
### 1.7 states -client

```
   ---------------------------------------------------------------------
   |              |INIT-REBOOT  |SELECTING    |RENEWING     |REBINDING |
   ---------------------------------------------------------------------
   |broad/unicast |broadcast    |broadcast    |unicast      |broadcast |
   |server-ip     |MUST NOT     |MUST         |MUST NOT     |MUST NOT  |
   |requested-ip  |MUST         |MUST         |MUST NOT     |MUST NOT  |
   |ciaddr        |zero         |zero         |IP address   |IP address|
   ---------------------------------------------------------------------

              Table 4: Client messages from different states
```
### 1.8 message fields - client

```
(rfc2131 +2023)
Field      DHCPDISCOVER          DHCPREQUEST           DHCPDECLINE,
           DHCPINFORM                                  DHCPRELEASE
-----      ------------          -----------           -----------
'op'       BOOTREQUEST           BOOTREQUEST           BOOTREQUEST
'htype'    (From "Assigned Numbers" rfc2131)
'hlen'     (Hardware address length in octets)
'hops'     0                     0                     0
'xid'      selected by client    'xid' from server     selected by
                                 DHCPOFFER message     client
'secs'     0 or seconds since    0 or seconds since    0
           DHCP process started  DHCP process started
'flags'    Set 'BROADCAST'       Set 'BROADCAST'       0
           flag if client        flag if client
           requires broadcast    requires broadcast
           reply                 reply
'ciaddr'   0 (DHCPDISCOVER)      0 or client's         0 (DHCPDECLINE)
           client's              network address       client's network
           network address       (BOUND/RENEW/REBIND)  address
           (DHCPINFORM)                                (DHCPRELEASE)
'yiaddr'   0                     0                     0
'siaddr'   0                     0                     0
'giaddr'   0                     0                     0
'chaddr'   client's hardware     client's hardware     client's hardware
           address               address               address
'sname'    options, if           options, if           (unused)
           indicated in          indicated in
           'sname/file'          'sname/file'
           option; otherwise     option; otherwise
           unused                unused
'file'     options, if           options, if           (unused)
           indicated in          indicated in
           'sname/file'          'sname/file'
           option; otherwise     option; otherwise
           unused                unused
'options'  options               options               (unused)



Option                     DHCPDISCOVER  DHCPREQUEST      DHCPDECLINE,
                           DHCPINFORM                     DHCPRELEASE
------                     ------------  -----------      -----------
Requested IP address       MAY           MUST (in         MUST
                           (DISCOVER)    SELECTING or     (DHCPDECLINE),
                           MUST NOT      INIT-REBOOT)     MUST NOT
                           (INFORM)      MUST NOT (in     (DHCPRELEASE)
                                         BOUND or
                                         RENEWING)
IP address lease time      MAY           MAY              MUST NOT
                           (DISCOVER)
                           MUST NOT
                           (INFORM)
Use 'file'/'sname' fields  MAY           MAY              MAY
DHCP message type          DHCPDISCOVER/ DHCPREQUEST      DHCPDECLINE/
                           DHCPINFORM                     DHCPRELEASE
Client identifier          MAY           MAY              MAY
Vendor class identifier    MAY           MAY              MUST NOT
Server identifier          MUST NOT      MUST (after      MUST
                                         SELECTING)
                                         MUST NOT (after
                                         INIT-REBOOT,
                                         BOUND, RENEWING
                                         or REBINDING)
Parameter request list     MAY           MAY              MUST NOT
Maximum message size       MAY           MAY              MUST NOT
Message                    SHOULD NOT    SHOULD NOT       SHOULD
Site-specific              MAY           MAY              MUST NOT
All others                 MAY           MAY              MUST NOT

             Table 5:  Fields and options used by DHCP clients
```

