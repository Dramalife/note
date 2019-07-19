#! /bin/bash
#
# note network tcpdump related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
#
# -xx    When parsing and printing, in addition to printing the headers of
# 	 each packet, print the data of each packet, including its link level
# 	 header, in hex.
#
# -v     When parsing and printing, produce (slightly more) verbose output.
#	 For example, the time to live, identification, total length and options
#	 in an IP packet are printed.  Also enables additional packet integrity
#	 checks such as  verifying  the  IP and ICMP header checksum.1
# 	 When writing to a file with the-w option, report, every 10seconds, the
# 	 number of packetscaptured.
#
# -n     Don't convert addresses (i.e., host addresses, port numbers, etc.) to
#	 names.
#	 {Don't convert host address to names.}
# -nn	 {数字的方式显示IP和端口。一个n是ip}
#	 {Don't convert host address and port numbers to names.}

sudo tcpdump -i $1 -nn -xx -v -w $2

