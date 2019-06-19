#! /bin/bash

make configure
./configure
make all
# sudo apt-get purge git #remove old version
sudo make install


#  # PROBLEM 1
#    ---------
#  ## need lib-curl, see git/INSTALL +141
#  ## ref url :(https://blog.csdn.net/zhezhebie/article/details/78035979)
#  baohua@5b2vdev:~/note/tmp/curl-7.65.1 $ git pull
#  fatal: unable to find remote helper for 'https'
#  
#  ## git/INSTALL +141
#  	- "libcurl" library is used by git-http-fetch, git-fetch, and, if
#  	  the curl version >= 7.34.0, for git-imap-send.  You might also
#  	  want the "curl" executable for debugging purposes. If you do not
#  	  use http:// or https:// repositories, and do not want to put
#  	  patches into an IMAP mailbox, you do not have to have them
#  	  (use NO_CURL).
#  
#  ## clear configure about curl
#  vi config.mak.autogen > NO_CURL=   
#  or 
#  run ./configure
#  
#  ## install curl
#  
#  ## make & install git

