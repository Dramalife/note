#! /bin/bash
#
# note gcc-git related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init : 2019.06.19,
# Update : 2019.08.17 ,Add command line autocomplete.
# Update : 
#

make configure
./configure
make all
# sudo apt-get purge git #remove old version
sudo make install

#  # PROBLEM 1
#    ---------
#  ## need lib-curl, see git/INSTALL +141
#  ## ref url :(https://blog.csdn.net/zhezhebie/article/details/78035979)
#  ## ref url :(https://stackoverflow.com/questions/8329485/unable-to-find-remote-helper-for-https-during-git-clone)
#  ## fatal : "致命的"
#  baohua@5b2vdev:~/note/tmp/curl-7.65.1 $ git pull
#  fatal: unable to find remote helper for 'https'
#  ## git/INSTALL +141
#  	- "libcurl" library is used by git-http-fetch, git-fetch, and, if
#  	  the curl version >= 7.34.0, for git-imap-send.  You might also
#  	  want the "curl" executable for debugging purposes. If you do not
#  	  use http:// or https:// repositories, and do not want to put
#  	  patches into an IMAP mailbox, you do not have to have them
#  	  (use NO_CURL).
#  ## clear configure about curl
#  vi config.mak.autogen > NO_CURL=   
#  or 
#  run ./configure
#  ## install curl
#  ## make & install git

#  # PROBLEM2 -- command line autocomplete
#    ---------
#  cp git/contrib/completion/git-completion.bash ~/.git-completion.bash
#  echo "source ~/.git-completion.bash" >> ~/.bashrc
  
### PROBLEM3 
#  $ git pull
#	fatal: unable to find remote helper for 'https'
#
# in file "configure" line 1353:
#	 --with-curl             support http(s):// transports (default is YES)
#                           ARG can be also prefix for curl library and headers
#

