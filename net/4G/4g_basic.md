driver\(interface\)\
dial\(AT command\)

### 模组
||||
|--|--|--|
|0|物理接口|Mini PCI-E 52PIN|
|1|bus|PCI-E|
|2|模组实现网络接口|ECM:USB实现网络接口卡\(NIC\)|
|3|USB和总线的关系|PCI-E中包含USB差分信号DN、DP,还包含SIM卡接口，UART接口【参考：阿乐卡文档】|
#### [USB中典型类及子类](https://blog.csdn.net/weijory/article/details/75570597)
|类别|解释|子类|典型应用|IC芯片|
|UVC|视频类||免驱USB摄像头||
|CDC|通讯类|RNDIS|||
||||ECM\(p24\)|免驱USB网卡|RTL8152B|
|||EEM|||

#### [PCI-Express](https://baike.baidu.com/item/PCI-Express)(peripheral component interconnect express)是一种高速串行计算机扩展总线标准

#### MZ393-模组

MZ393在 Linux上可以通过两种方式进行拨号上网。
一种是 PPP 拨号上网，另一种是 ECM 方式拨号上网。 ECM 可以看成是在 USB 接口上
实现网络接口卡（ NIC, Network InterfaceCard）功能的不同协议规范。

MZ393 模块的 USB 口被映射为多个接口，在 Linux 系统下的端口如下表所示：

|接口号|0|1\(1\)|2|3|4|
|--|--|--|--|--|--|
|功能|ECM|\/|AT|Modem|Log|
|Linux 对应设备\(2\)|eth1|ttyUSB0|ttyUSB1|ttyUSB2|

**注1：** 端口 1 本质上是 ECM 端口的一部分，不要对该端口进行单独的操作。
**注2：** 不同平台生成的设备文件可能会有差异。

#### MZ393 PCIE PIN 脚定义
|管脚号|管脚号名称|描述|I/O|说明|
|--|--|--|--|--|
|1|AP2CP_WAKE|主机唤醒模块功能信号|I|/|
2|VDD_PCIE|DC 3.8V|P|范围为： 3.2V~4.2V
3|CP2AP_WAKE|模块唤醒主机功能信号|/|/
4|GND|地|/|/
5|NC|/|/|/
6|NC|/|/|/
7|NC|/|/|/
8|VSIM_1V8_3V0|SIM/USIM 卡电源|P|DC 1.8V/3.0V
9|GND|地|/|/
10|SIM_DATA|SIM/USIM 卡数据信号|B|/
11|NC|/|/|/
12|SIM_CLK|SIM/USIM 卡时钟信号|O|/
13|NC|/|/|/
14|SIM_RST|SIM/USIM 卡复位信号|O|/
15|GND|地|/|/
16|NC|/|/|/
17|NC|/|/|/
18|GND|地|/|/
19|NC|/|/|/
20|NC|||
21|GND|地|/|/
22|NC|/|I|/
23|AP2CP_SLEEP|主机休眠状态指示|/|/
24|VDD_PCIE|DC 3.8V|P|范围为： 3.2V~4.2V
25|CP2AP_SLEEP|模块休眠状态指示|/|/
26|GND|地|/|/
27|GND|地|/|/
28|NC|NC|/|/
29|GND|地|/|/
30|NC|/|/|/
31|NC|/|/|/
32|NC|/|/|/
33|NC|/|/|/
34|GND|地|/|/
35|GND|地|/|/
36|USB_D-|USB 差分信号 DN|B|USB2.0
37|GND|地|/|/
38|USB_D+|USB 差分信号 DP|B|USB2.0
39|VDD_PCIE|DC 3.8V|P|范围为： 3.2V~4.2V
40|GND|地|/|/
41|VDD_PCIE|DC 3.8V|P|范围为： 3.2V~4.2V
42|NC|/|/|/
43|GND|地|/|/
44|NC|/|/|/
45|NC|/|/|/
46|NC|/|/|/
47|NC|/|/|/
48|NC|/|/|/
49|CP_UART_TXD|模块串口发射|O
50|GND|地|/|/
51|CP_UART_RXD|模块串口接收|I
52|VDD_PCIE|DC 3.8V|P|范围为： 3.2V~4.2V
