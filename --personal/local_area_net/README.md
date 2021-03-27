#### 组网

<img src="https://gitee.com/Dramalife/blog_note/raw/master/network/dl_local_net_pic/local_net.png" width="70%" height="70%" alt="图片名称" align=center />

##### 192.168.0.0/24网段

- BananaPi R2连接了一块2TB的机械硬盘，①通过samba和nfs服务提供NAS功能；
- BananaPi R1连接了一块500GB的硬盘，LAN测（172.16.1.0/24）也连接了设备，①提供NAS和Router功能；②LAN测设备运行了第三方内网穿透服务，用于在外网中访问；③防火墙阻止LAN测访问192.168.0/24网段，使BananaPi R2的NAS只直接暴露在内网中（如需在外网环境访问，需把BananaPi R1当作跳板）；

##### 172.16.1.0/24网段

- NanoPi M4性能较强，2核A72+4核A53，用于程序调试运行主力机 和 运行图形工具程序（时钟程序）；
- Orange Pi Zero主要用于运行内网穿透服务，搭载armv7架构处理器；



#### 实物图
总览  
<img src="https://gitee.com/Dramalife/blog_note/raw/master/network/dl_local_net_pic/overview_all.png" alt="overview" align=center />



ROC-RK3328-CC, Orange Pi Zero， RPI  
<img src="https://gitee.com/Dramalife/blog_note/raw/master/network/dl_local_net_pic/3328_zero_raspberry_0000.png" alt="3328_opi0_rpi2b" align=center />



BananaPi R2  
<img src="https://gitee.com/Dramalife/blog_note/raw/master/network/dl_local_net_pic/bpi_r2_0000.png" alt="BananaPi R2" align=center />



BananaPi R1  
<img src="https://gitee.com/Dramalife/blog_note/raw/master/network/dl_local_net_pic/bpi_ri_0000.png" alt="BananaPi R1" align=center />



NanoPi M4  
<img src="https://gitee.com/Dramalife/blog_note/raw/master/network/dl_local_net_pic/nanopi_m4_0000.png" alt="NanoPi M4" align=center />
