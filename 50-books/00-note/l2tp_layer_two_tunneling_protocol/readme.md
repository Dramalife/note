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
[Install](./xl2tpd_install.htm)  
[Use](./xl2tpd_USE_config_sample.md)  

```bash
./xl2tpd -c ~/note/l2tpd.conf_LNS_dramalife -s ~/note/chapsecrets.sample_dramalife -D
```
  
##### 2.2 Configuration  
[configuration-sample-chapsecrets](./chapsecrets.sample_dramalife)     
[configuration-sample-l2tpd.conf](./l2tpd.conf_LNS_dramalife)     
[But error occured, But resolved ;) ](./error_lns_CDN.md)  
  
##### 2.3 Protocol Message  
[l2tp message](./l2tp_message.md)  
  
#### 3. TODO  
  
internals     
  
#### 4. DOCs

```bash
:~/xl2tpd $ grep "rfc" . -rn
./doc/xl2tpd.conf.5:121:more information about hidden AVP's and AVP in general, refer to rfc2661    
./doc/README.patents:43:The L2TP became an IETF standard, see http://www.ietf.org/rfc/rfc2661.txt    
```

