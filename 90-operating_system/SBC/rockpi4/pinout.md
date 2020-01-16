> \# note "rockpi4" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Source : [wiki.radxa.com](https://wiki.radxa.com),[page](https://wiki.radxa.com/Rockpi4/hardware/rockpi4#gpio)  
\#  
\# Init : 2019.09.15;  
\# Update   
\#  



<h2><span class="mw-headline" id="Processor">Processor</span></h2>
<p>The Rockchip RK3399 Soc used in ROCK Pi 4 includes 64bits hexa core processor with dual 1.8GHz Cortex-72 and qual 1.4GHz Cortex-A53, Mali T860MP4 graphics processing unit (GPU) and Internal SRAM. It has a level 1 (L1) cache and a level 2 (L2). For level 1 cache, 48KB Icache and 32KB Dcache is for each A72. 32KB Icache and 32KB Dcache is for each A53. For level 2 cache, 1024KB cache is for big cluster and 512KB cache is for little cluster.
</p>
<h2><span class="mw-headline" id="Networking">Networking</span></h2>
<p>On the ROCK Pi 4 Model A, B board, the Giga Bit Ethernet port is provided. From the test result, we know that the bandwidth is at least 939Mbits/sec. If you are interested in POE (Power Over Ethernet), you should try it on the Pi 4 board.
<br />The ROCK Pi 4 Model B is equipped with 2.4GHz 802.11 b/g/n and 5G ac/a WIFI. The Pi 4B also features Bluetooth 5.0.
</p>
<h2><span class="mw-headline" id="Peripherals">Peripherals</span></h2>
<p>The ROCK Pi 4 Model A and B have four USB-A connectors. One is for USB 3.0 OTG. One  is for 3.0 HOST. And the others are for USB 2.0 HOST. The hardware switch for host/device switch may be useful when you use the USB 3.0 OTG connector. The ROCK Pi 4 may be operated with any generic USB computer keyboard and mouse. It may also be used with USB storage, USB to MIDI converters, and virtually any other device/component with USB capabilities.
</p><p>The ROCK Pi 4 Model A and B are equipped with a standard 3.5mm jack. An audio lead is necessary to produce sound when there is not an HDMI cable. Audio can be played through speakers or headphones using jack. This requires you to use the Desktop volume control for configuration.
</p>
<h4><span class="mw-headline" id="MIPI_Camera_Interface">MIPI Camera Interface</span></h4>
<p>There is a wide range of camera applications in our lives. MIPI CSI 2 lane on board support 800 MP camera via FPC connector. 
</p><p>The MIPI CSI interface pin specification shows below.
</p>
<table class="wikitable">

<tr>
<th> Pin# </th>
<th> Name
</th></tr>
<tr>
<td> 1 </td>
<td> VCC_CAM
</td></tr>
<tr>
<td> 2 </td>
<td> I2C4_SDA
</td></tr>
<tr>
<td> 3 </td>
<td> I2C4_SCL
</td></tr>
<tr>
<td> 4 </td>
<td> CAM_MCLK
</td></tr>
<tr>
<td> 5 </td>
<td> CAM_GPIO1
</td></tr>
<tr>
<td> 6 </td>
<td> GND
</td></tr>
<tr>
<td> 7 </td>
<td> MIPI_RX0_CLKP
</td></tr>
<tr>
<td> 8 </td>
<td> MIPI_RX0_CLKN
</td></tr>
<tr>
<td> 9 </td>
<td> GND
</td></tr>
<tr>
<td> 10 </td>
<td> MIPI_RX0_D1P
</td></tr>
<tr>
<td> 11 </td>
<td> MIPI_RX0_D1N
</td></tr>
<tr>
<td> 12 </td>
<td> GND
</td></tr>
<tr>
<td> 13 </td>
<td> MIPI_RX0_D0P
</td></tr>
<tr>
<td> 14 </td>
<td> MIPI_RX0_D0P
</td></tr></table>
<h4><span class="mw-headline" id="MIPI_Display_Interface">MIPI Display Interface</span></h4>
<p>The ROCK Pi 4 Model A and B are equipped with one HDMI connector and one MIPI DSI. As for HDMI, the maximum resolution is 4k@60Hz. Any HDMI monitor should work as a display for the Pi 4. As for MIPI DSI, it is designed for raw LCD pannel. HDMI and MIPI DSI can work at the same time.
</p><p>The MIPI DSI interface pin specification shows below.
</p>
<table class="wikitable">

<tr>
<th> Pin# </th>
<th> Name
</th></tr>
<tr>
<td> 1 </td>
<td> VCC_MIPI
</td></tr>
<tr>
<td> 2 </td>
<td> VCC_MIPI
</td></tr>
<tr>
<td> 3 </td>
<td> GND
</td></tr>
<tr>
<td> 4 </td>
<td> I2C_SDA_AUDIO
</td></tr>
<tr>
<td> 5 </td>
<td> I2C_SCL_AUDIO
</td></tr>
<tr>
<td> 6 </td>
<td> GND
</td></tr>
<tr>
<td> 7 </td>
<td> MIPI_TX/RX_D0P
</td></tr>
<tr>
<td> 8 </td>
<td> MIPI_TX_RX_D0N
</td></tr>
<tr>
<td> 9 </td>
<td> GND
</td></tr>
<tr>
<td> 10 </td>
<td> MIPI_TX/RX_CLKP
</td></tr>
<tr>
<td> 11 </td>
<td> MIPI_TX_RX_CLKN
</td></tr>
<tr>
<td> 12 </td>
<td> GND
</td></tr>
<tr>
<td> 13 </td>
<td> MIPI_TX/RX_D1P
</td></tr>
<tr>
<td> 14 </td>
<td> MIPI_TX/RX_D1N
</td></tr>
<tr>
<td> 15 </td>
<td> GND
</td></tr></table>
<h4><span class="mw-headline" id="TF_Card_Interface">TF Card Interface</span></h4>
<p>The TF card can be used as a system storage or an external storage. When it's used as a system storage, you had better choose the ones with storage space larger than 8GB. When it's used as an external storage, you can choose the ones  with storage space up to 128GB. When the TF card is inserted into the TF card slot , the device will be automatically recognized by the system.
</p><p>The TF card interface pin specification shows below.
</p>
<table class="wikitable">

<tr>
<th> Pin# </th>
<th> Name
</th></tr>
<tr>
<td> 1 </td>
<td> SDMMC0_D2
</td></tr>
<tr>
<td> 2 </td>
<td> SDMMC0_D3
</td></tr>
<tr>
<td> 3 </td>
<td> SDMMC0_CMD
</td></tr>
<tr>
<td> 4 </td>
<td> VCC3V3_SYS
</td></tr>
<tr>
<td> 5 </td>
<td> SDMMC0_CLK
</td></tr>
<tr>
<td> 6 </td>
<td> GND
</td></tr>
<tr>
<td> 7 </td>
<td> SDMMC0_D0
</td></tr>
<tr>
<td> 8 </td>
<td> SDMMC0_D1
</td></tr>
<tr>
<td> 9 </td>
<td> SDMMC0_DET_L
</td></tr>
<tr>
<td> 10 </td>
<td> GND
</td></tr>
<tr>
<td> 11 </td>
<td> GND
</td></tr>
<tr>
<td> 12 </td>
<td> GND
</td></tr>
<tr>
<td> 13 </td>
<td> GND
</td></tr></table>
<h4><span class="mw-headline" id="eMMC_Socket_on_Board_Interface_Feature">eMMC Socket on Board Interface Feature</span></h4>
<p>The high performance eMMC module is the best choice as the system storage for ROCK Pi 4. The eMMC module with 8GB/16GB/32GB/64GB/128GB is available.
</p><p>The eMMC Socket pin specification shows below.
</p>
<table class="wikitable">

<tr>
<th> Name </th>
<th> Pin# </th>
<th> </th>
<th> Pin# </th>
<th> Name
</th></tr>
<tr>
<td> GND </td>
<td> 1 </td>
<td> </td>
<td> 34 </td>
<td> GND
</td></tr>
<tr>
<td> EMMC_D5 </td>
<td> 2 </td>
<td> </td>
<td> 33 </td>
<td> EMMC_D6
</td></tr>
<tr>
<td> GND </td>
<td> 3 </td>
<td> </td>
<td> 32 </td>
<td> GND
</td></tr>
<tr>
<td> EMMC_D4 </td>
<td> 4 </td>
<td> </td>
<td> 31 </td>
<td> EMMC_D7
</td></tr>
<tr>
<td> GND </td>
<td> 5 </td>
<td> </td>
<td> 30 </td>
<td> GND
</td></tr>
<tr>
<td> EMMC_D0 </td>
<td> 6 </td>
<td> </td>
<td> 29 </td>
<td> EMMC_D1
</td></tr>
<tr>
<td> GND </td>
<td> 7 </td>
<td> </td>
<td> 28 </td>
<td> GND
</td></tr>
<tr>
<td> EMMC_CLK </td>
<td> 8 </td>
<td> </td>
<td> 27 </td>
<td> EMMC_D2
</td></tr>
<tr>
<td> GND </td>
<td> 9 </td>
<td> </td>
<td> 26 </td>
<td> GND
</td></tr>
<tr>
<td> EMMC_D3 </td>
<td> 10 </td>
<td> </td>
<td> 25 </td>
<td> EMMC_CMD
</td></tr>
<tr>
<td> GND </td>
<td> 11 </td>
<td> </td>
<td> 24 </td>
<td> GND
</td></tr>
<tr>
<td> EMMC_RSTN </td>
<td> 12 </td>
<td> </td>
<td> 23 </td>
<td> VCC3V3_SYS
</td></tr>
<tr>
<td> GND </td>
<td> 13 </td>
<td> </td>
<td> 22 </td>
<td> VCC3V3_SYS
</td></tr>
<tr>
<td> GND </td>
<td> 14 </td>
<td> </td>
<td> 21 </td>
<td> VCC_1V8
</td></tr>
<tr>
<td> EMMC_RCLK </td>
<td> 15 </td>
<td> </td>
<td> 20 </td>
<td>  VCC_1V8
</td></tr>
<tr>
<td> GND </td>
<td> 16 </td>
<td> </td>
<td> 19 </td>
<td> GND
</td></tr>
<tr>
<td> GND </td>
<td> 17 </td>
<td> </td>
<td> 18 </td>
<td> GND
</td></tr></table>
<h4><span class="mw-headline" id="PCIE_M.2_MGFF_M-KEY_SOCKET_Interface">PCIE M.2 MGFF M-KEY SOCKET Interface</span></h4>
<p>On ROCK Pi 4 Model A and B board, M.2 connector supports up to 2T M2 NVME SSD.
</p><p>The PCIE M.2 interface pin specification shows below.
</p>
<table class="wikitable">

<tr>
<th> Name </th>
<th> Pin# </th>
<th> </th>
<th> Pin# </th>
<th> Name
</th></tr>
<tr>
<td> GND </td>
<td> 1 </td>
<td> </td>
<td> 2 </td>
<td> +3.3V
</td></tr>
<tr>
<td> GND </td>
<td> 3 </td>
<td> </td>
<td> 4 </td>
<td> +3.3V
</td></tr>
<tr>
<td> PERn3 </td>
<td> 5 </td>
<td> </td>
<td> 6 </td>
<td> NC
</td></tr>
<tr>
<td> PERp3 </td>
<td> 7 </td>
<td> </td>
<td> 8 </td>
<td> NC
</td></tr>
<tr>
<td> GND </td>
<td> 9 </td>
<td> </td>
<td> 10 </td>
<td> DAS/DSS#
</td></tr>
<tr>
<td> PETn3 </td>
<td> 11 </td>
<td> </td>
<td> 12 </td>
<td> +3.3V
</td></tr>
<tr>
<td> PETp3 </td>
<td> 13 </td>
<td> </td>
<td> 14 </td>
<td> +3.3V
</td></tr>
<tr>
<td> GND </td>
<td> 15 </td>
<td> </td>
<td> 16 </td>
<td> +3.3V
</td></tr>
<tr>
<td> PERn2 </td>
<td> 17 </td>
<td> </td>
<td> 18 </td>
<td> +3.3V
</td></tr>
<tr>
<td> PERp2 </td>
<td> 19 </td>
<td> </td>
<td> 20 </td>
<td> EMMC_CMD
</td></tr>
<tr>
<td> GND </td>
<td> 21 </td>
<td> </td>
<td> 22 </td>
<td> NC
</td></tr>
<tr>
<td> PETn2 </td>
<td> 23 </td>
<td> </td>
<td> 24 </td>
<td> NC
</td></tr>
<tr>
<td> PETp2 </td>
<td> 25 </td>
<td> </td>
<td> 26 </td>
<td> NC
</td></tr>
<tr>
<td> GND </td>
<td> 27 </td>
<td> </td>
<td> 28 </td>
<td> NC
</td></tr>
<tr>
<td> PERn1 </td>
<td> 29 </td>
<td> </td>
<td> 30 </td>
<td>  NC
</td></tr>
<tr>
<td> PERp1 </td>
<td> 31 </td>
<td> </td>
<td> 32 </td>
<td> NC
</td></tr>
<tr>
<td> GND </td>
<td> 33 </td>
<td> </td>
<td> 34 </td>
<td> NC
</td></tr>
<tr>
<td> PETn1 </td>
<td> 35 </td>
<td> </td>
<td> 36 </td>
<td> NC
</td></tr>
<tr>
<td> PETp1  </td>
<td> 37 </td>
<td> </td>
<td> 38 </td>
<td> DEVSLP
</td></tr>
<tr>
<td> GND </td>
<td> 39 </td>
<td> </td>
<td> 40 </td>
<td>  NC
</td></tr>
<tr>
<td> PERn0/SATA-B- </td>
<td> 41 </td>
<td> </td>
<td> 42 </td>
<td> NC
</td></tr>
<tr>
<td> PERp0/SATA-B+ </td>
<td> 43 </td>
<td> </td>
<td> 44 </td>
<td> NC
</td></tr>
<tr>
<td> GND </td>
<td> 45 </td>
<td> </td>
<td> 46 </td>
<td> NC
</td></tr>
<tr>
<td> PETn0/SATA-A- </td>
<td> 47 </td>
<td> </td>
<td> 48 </td>
<td> NC
</td></tr>
<tr>
<td> PETp0/SATA-A+ </td>
<td> 49 </td>
<td> </td>
<td> 50 </td>
<td>  PERST#
</td></tr>
<tr>
<td> GND </td>
<td> 51 </td>
<td> </td>
<td> 52 </td>
<td> CLKREQ#
</td></tr>
<tr>
<td> REFCLKN </td>
<td> 53 </td>
<td> </td>
<td> 54 </td>
<td> PEWake#
</td></tr>
<tr>
<td> REFCLKP </td>
<td> 55 </td>
<td> </td>
<td> 56 </td>
<td> NC
</td></tr>
<tr>
<td> GND </td>
<td> 57 </td>
<td> </td>
<td> 58 </td>
<td> NC
</td></tr>
<tr>
<td>  </td>
<td>  </td>
<td>  </td>
<td>  </td>
<td>
</td></tr>
<tr>
<td> NC </td>
<td> 67 </td>
<td> </td>
<td> 68 </td>
<td>  SUSCLK
</td></tr>
<tr>
<td> PEDET </td>
<td> 69 </td>
<td> </td>
<td> 70 </td>
<td> +3.3V
</td></tr>
<tr>
<td> GND </td>
<td> 71 </td>
<td> </td>
<td> 72 </td>
<td> +3.3V
</td></tr>
<tr>
<td> GND </td>
<td> 73 </td>
<td> </td>
<td> 74  </td>
<td> +3.3V
</td></tr>
<tr>
<td> GND </td>
<td> 75 </td>
<td> </td>
<td>  </td>
<td>
</td></tr></table>
<h4><span class="mw-headline" id="HDMI_Interface">HDMI Interface</span></h4>
<p>The ROCK Pi 4 Model A and B are equipped with one HDMI connector and one MIPI DSI. As for HDMI, the maximum resolution is 4k@60Hz. Any HDMI monitor should work as a display for the Pi 4. As for MIPI DSI, it is designed for raw LCD pannel. HDMI and MIPI DSI can work at the same time. 
</p><p>The HDMI interface pin specification shows below.
</p>
<table class="wikitable">

<tr>
<th> Pin# </th>
<th> Name
</th></tr>
<tr>
<td> 1 </td>
<td> HDMI_TX2P
</td></tr>
<tr>
<td> 2 </td>
<td> GND
</td></tr>
<tr>
<td> 3 </td>
<td> HDMI_TX2N
</td></tr>
<tr>
<td> 4 </td>
<td> HDMI_TX1P
</td></tr>
<tr>
<td> 5 </td>
<td> GND
</td></tr>
<tr>
<td> 6 </td>
<td> HDMI_TX1N
</td></tr>
<tr>
<td> 7 </td>
<td> HDMI_TX0P
</td></tr>
<tr>
<td> 8 </td>
<td> GND
</td></tr>
<tr>
<td> 9 </td>
<td> HDMI_TX0N
</td></tr>
<tr>
<td> 10 </td>
<td> HDMI_TXCP
</td></tr>
<tr>
<td> 11 </td>
<td> GND
</td></tr>
<tr>
<td> 12 </td>
<td> HDMI_TXCN
</td></tr>
<tr>
<td> 13 </td>
<td> PORT_CEC
</td></tr>
<tr>
<td> 14 </td>
<td> NC
</td></tr>
<tr>
<td> 15 </td>
<td> DDC_SCL
</td></tr>
<tr>
<td> 16 </td>
<td> DDC_SDA
</td></tr>
<tr>
<td> 17 </td>
<td> GND
</td></tr>
<tr>
<td> 18 </td>
<td> VCC5V0_HDMI
</td></tr>
<tr>
<td> 19 </td>
<td> HDMI_HPD
</td></tr></table>
<h2><span class="mw-headline" id="General_purpose_input-output_.28GPIO.29_connector"><span id="gpio">General purpose input-output (GPIO) connector</span></span></h2>
<p>ROCK Pi 4 has a 40-pin expansion header. Each pin is distinguished by color.
</p>
<table class="wikitable">
<tr>
<th> GPIO number </th>
<th> Function2 </th>
<th> Function1 </th>
<th>  GPIO </th>
<th>  Pin# </th>
<th> </th>
<th> Pin# </th>
<th> GPIO </th>
<th> Function1 </th>
<th> Function2 </th>
<th> GPIO number
</th></tr>
<tr>
<td> </td>
<td> </td>
<td> +3.3V </td>
<td>  </td>
<td style="background:yellow"> 1 </td>
<td>  </td>
<td style="background:red"> 2 </td>
<td>  </td>
<td> +5.0V </td>
<td>  </td>
<td>
</td></tr>
<tr>
<td> 71 </td>
<td> </td>
<td> I2C7_SDA </td>
<td> GPIO2_A7 </td>
<td style="background:green; color:white"> 3 </td>
<td> </td>
<td style="background:red"> 4 </td>
<td> </td>
<td> +5.0V </td>
<td>   </td>
<td>
</td></tr>
<tr>
<td> 72 </td>
<td> </td>
<td> I2C7_SCL </td>
<td> GPIO2_B0 </td>
<td style="background:green; color:white"> 5 </td>
<td> </td>
<td style="background:black; color:white"> 6 </td>
<td>  </td>
<td> GND </td>
<td>   </td>
<td>
</td></tr>
<tr>
<td> 75 </td>
<td> </td>
<td> SPI2_CLK </td>
<td> GPIO2_B3 </td>
<td style="background:green; color:white"> 7 </td>
<td> </td>
<td style="background:green; color:white"> 8 </td>
<td> GPIO4_C4 </td>
<td style="background:orange">DEBUG_TXD </td>
<td>   </td>
<td> 148
</td></tr>
<tr>
<td> </td>
<td> </td>
<td>  GND </td>
<td>  </td>
<td style="background:black; color:white"> 9 </td>
<td> </td>
<td style="background:green; color:white">10 </td>
<td> GPIO4_C3 </td>
<td style="background:orange">DEBUG_RXD </td>
<td>   </td>
<td> 147
</td></tr>
<tr>
<td>146  </td>
<td> </td>
<td>  PWM0 </td>
<td> GPIO4_C2 </td>
<td style="background:green; color:white">11 </td>
<td> </td>
<td style="background:green; color:white">12 </td>
<td> GPIO4_A3 </td>
<td> I2S1_SCLK </td>
<td>   </td>
<td> 131
</td></tr>
<tr>
<td> 150 </td>
<td> </td>
<td> PWM1 </td>
<td> GPIO4_C6 </td>
<td style="background:green; color:white">13 </td>
<td>  </td>
<td style="background:black; color:white">14 </td>
<td> </td>
<td> GND </td>
<td>   </td>
<td>
</td></tr>
<tr>
<td> 149 </td>
<td> </td>
<td> SPDIF_TX </td>
<td>  GPIO4_C5 </td>
<td style="background:green; color:white">15 </td>
<td> </td>
<td style="background:green; color:white">16 </td>
<td> GPIO4_D2 </td>
<td> </td>
<td>   </td>
<td> 154
</td></tr>
<tr>
<td> </td>
<td> </td>
<td>  +3.3V </td>
<td> </td>
<td style="background:yellow">17 </td>
<td> </td>
<td style="background:green; color:white">18 </td>
<td> GPIO4_D4 </td>
<td> </td>
<td>   </td>
<td> 156
</td></tr>
<tr>
<td>40 </td>
<td> UART4_TXD </td>
<td>  SPI1_TXD </td>
<td> GPIO1_B0 </td>
<td style="background:green; color:white">19 </td>
<td>  </td>
<td style="background:black; color:white">20 </td>
<td> </td>
<td> GND </td>
<td>   </td>
<td>
</td></tr>
<tr>
<td>15 </td>
<td> UART4_RXD </td>
<td> SPI1_RXD </td>
<td> GPIO1_A7  </td>
<td style="background:green; color:white">21  </td>
<td>   </td>
<td style="background:green; color:white">22  </td>
<td> GPIO4_D5  </td>
<td>   </td>
<td> </td>
<td> 157
</td></tr>
<tr>
<td>41 </td>
<td> </td>
<td>  SPI1_CLK </td>
<td> GPIO1_B1 </td>
<td style="background:green; color:white">23 </td>
<td>  </td>
<td style="background:green; color:white">24 </td>
<td> GPIO1_B2  </td>
<td> SPI1_CSn  </td>
<td>  </td>
<td> 42
</td></tr>
<tr>
<td> </td>
<td> </td>
<td>  GND  </td>
<td>  </td>
<td style="background:black; color:white">25  </td>
<td>   </td>
<td style="background:green; color:white">26 </td>
<td>  </td>
<td> ADC_IN0 </td>
<td>   </td>
<td>
</td></tr>
<tr>
<td> 64 </td>
<td> </td>
<td>  I2C2_SDA  </td>
<td> GPIO2_A0 </td>
<td style="background:blue; color:white">27  </td>
<td>  </td>
<td style="background:blue; color:white">28 </td>
<td> GPIO2_A1 </td>
<td> I2C2_CLK </td>
<td>  </td>
<td> 65
</td></tr>
<tr>
<td> 74 </td>
<td> I2C6_SCL </td>
<td>  SPI2_TXD  </td>
<td> GPIO2_B2 </td>
<td style="background:green; color:white">29  </td>
<td>  </td>
<td style="background:black; color:white">30 </td>
<td>  </td>
<td> GND </td>
<td>   </td>
<td>
</td></tr>
<tr>
<td> 73 </td>
<td> I2C6_SDA </td>
<td>  SPI2_RXD  </td>
<td> GPIO2_B1 </td>
<td style="background:green; color:white">31  </td>
<td>  </td>
<td style="background:green; color:white">32 </td>
<td> GPIO3_C0 </td>
<td> SPDIF_TX </td>
<td> UART3_CTSn </td>
<td> 112
</td></tr>
<tr>
<td> 76 </td>
<td> </td>
<td>   SPI2_CSn </td>
<td> GPIO2_B4 </td>
<td style="background:green; color:white">33  </td>
<td>  </td>
<td style="background:black; color:white">34 </td>
<td>  </td>
<td> GND </td>
<td>   </td>
<td>
</td></tr>
<tr>
<td> 133 </td>
<td> </td>
<td>   I2S1_LRCK_TX </td>
<td> GPIO4_A5 </td>
<td style="background:green; color:white">35  </td>
<td>  </td>
<td style="background:green; color:white">36 </td>
<td> GPIO4_A4 </td>
<td> I2S1_LRCK_RX </td>
<td>   </td>
<td> 132
</td></tr>
<tr>
<td> 158 </td>
<td> </td>
<td>   </td>
<td> GPIO4_D6 </td>
<td style="background:green; color:white">37  </td>
<td>  </td>
<td style="background:green; color:white">38 </td>
<td> GPIO4_A6 </td>
<td> I2S1_SDI </td>
<td>   </td>
<td> 134
</td></tr>
<tr>
<td> </td>
<td> </td>
<td>   GND </td>
<td>  </td>
<td style="background:black; color:white">39  </td>
<td>  </td>
<td style="background:green; color:white">40  </td>
<td> GPIO4_A7 </td>
<td> I2S1_SDO </td>
<td>   </td>
<td> 135
</td></tr></table>
<h4><span class="mw-headline" id="More_details_about_40-pin_Header">More details about 40-pin Header</span></h4>
<ul>
<li> Function marked with color orange is the default function of this pin. 
</li>
<li> Except Pins for power supply, all pins are laid out directly to Soc RK3399.
</li>
<li> For pin 3, 5, 27, 28, 29 and 31, each pin is connected to the 3.0V supply through a 4.7K pull-up resistor.
</li>
<li> Pin 19, 21, 23, 24 are laid out directly to the pins of SPI device on board.
</li>
<li> Pin 7 is laid out directly to the pin of MIPI CSI on board.
</li>
<li> For UART4-TXD/RXD
<ul>
<li> By testing, it supports a wide range of baud rate. It includes but not is not limited to the following baud rates. For instance, 115200bps. 500000bps, 1500000bps and so on.
</li>
</ul>
</li>
<li> For I2C-2 and I2C-7
<ul>
<li> We have do the test using the i2c device e2prom. We  need to open the i2c device file, and then do the read or write operation.
</li>
</ul>
</li>
</ul>

