[source url](https://blog.csdn.net/flyingcys/article/details/57406346)
#### 1. Install

##### 1.1 Ubuntu
```
Server：sudo apt-get install tftpd-hpa
Client：sudo apt-get install tftp-hpa //optional
```
##### 1.2 CentOS
TODO : Solve problem - timed out
```
sudo yum install -y tftp-server
```

#### 2. Config

`vi /etc/default/tftpd-hpa`
1. “TFTP_DIRECTORY”为TFTP_Server服务目录
2. 修改“TFTP_ADDRESS”为0.0.0.0:69，表示所有IP源都可以访问
3. 修改“TFTP_OPTIONS”为“-l -c -s”
|||
|--|--|
|-l|以standalone/listen模式启动TFTP服务，而不是从xinetd启动|
|-c|可创建新文件。默认情况下TFTP只允许覆盖原有文件而不能创建新文件|
|-s|改变TFTP启动的根目录，加了-s后，客户端使用TFTP时，不再需要输入指定目录，填写文件的文件路径，而是使用配置文件中写好的目录|

#### service restart
`sudo service tftpd-hpd restart`

#### Client
`apt-get install busybox`
`busybox tftp A.B.C.D -pl 1.file`
