#! /bin/bash
#
# https://github.com/dramalife/note.git
# Author : dramalife@live.com
# Init : 2020.03.26
#


ulimit
sudo echo "core" > /proc/sys/kernel/core_pattern
cat /proc/sys/kernel/core_pattern
cat /proc/sys/kernel/core_uses_pid
