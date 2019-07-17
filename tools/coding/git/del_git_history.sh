#! /bin/bash
#
# note git actu-del related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Ref Url : https://blog.csdn.net/u012145252/article/details/84178687

git filter-branch --force --index-filter 'git rm -r --cached --ignore-unmatch \
strace5 \
develop \
books \
userspace_programming \
kernel_programming \
kernel_using \
tools/busybox-1_31_0 \
tools/busybox \
tools/strace5 \
tools/strace5_syscall_trace \
tools/ctags-5.8 \
tools/curl-7.65.1 \
tools/curl \
tools/git-2.22.0.68.g0aae918 \
tools/lsof-4.86+dfsg.orig \
tools/quagga-1.2.4 \
tmp/busybox-1_31_0 \
tmp/busybox\
tmp/strace5 \
tmp/strace5_syscall_trace \
tmp/ctags-5.8 \
tmp/curl-7.65.1 \
tmp/curl \
tmp/git-2.22.0.68.g0aae918 \
tmp/lsof-4.86+dfsg.orig \
tmp/quagga-1.2.4 \
' \
--prune-empty --tag-name-filter cat -- --all

