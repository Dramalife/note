+|-r [t[m<fmt>]]
	puts  lsof in repeat mode.  There lsof lists open files as selected by other options, delays t seconds (default fifteen), then repeats the listing, delaying and
	listing repetitively until stopped by a condition defined by the prefix to the option.


# List all files opened by PROG
sudo lsof -c PROGRAM1 -c PROGRAM2

# List all files opened by USER
sudo lsof -u USER1,USER2
sudo lsof -u ^USER3

# List all files opened by PID
sudo lsof -p PID1,PID2,PID3
sudo lsof -p ^PID4

# List all network connections
sudo lsof -i
# List all network connections of TCP,UDP protocol
sudo lsof -i tcp
sudo lsof -i udp
# List process using PORT number
sudo lsof -i :25
# List process using PORT defined at "/etc/services"
sudo lsof -i :ntp
# List process using PORT(number) of UDP protocol
sudo lsof -i udp:53
# List process using IPv4
sudo lsof -i 4

# List all NFS files
sudo lsof -N

# List all UNIX.socket files
sudo lsof -U

# List all memory mapped files
sudo lsof -d mem
# List all process loaded to mem and processing
sudo lsof -d txt


# List network connections of(-a : &&) USER
sudo lsof -a -u USER -i

# List files opened by USR or(||) PROG
sudo lsof -u USR -c PROG
# List files opened by USR and(&&) PROG
sudo lsof -a -u USER -c PROG


#
sudo lsof -r 1 FILE
