KDC : Key Distribution Center
AS  : Authentication Server
TGS : Ticket Granting Server
ST : service ticket
TGT: ticket granting ticket

KDC Clients : user & HTTP service

Kerberos realm
```
,_________________,
|KDC  |AS   ->TGT |
|     |-----------|
|     |TGS  ->ST  |
``````````````````'
 ^
 |
 |
 v
KDC-Clients {user, HTTP service}
```

```
usr ----- no TGT, no ST     ----> Service
usr ----- credential        ----> KDC-AS
usr <---- TGT, SK_TGS       ----- KDC-AS
usr ----- TGT               ----> KDC-TGS
usr <---- ST, SK_Service    ----- KDC-TGS
usr ----- ST, Authenticator ----> Service
```
