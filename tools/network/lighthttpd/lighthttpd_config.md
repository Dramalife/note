>http://blog.chinaunix.net/uid-25266990-id-127946.html  
http://redmine.lighttpd.net/projects/lighttpd/wiki/IPv6-Config  


```diff
// /etc/lighttpd.conf
+ # listen to ipv6
+ $SERVER["socket"] == "[::]:80" {  }
```

