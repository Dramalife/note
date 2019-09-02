#### 1.
 _______________
| IP   		|
|---------------|
| PPP  		|
|---------------|
| L2TP*		|
|---------------|
| UDP(1701)  	|
|---------------|
| IP   		|
|---------------|
| L2/L1		|
````````````````

#### 2  
  
##### 2.1 Install & Use  

[Install](/50-books/00-note/l2tp_layer_two_tunneling_protocol/xl2tpd_install.htm)  
[Use](/50-books/00-note/l2tp_layer_two_tunneling_protocol/xl2tpd_USE_config_sample.md)  

```bash
/50-books/00-note/l2tp_layer_two_tunneling_protocol/xl2tpd -c ~/note/l2tpd.conf_LNS_dramalife -s ~/note/chapsecrets.sample_dramalife -D
```
  
##### 2.2 Configuration  

[configuration-sample-chapsecrets](/50-books/00-note/l2tp_layer_two_tunneling_protocol/sample_config/chapsecrets.sample_dramalife)     
[configuration-sample-l2tpd.conf](/50-books/00-note/l2tp_layer_two_tunneling_protocol/sample_config/l2tpd.conf_LNS_dramalife)     
[But error occured, But resolved ;) ](/50-books/00-note/l2tp_layer_two_tunneling_protocol/error_LNS_send_CDN_after_Tunnel_and_Session_establish.md)  
  
##### 2.3 Protocol Message  

[l2tp message](/50-books/00-note/l2tp_layer_two_tunneling_protocol/l2tp_message.md)  
  

#### 3. TODO  
  
internals     
  

#### 4. DOCs

```bash
:~/xl2tpd $ grep "rfc" . -rn
./doc/xl2tpd.conf.5:121:more information about hidden AVP's and AVP in general, refer to rfc2661    
./doc/README.patents:43:The L2TP became an IETF standard, see http://www.ietf.org/rfc/rfc2661.txt    
```

