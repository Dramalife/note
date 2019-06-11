#! /bin/bash


# Sample --fd
ls -l /proc/$1/fd/*
# lrwx------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/0 -> /dev/null
# lrwx------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/1 -> /dev/null
# lrwx------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/2 -> /dev/null
# lr-x------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/3 -> pipe:[16237]
# l-wx------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/4 -> pipe:[16237]
# lrwx------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/5 -> socket:[16238]
# l-wx------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/8 -> /tmp/zebra_log
# lrwx------    1 root     root            64 Jun 10 11:12 /proc/6172/fd/9 -> socket:[15965]

