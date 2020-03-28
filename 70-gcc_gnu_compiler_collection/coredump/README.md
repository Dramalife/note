# core - core dump file - CORE(5)

PROC
```
       /proc/sys/fs/suid_dumpable (since Linux 2.6.13)
              The value in this file is assigned to a process's "dumpable" flag in the circumstances described in prctl(2).  In effect, the value in  this
              file  determines  whether core dump files are produced for set-user-ID or otherwise protected/tainted binaries.  The "dumpable" setting also
              affects the ownership of files in a process's /proc/[pid] directory, as described above.

              Three different integer values can be specified:

              0 (default)
                     This provides the traditional (pre-Linux 2.6.13) behavior.  A core dump will not be produced for a process which has changed  creden‐
                     tials  (by calling seteuid(2), setgid(2), or similar, or by executing a set-user-ID or set-group-ID program) or whose binary does not
                     have read permission enabled.

              1 ("debug")
                     All processes dump core when possible.  (Reasons why a process might nevertheless not dump core are described in core(5).)  The  core
                     dump  is  owned  by  the filesystem user ID of the dumping process and no security is applied.  This is intended for system debugging
                     situations only: this mode is insecure because it allows unprivileged users to examine the memory contents of privileged processes.

              2 ("suidsafe")
                     Any binary which normally would not be dumped (see "0" above) is dumped readable by root only.  This allows the user  to  remove  the
                     core dump file but not to read it.  For security reasons core dumps in this mode will not overwrite one another or other files.  This
                     mode is appropriate when administrators are attempting to debug problems in a normal environment.

                     Additionally, since Linux 3.6, /proc/sys/kernel/core_pattern must either be an absolute pathname or a pipe command,  as  detailed  in
                     core(5).  Warnings will be written to the kernel log if core_pattern does not follow these rules, and no core dump will be produced.

              For details of the effect of a process's "dumpable" setting on ptrace access mode checking, see ptrace(2).



```
