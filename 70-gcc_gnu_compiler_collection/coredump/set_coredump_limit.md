```
 https://github.com/dramalife/note.git
 Author : dramalife@live.com
 Init : 2020.03.26
```

Examine
```
ulimit -c
cat /proc/sys/kernel/core_pattern
cat /proc/sys/kernel/core_uses_pid
```

Setting
```
# Only effective on the current terminal.(CH:仅在当前终端生效)
ulimit -c unlimited
# Core file path - CORE(5)
sudo echo "/tmp/core-%e-%p-%t" > /proc/sys/kernel/core_pattern
# suid_dumpable - PROC(7)
sudo echo "2" > /proc/sys/fs/suid_dumpable
```
