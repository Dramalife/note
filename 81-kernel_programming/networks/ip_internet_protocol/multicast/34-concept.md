[ref1 - 组播_百度百科](https://www.baidu.com/link?url=CNFr-_ZcbEBN_ZJCw-1ThB-e-LEV5Z8q776bIhDHYlhBj4WmcoyF_SUq8eunvM84Wsi9PR3KdkSTYMufQId8SSoyjqtDohuQ4ZPBPEHnzNe&wd=&eqid=e07d8df80000c8dc000000025ddde2c5)

#  Multicast （组播/多播）

 在发送和接收者实现点对多点连接 



## 体系结构
​	组播协议分为主机-路由器之间的**组成员关系协议**和路由器-路由器之间的**组播路由协议**。
​	组成员关系协议包括IGMP（互连网组管理协议）。
​	组播路由协议分为域内组播路由协议及域间组播路由协议。域内组播路由协议包括PIM-SM、PIM-DM、DVMRP等协议，域间组播路由协议包括MBGP、MSDP等协议。
​	同时为了有效抑制组播数据在链路层的扩散，引入了IGMP Snooping、CGMP等二层组播协议。对组播的技术历史作出了巨大的贡献！

IGMP建立并且维护路由器直联网段的组成员关系信息。域内组播路由协议根据IGMP维护的这些组播组成员关系信息，运用一定的组播路由算法构造组播分发树进行组播数据包转发。域间组播路由协议在各自治域间发布具有组播能力的路由信息以及组播源信息，以使组播数据在域间进行转发。





