#! /bin/bash
#
# note "coreutils-8.28" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
# GNU bash, version 4.4.20(1)-release (x86_64-pc-linux-gnu)
# Copyright (C) 2016 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Init : 2019.10.31;
# Update :
#



# coreutils-8.28 $ ls src/*.c
#
# src/base64.c          src/dd.c                src/hostid.c           src/mv.c            src/rm.c          src/timeout.c
# src/basename.c        src/df.c                src/hostname.c         src/nice.c          src/rmdir.c       src/touch.c
# src/cat.c             src/dircolors.c         src/id.c               src/nl.c            src/runcon.c      src/tr.c
# src/chcon.c           src/dirname.c           src/install.c          src/nohup.c         src/selinux.c     src/true.c
# src/chgrp.c           src/du.c                src/join.c             src/nproc.c         src/seq.c         src/truncate.c
# src/chmod.c           src/echo.c              src/kill.c             src/numfmt.c        src/set-fields.c  src/tsort.c
# src/chown.c           src/env.c               src/lbracket.c         src/od.c            src/shred.c       src/tty.c
# src/chown-core.c      src/expand.c            src/libstdbuf.c        src/operand2sig.c   src/shuf.c        src/uname-arch.c
# src/chroot.c          src/expand-common.c     src/link.c             src/paste.c         src/sleep.c       src/uname.c
# src/cksum.c           src/expr.c              src/ln.c               src/pathchk.c       src/sort.c        src/uname-uname.c
# src/comm.c            src/extent-scan.c       src/logname.c          src/pinky.c         src/split.c       src/unexpand.c
# src/copy.c            src/factor.c            src/ls.c               src/pr.c            src/stat.c        src/uniq.c
# src/coreutils-arch.c  src/false.c             src/ls-dir.c           src/printenv.c      src/stdbuf.c      src/unlink.c
# src/coreutils.c       src/find-mount-point.c  src/ls-ls.c            src/printf.c        src/stty.c        src/uptime.c
# src/coreutils-dir.c   src/fmt.c               src/ls-vdir.c          src/prog-fprintf.c  src/sum.c         src/users.c
# src/coreutils-vdir.c  src/fold.c              src/make-prime-list.c  src/ptx.c           src/sync.c        src/version.c
# src/cp.c              src/force-link.c        src/md5sum.c           src/pwd.c           src/tac.c         src/wc.c
# src/cp-hash.c         src/getlimits.c         src/mkdir.c            src/readlink.c      src/tac-pipe.c    src/whoami.c
# src/csplit.c          src/group-list.c        src/mkfifo.c           src/realpath.c      src/tail.c        src/who.c
# src/cut.c             src/groups.c            src/mknod.c            src/relpath.c       src/tee.c         src/yes.c
# src/date.c            src/head.c              src/mktemp.c           src/remove.c        src/test.c

# GNU coreutils online help: <http://www.gnu.org/software/coreutils/>.(man 1 rm)

wget https://mirrors.sjtug.sjtu.edu.cn/gnu/coreutils/coreutils-8.28.tar.xz
