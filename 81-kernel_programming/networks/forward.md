
|InternetRouter---------.
			|
|Router A		|
|WAN:172.16.127.x-------(NAT**)
|WLAN:192.168.99.x ------.
			 |
|Router B		 |
|WWAN:192.168.99.x-------(NAT**)
|LAN:192.168.1.x--------.
			|
|PC			|
|WAN:192.168.1.x--------`


**: NAT or Static Route or Dynamic Route.

Forward Flow TODO
NONE:
PC[(gw)from192.168.1.x , to8.8.8.8] >
RouterB[(gw)from192.168.1.x , to8.8.8.8] >
RouterA[(gw)from192.168.1.x , to8.8.8.8] >
InternetRouter x(Local Packet)

RouterA-NAT, RouterB-NONE:
PC[(gw)from192.168.1.x , to8.8.8.8] >
RouterB[(gw)from192.168.1.x , to8.8.8.8] >
RouterA[(gw)from192.168.1.x , to8.8.8.8] >
InternetRouter >
RouterA[(gw)from8.8.8.8 , to192.168.1.x] >
InternetRouter ...

RouterA-NAT, RouterB-NAT:
PC[(gw)from192.168.1.x , to8.8.8.8] >
RouterB[(nat)from192.168.99.x , to8.8.8.8] >
RouterA[(nat)from172.16.127.x , to8.8.8.8] >
InternetRouter >
RouterA[(nat)from8.8.8.8 , to172.16.127.x] >
RouterB[(nat)from8.8.8.8 , to192.168.99.x] >
PC[(nat)from8.8.8.8 , to192.168.1.x]

RouterA-StaticRoute, RouterB-(Static)Route:
PC[(gw)from192.168.1.x , to8.8.8.8] >
RouterB[(gw)from192.168.1.x , to8.8.8.8] >
RouterA[(gw)from192.168.1.x , to8.8.8.8] >
InternetRouter >
RouterA[(gw)from8.8.8.8 , to192.168.1.x] >
RouterB[(gw)from8.8.8.8 , to192.168.1.x] >
PC[(gw)from8.8.8.8 , to192.168.1.x]

