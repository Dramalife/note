#! /bin/bash
#
# note 4g related
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

# Show driver
cat /proc/bus/usb/devices
# Show interrupt
cat /proc/interrupts
# Open AT port
busybox microcom -t 10000 /dev/ttyUSB2

# *power up?
# AT

# *radio on? 0:off, 1:on
# AT+CFUN?

# *pin status / input pin
# AT+CPIN?
#	AT+CPIN="1234"
# AT+QCPIN?

# *change pin
# AT+CPWD="SC","1234","6666"

# *inquire IMSI(sim exist / locked?)
# AT+CIMI

# *inquire signal strength
# AT+CCSQ
# AT^HDRCSQ
# AT+CSQ
#	+CSQ:RSSI,RSCP
#		RSSI:	{0,-113dBm}
#			{1,-111dBm}
#			{2~30,-109~-51dBm}
#			{31,>=-51dBm}*
#			{99,unknown}
#		RSCP:	{100,<=-116dBm}
#			{101,-115dBm}
#			{102~190,-114~-26dBm}
#			{191,>=-25dBm}*
#			{199,unknown}

# *search mode
# AT+MODODREX?
#	{5,LTE ONLY}

# *select operator
# AT+COPS?
# AT+COPS=?

# *
# AT+SYSINFO
#	^SYSINFO:2(service ok),3,0(no roam),2(CDMA),1(UIM ok)

#
# AT+CREG?
# AT+CEREG?
#	+CEREG:1,1(registed)

# *APN
# AT+CGDCONT

# *service mode
# AT+PSRAT
#	+PSRAT: EDGE/LTE FDD ...

# *Longsung
# AT+LCTCELLINFO
#	CURR_MODE	|当前制式			|
#	CELL_ID
#	LAC_ID
#	RSSI		|接收的信号强度指示		|
#	RSRP
#	RSRQ
#	SINR		|信号与干扰噪声比值，单位为dB	|	
#	BAND
#	CHANNEL
#	UE_CATEORY
#	PATHLOSS
#	SNR
#	DUPLEX MODE
#	CGI == 0 ,register failed.
# AT^RESET		(reset module)
# AT+MODODREX=5		(LTE ONLY)
# AT+LCTSW		(show software version)

