KDC : Key Distribution Center
AS  : Authentication Server
TGS : Ticket Granting Server
////////
ST : service ticket
TGT: ticket granting ticket
SK_TGS: Session Key of user and TGS

KDC Clients : user & HTTP service

Kerberos realm
```
,________________________,
|KDC  |AS   ->TGT(renew) |
|     |------------------|
|     |TGS  ->ST(service)|
`````````````````````````'
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
