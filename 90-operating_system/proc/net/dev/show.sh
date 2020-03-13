#! /bin/bash
#
# Init : 2020.03.13
# Update

# proc(5)
#
#The dev pseudo-file contains network device status information.  This gives the number of received and sent packets, the number of errors and
#collisions and other basic statistics.  These are used by the ifconfig(8) program to report device status.  The format is:

cat /proc/net/dev

#Sample
#
#Inter-|   Receive                                                |  Transmit
# face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
#enp0s3: 1242864498 9611117    0 605009    0     0          0     39944 231125269 1346844    0    0    0     0       0          0
#enp0s8:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
#    lo: 1391306   19097    0    0    0     0          0         0  1391306   19097    0    0    0     0       0          0
#enp0s9:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
