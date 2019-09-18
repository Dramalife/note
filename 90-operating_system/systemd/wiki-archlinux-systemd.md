{{Lowercase title}}
[[Category:Daemons]]
[[Category:Init]]
[[ar:Systemd]]
[[de:Systemd]]
[[el:Systemd]]
[[es:Systemd]]
[[fa:Systemd]]
[[fr:Systemd]]
[[it:Systemd]]
[[ja:Systemd]]
[[pt:Systemd]]
[[ru:Systemd]]
[[zh-hans:Systemd]]
[[zh-hant:Systemd]]
{{Related articles start}}
{{Related|systemd/User}}
{{Related|systemd/Timers}}
{{Related|systemd/Journal}}
{{Related|systemd FAQ}}
{{Related|init}}
{{Related|Daemons}}
{{Related|udev}}
{{Related|Improving performance/Boot process}}
{{Related|Allow users to shutdown}}
{{Related articles end}}

From the [https://freedesktop.org/wiki/Software/systemd/ project web page]:

:''systemd'' is a suite of basic building blocks for a Linux system. It provides a system and service manager that runs as PID 1 and starts the rest of the system. systemd provides aggressive parallelization capabilities, uses socket and [[D-Bus]] activation for starting services, offers on-demand starting of daemons, keeps track of processes using Linux [[control groups]], maintains mount and automount points, and implements an elaborate transactional dependency-based service control logic. ''systemd'' supports SysV and LSB init scripts and works as a replacement for sysvinit. Other parts include a logging daemon, utilities to control basic system configuration like the hostname, date, locale, maintain a list of logged-in users and running containers and virtual machines, system accounts, runtime directories and settings, and daemons to manage simple network configuration, network time synchronization, log forwarding, and name resolution.

{{Note|1=For a detailed explanation of why Arch moved to ''systemd'', see [https://bbs.archlinux.org/viewtopic.php?pid=1149530#p1149530 this forum post].}}

{{Expansion|Add information about {{Pkg|systemd-sysvcompat}} and the commands it provides.}}

== Basic systemctl usage  ==

The main command used to introspect and control ''systemd'' is ''systemctl''. Some of its uses are examining the system state and managing the system and services. See {{man|1|systemctl}} for more details.

{{Tip|
* You can use all of the following ''systemctl'' commands with the {{ic|-H ''user''@''host''}} switch to control a ''systemd'' instance on a remote machine. This will use [[SSH]] to connect to the remote ''systemd'' instance.
* [[Plasma]] users can install {{AUR|systemd-kcm}} as a graphical frontend for ''systemctl''. After installing the module will be added under ''System administration''.}}

=== Analyzing the system state ===

Show '''system status''' using:

 $ systemctl status

'''List running''' units:

 $ systemctl

or:

 $ systemctl list-units

'''List failed''' units:

 $ systemctl --failed

The available unit files can be seen in {{ic|/usr/lib/systemd/system/}} and {{ic|/etc/systemd/system/}} (the latter takes precedence). '''List installed''' unit files with:

 $ systemctl list-unit-files

Show the [[cgroups|cgroup slice]], memory and parent for a PID:

 $ systemctl status ''pid''

=== Using units ===

Units can be, for example, services (''.service''), mount points (''.mount''), devices (''.device'') or sockets (''.socket'').

When using ''systemctl'', you generally have to specify the complete name of the unit file, including its suffix, for example {{ic|sshd.socket}}. There are however a few short forms when specifying the unit in the following ''systemctl'' commands:

* If you do not specify the suffix, systemctl will assume ''.service''. For example, {{ic|netctl}} and {{ic|netctl.service}} are equivalent.
* Mount points will automatically be translated into the appropriate ''.mount'' unit. For example, specifying {{ic|/home}} is equivalent to {{ic|home.mount}}.
* Similar to mount points, devices are automatically translated into the appropriate ''.device'' unit, therefore specifying {{ic|/dev/sda2}} is equivalent to {{ic|dev-sda2.device}}.

See {{man|5|systemd.unit}} for details.

{{Note|Some unit names contain an {{ic|@}} sign (e.g. {{ic|name@''string''.service}}): this means that they are [http://0pointer.de/blog/projects/instances.html instances] of a ''template'' unit, whose actual file name does not contain the {{ic|''string''}} part (e.g. {{ic|name@.service}}). {{ic|''string''}} is called the ''instance identifier'', and is similar to an argument that is passed to the template unit when called with the ''systemctl'' command: in the unit file it will substitute the {{ic|%i}} specifier. 

To be more accurate, ''before'' trying to instantiate the {{ic|name@.suffix}} template unit, ''systemd'' will actually look for a unit with the exact {{ic|name@string.suffix}} file name, although by convention such a "clash" happens rarely, i.e. most unit files containing an {{ic|@}} sign are meant to be templates. Also, if a template unit is called without an instance identifier, it will just fail, since the {{ic|%i}} specifier cannot be substituted.
}}

{{Tip|
* Most of the following commands also work if multiple units are specified, see {{man|1|systemctl}} for more information.
* The {{ic|--now}} switch can be used in conjunction with {{ic|enable}}, {{ic|disable}}, and {{ic|mask}} to respectively start, stop, or mask the unit ''immediately'' rather than after rebooting.
* A package may offer units for different purposes. If you just installed a package, {{ic|pacman -Qql ''package'' <nowiki>|</nowiki> grep -Fe .service -e .socket}} can be used to check and find them.}}

'''Start''' a unit immediately:

 # systemctl start ''unit''

'''Stop''' a unit immediately:

 # systemctl stop ''unit''

'''Restart''' a unit:

 # systemctl restart ''unit''

Ask a unit to '''reload''' its configuration:

 # systemctl reload ''unit''

Show the '''status''' of a unit, including whether it is running or not:

 $ systemctl status ''unit''

'''Check''' whether a unit is already enabled or not:

 $ systemctl is-enabled ''unit''

'''Enable''' a unit to be started on '''bootup''':

 # systemctl enable ''unit''

'''Enable''' a unit to be started on '''bootup''' and '''Start''' immediately:

 # systemctl enable --now ''unit''

'''Disable''' a unit to not start during bootup:

 # systemctl disable ''unit''

'''Mask''' a unit to make it impossible to start it (both manually and as a dependency, which makes masking dangerous):

 # systemctl mask ''unit''

'''Unmask''' a unit:

 # systemctl unmask ''unit''

Show the '''manual page''' associated with a unit (this has to be supported by the unit file):

 $ systemctl help ''unit''

'''Reload ''systemd'' ''' manager configuration, scanning for '''new or changed units''':
{{Note|This does not ask the changed units to reload their own configurations. See {{ic|reload}} example above.}}

 # systemctl daemon-reload

=== Power management ===

[[polkit]] is necessary for power management as an unprivileged user. If you are in a local ''systemd-logind'' user session and no other session is active, the following commands will work without root privileges. If not (for example, because another user is logged into a tty), ''systemd'' will automatically ask you for the root password.

Shut down and reboot the system:

 $ reboot

Shut down and power-off the system:

 $ poweroff

Suspend the system:

 $ systemctl suspend

Put the system into hibernation:

 $ systemctl hibernate

Put the system into hybrid-sleep state (or suspend-to-both):

 $ systemctl hybrid-sleep

== Writing unit files ==

The syntax of ''systemd'''s [https://www.freedesktop.org/software/systemd/man/systemd.unit.html unit files] is inspired by XDG Desktop Entry Specification ''.desktop'' files, which are in turn inspired by Microsoft Windows ''.ini'' files. Unit files are loaded from multiple locations (to see the full list, run {{ic|1=systemctl show --property=UnitPath}}), but the main ones are (listed from lowest to highest precedence):

* {{ic|/usr/lib/systemd/system/}}: units provided by installed packages
* {{ic|/etc/systemd/system/}}: units installed by the system administrator

{{Note|
* The load paths are completely different when running ''systemd'' in [[systemd/User#How it works|user mode]].
* systemd unit names may only contain ASCII alphanumeric characters, underscores and periods. All other characters must be replaced by C-style "\x2d" escapes, or employ their predefined semantics ('@', '-'). See {{man|5|systemd.unit}} and {{man|1|systemd-escape}} for more information.}}

Look at the units installed by your packages for examples, as well as the [https://www.freedesktop.org/software/systemd/man/systemd.service.html#Examples annotated example section] of {{man|5|systemd.service}}.

{{Tip|Comments prepended with {{ic|#}} may be used in unit-files as well, but only in new lines. Do not use end-line comments after ''systemd'' parameters or the unit will fail to activate.}}

=== Handling dependencies ===

With ''systemd'', dependencies can be resolved by designing the unit files correctly. The most typical case is that the unit ''A'' requires the unit ''B'' to be running before ''A'' is started. In that case add {{ic|1=Requires=''B''}} and {{ic|1=After=''B''}} to the {{ic|[Unit]}} section of ''A''. If the dependency is optional, add {{ic|1=Wants=''B''}} and {{ic|1=After=''B''}} instead. Note that {{ic|1=Wants=}} and {{ic|1=Requires=}} do not imply {{ic|1=After=}}, meaning that if {{ic|1=After=}} is not specified, the two units will be started in parallel.

Dependencies are typically placed on services and not on [[#Targets]]. For example, {{ic|network.target}} is pulled in by whatever service configures your network interfaces, therefore ordering your custom unit after it is sufficient since {{ic|network.target}} is started anyway.

=== Service types ===

There are several different start-up types to consider when writing a custom service file. This is set with the {{ic|1=Type=}} parameter in the {{ic|[Service]}} section:

* {{ic|1=Type=simple}} (default): ''systemd'' considers the service to be started up immediately. The process must not fork. Do not use this type if other services need to be ordered on this service, unless it is socket activated.
* {{ic|1=Type=forking}}: ''systemd'' considers the service started up once the process forks and the parent has exited. For classic daemons use this type unless you know that it is not necessary. You should specify {{ic|1=PIDFile=}} as well so ''systemd'' can keep track of the main process.
* {{ic|1=Type=oneshot}}: this is useful for scripts that do a single job and then exit. You may want to set {{ic|1=RemainAfterExit=yes}} as well so that ''systemd'' still considers the service as active after the process has exited.
* {{ic|1=Type=notify}}: identical to {{ic|1=Type=simple}}, but with the stipulation that the daemon will send a signal to ''systemd'' when it is ready. The reference implementation for this notification is provided by ''libsystemd-daemon.so''.
* {{ic|1=Type=dbus}}: the service is considered ready when the specified {{ic|BusName}} appears on DBus's system bus.
* {{ic|1=Type=idle}}: ''systemd'' will delay execution of the service binary until all jobs are dispatched. Other than that behavior is very similar to {{ic|1=Type=simple}}. 

See the [https://www.freedesktop.org/software/systemd/man/systemd.service.html#Type= systemd.service(5)] man page for a more detailed explanation of the {{ic|Type}} values.

=== Editing provided units ===

{{Style|Should be renamed to more descriptive ''Modifying provided units''.|talk=Talk:Edit#Deprecation}}

To avoid conflicts with pacman, unit files provided by packages should not be directly edited. There are two safe ways to modify a unit without touching the original file: create a new unit file which [[#Replacement unit files|overrides the original unit]] or create [[#Drop-in files|drop-in snippets]] which are applied on top of the original unit. For both methods, you must reload the unit afterwards to apply your changes. This can be done either by editing the unit with {{ic|systemctl edit}} (which reloads the unit automatically) or by reloading all units with:

 # systemctl daemon-reload

{{Tip|
* You can use ''systemd-delta'' to see which unit files have been overridden or extended and what exactly has been changed.
* Use {{ic|systemctl cat ''unit''}} to view the content of a unit file and all associated drop-in snippets.
}}

==== Replacement unit files ====

To replace the unit file {{ic|/usr/lib/systemd/system/''unit''}}, create the file {{ic|/etc/systemd/system/''unit''}} and ''reenable'' the unit to update the symlinks:

 # systemctl reenable ''unit''

Alternatively, run:

 # systemctl edit --full ''unit''

This opens {{ic|/etc/systemd/system/''unit''}} in your editor (copying the installed version if it does not exist yet) and automatically reloads it when you finish editing.

{{Note|The replacement units will keep on being used even if Pacman updates the original units in the future. This method makes system maintenance more difficult and therefore the next approach is preferred.}}

==== Drop-in files ====

To create drop-in files for the unit file {{ic|/usr/lib/systemd/system/''unit''}}, create the directory {{ic|/etc/systemd/system/''unit''.d/}} and place ''.conf'' files there to override or add new options. ''systemd'' will parse and apply these files on top of the original unit.

The easiest way to do this is to run:

 # systemctl edit ''unit''

This opens the file {{ic|/etc/systemd/system/''unit''.d/override.conf}} in your text editor (creating it if necessary) and automatically reloads the unit when you are done editing.

{{Note|Not all keys can be overridden with drop-in files. For example, for changing {{ic|1=Conflicts=}} a replacement file [https://lists.freedesktop.org/archives/systemd-devel/2017-June/038976.html is necessary].}}

==== Revert to vendor version ====

To revert any changes to a unit made using {{ic|systemctl edit}} do:

 # systemctl revert ''unit''

==== Examples ====

For example, if you simply want to add an additional dependency to a unit, you may create the following file:

{{hc|/etc/systemd/system/''unit''.d/customdependency.conf|2=
[Unit]
Requires=''new dependency''
After=''new dependency''
}}

As another example, in order to replace the {{ic|ExecStart}} directive for a unit that is not of type {{ic|oneshot}}, create the following file:

{{hc|/etc/systemd/system/''unit''.d/customexec.conf|2=
[Service]
ExecStart=
ExecStart=''new command''
}}

Note how {{ic|ExecStart}} must be cleared before being re-assigned [https://bugzilla.redhat.com/show_bug.cgi?id=756787#c9]. The same holds for every item that can be specified multiple times, e.g. {{ic|OnCalendar}} for timers.

One more example to automatically restart a service:

{{hc|/etc/systemd/system/''unit''.d/restart.conf|2=
[Service]
Restart=always
RestartSec=30
}}

== Targets ==

{{Style|Unclear description, copy-pasted content (explicitly mentions "Fedora").|section=Make section "Targets" more clearly}}

''systemd'' uses ''targets'' to group units together via dependencies and as standardized synchronization points. They serve a similar purpose as [[wikipedia:Runlevel|runlevels]] but act a little different. Each ''target'' is named instead of numbered and is intended to serve a specific purpose with the possibility of having multiple ones active at the same time. Some ''target''s are implemented by inheriting all of the services of another ''target'' and adding additional services to it. There are ''systemd'' ''target''s that mimic the common SystemVinit runlevels so you can still switch ''target''s using the familiar {{ic|telinit RUNLEVEL}} command.

=== Get current targets ===

The following should be used under ''systemd'' instead of running {{ic|runlevel}}:

 $ systemctl list-units --type=target

=== Create custom target ===

The runlevels that held a defined meaning under sysvinit (i.e., 0, 1, 3, 5, and 6); have a 1:1 mapping with a specific ''systemd'' ''target''. Unfortunately, there is no good way to do the same for the user-defined runlevels like 2 and 4. If you make use of those it is suggested that you make a new named ''systemd'' ''target'' as {{ic|/etc/systemd/system/''your target''}} that takes one of the existing runlevels as a base (you can look at {{ic|/usr/lib/systemd/system/graphical.target}} as an example), make a directory {{ic|/etc/systemd/system/''your target''.wants}}, and then symlink the additional services from {{ic|/usr/lib/systemd/system/}} that you wish to enable.

=== Mapping between SysV runlevels and systemd targets ===

{| class="wikitable"
! SysV Runlevel !! systemd Target !! Notes
|-
| 0 || runlevel0.target, poweroff.target || Halt the system.
|-
| 1, s, single || runlevel1.target, rescue.target || Single user mode.
|-
| 2, 4 || runlevel2.target, runlevel4.target, multi-user.target || User-defined/Site-specific runlevels. By default, identical to 3.
|-
| 3 || runlevel3.target, multi-user.target || Multi-user, non-graphical. Users can usually login via multiple consoles or via the network.
|-
| 5 || runlevel5.target, graphical.target || Multi-user, graphical. Usually has all the services of runlevel 3 plus a graphical login.
|-
| 6 || runlevel6.target, reboot.target || Reboot
|-
| emergency || emergency.target || Emergency shell
|-
|}

=== Change current target ===

In ''systemd'' targets are exposed via ''target units''. You can change them like this:

 # systemctl isolate graphical.target

This will only change the current target, and has no effect on the next boot. This is equivalent to commands such as {{ic|telinit 3}} or {{ic|telinit 5}} in Sysvinit.

=== Change default target to boot into ===

The standard target is {{ic|default.target}}, which is a symlink to {{ic|graphical.target}}. This roughly corresponds to the old runlevel 5.

To verify the current target with ''systemctl'':

 $ systemctl get-default

To change the default target to boot into, change the {{ic|default.target}} symlink. With ''systemctl'':

{{hc|1=# systemctl set-default multi-user.target|2=
Removed /etc/systemd/system/default.target.
Created symlink /etc/systemd/system/default.target -> /usr/lib/systemd/system/multi-user.target.}}

Alternatively, append one of the following [[kernel parameters]] to your bootloader:

* {{ic|1=systemd.unit=multi-user.target}} (which roughly corresponds to the old runlevel 3),
* {{ic|1=systemd.unit=rescue.target}} (which roughly corresponds to the old runlevel 1).

=== Default target order ===

Systemd chooses the {{ic|default.target}} according to the following order:

# Kernel parameter shown above
# Symlink of {{ic|/etc/systemd/system/default.target}}
# Symlink of {{ic|/usr/lib/systemd/system/default.target}}

== Temporary files ==

"''systemd-tmpfiles'' creates, deletes and cleans up volatile and temporary files and directories." It reads configuration files in {{ic|/etc/tmpfiles.d/}} and {{ic|/usr/lib/tmpfiles.d/}} to discover which actions to perform. Configuration files in the former directory take precedence over those in the latter directory.

Configuration files are usually provided together with service files, and they are named in the style of {{ic|/usr/lib/tmpfiles.d/''program''.conf}}. For example, the [[Samba]] daemon expects the directory {{ic|/run/samba}} to exist and to have the correct permissions. Therefore, the {{Pkg|samba}} package ships with this configuration:

{{hc|/usr/lib/tmpfiles.d/samba.conf|
D /run/samba 0755 root root}}

Configuration files may also be used to write values into certain files on boot. For example, if you used {{ic|/etc/rc.local}} to disable wakeup from USB devices with {{ic|echo USBE > /proc/acpi/wakeup}}, you may use the following tmpfile instead:

{{hc|/etc/tmpfiles.d/disable-usb-wake.conf|
#    Path                  Mode UID  GID  Age Argument
w    /proc/acpi/wakeup     -    -    -    -   USBE}}

See the {{man|8|systemd-tmpfiles}} and {{man|5|tmpfiles.d}} man pages for details.

{{Note|This method may not work to set options in {{ic|/sys}} since the ''systemd-tmpfiles-setup'' service may run before the appropriate device modules is loaded. In this case you could check whether the module has a parameter for the option you want to set with {{ic|modinfo ''module''}} and set this option with a [[Kernel modules#Setting module options|config file in /etc/modprobe.d]]. Otherwise you will have to write a [[Udev#About_udev_rules|udev rule]] to set the appropriate attribute as soon as the device appears.}}

== Timers ==

A timer is a unit configuration file whose name ends with ''.timer'' and encodes information about a timer controlled and supervised by ''systemd'', for timer-based activation. See [[systemd/Timers]].

{{Note|Timers can replace [[cron]] functionality to a great extent. See [[systemd/Timers#As a cron replacement]].}}

== Mounting ==

''systemd'' is in charge of mounting the partitions and filesystems specified in {{ic|/etc/fstab}}. The {{man|8|systemd-fstab-generator}} translates all the entries in {{ic|/etc/fstab}} into systemd units, this is performed at boot time and whenever the configuration of the system manager is reloaded.

''systemd'' extends the usual [[fstab]] capabilities and offers additional mount options. These affect the dependencies of the mount unit, they can for example ensure that a mount is performed only once the network is up or only once another partition is mounted. The full list of specific ''systemd'' mount options, typically prefixed with {{ic|x-systemd.}}, is detailed in {{man|5|systemd.mount|FSTAB}}.

An example of these mount options in the context of ''automounting'', which means mounting only when the resource is required rather than automatically at boot time, is provided in [[fstab#Automount with systemd]].

=== GPT partition automounting ===

On a [[GPT]] partitioned disk {{man|8|systemd-gpt-auto-generator}} will mount partitions following the [https://www.freedesktop.org/wiki/Specifications/DiscoverablePartitionsSpec/ Discoverable Partitions Specification], thus they can be omitted from {{ic|fstab}}.

The automounting for a partition can be disabled by changing the partition's [[Wikipedia:GUID Partition Table#Partition type GUIDs|type GUID]] or setting the partition attribute bit 63 "do not automount", see [[gdisk#Prevent GPT partition automounting]].

== Tips and tricks ==

=== Running services after the network is up ===

To delay a service after the network is up, include the following dependencies in the ''.service'' file:

{{hc|/etc/systemd/system/''foo''.service|2=
[Unit]
...
'''Wants=network-online.target'''
'''After=network-online.target'''
...
}}

The network wait service of the particular application that manages the network, must also be enabled so that {{ic|network-online.target}} properly reflects the network status.
* For the ones using [[NetworkManager]], [[enable]] {{ic|NetworkManager-wait-online.service}}.
* In the case of [[netctl]], enable the {{ic|netctl-wait-online.service}}.
* If using [[systemd-networkd]], {{ic|systemd-networkd-wait-online.service}} is by default enabled automatically whenever {{ic|systemd-networkd.service}} has been enabled; check this is the case with {{ic|systemctl is-enabled systemd-networkd-wait-online.service}}, there is no other action needed.

For more detailed explanations see [https://www.freedesktop.org/wiki/Software/systemd/NetworkTarget/ Running services after the network is up] in the systemd wiki.

=== Enable installed units by default ===

{{Expansion|How does it work with instantiated units?}}

Arch Linux ships with {{ic|/usr/lib/systemd/system-preset/99-default.preset}} containing {{ic|disable *}}. This causes ''systemctl preset'' to disable all units by default, such that when a new package is installed, the user must manually enable the unit.

If this behavior is not desired, simply create a symlink from {{ic|/etc/systemd/system-preset/99-default.preset}} to {{ic|/dev/null}} in order to override the configuration file. This will cause ''systemctl preset'' to enable all units that get installed—regardless of unit type—unless specified in another file in one ''systemctl preset'''s configuration directories. User units are not affected. See {{man|5|systemd.preset}} for more information.

{{Note|Enabling all units by default may cause problems with packages that contain two or more mutually exclusive units. ''systemctl preset'' is designed to be used by distributions and spins or system administrators. In the case where two conflicting units would be enabled, you should explicitly specify which one is to be disabled in a preset configuration file as specified in the manpage for {{ic|systemd.preset}}.}}

=== Sandboxing application environments ===
A unit file can be created as a sandbox to isolate applications and their processes within a hardened virtual environment. systemd leverages [[wikipedia:Linux_namespaces|namespaces]], white-/blacklisting of [[Capabilities]], and [[control groups]] to container processes through an extensive [https://www.freedesktop.org/software/systemd/man/systemd.exec.html execution environment configuration].

The enhancement of an existing systemd unit file with application sandboxing typically requires trial-and-error tests accompanied by the generous use of {{Pkg|strace}}, [[wikipedia:Standard_streams#Standard_error_.28stderr.29|stderr]] and [https://www.freedesktop.org/software/systemd/man/journalctl.html journalctl] error logging and output facilities. You may want to first search upstream documentation for already done tests to base trials on.

Some examples on how sandboxing with systemd can be deployed:
* {{Ic|CapabilityBoundingSet}} defines a whitelisted set of allowed capabilities, but may also be used to blacklist a specific capability for a unit.
** The {{Ic|CAP_SYS_ADM}} capability, for example, which should be one of the [https://lwn.net/Articles/486306/ goals of a secure sandbox]: {{ic|1=CapabilityBoundingSet=~ CAP_SYS_ADM}}

== Troubleshooting ==

=== Investigating systemd errors ===

As an example, we will investigate an error with {{ic|systemd-modules-load}} service:

'''1.''' Lets find the ''systemd'' services which fail to start at boot time:

{{hc|1=$ systemctl --state=failed|2=
systemd-modules-load.service   loaded '''failed failed'''  Load Kernel Modules}}

Another way is to live log ''systemd'' messages:

 $ journalctl -fp err

'''2.''' Ok, we found a problem with {{ic|systemd-modules-load}} service. We want to know more:
{{hc|$ systemctl status systemd-modules-load|2=
systemd-modules-load.service - Load Kernel Modules
   Loaded: loaded (/usr/lib/systemd/system/systemd-modules-load.service; static)
   Active: '''failed''' (Result: exit-code) since So 2013-08-25 11:48:13 CEST; 32s ago
     Docs: man:systemd-modules-load.service(8).
           man:modules-load.d(5)
  Process: '''15630''' ExecStart=/usr/lib/systemd/systemd-modules-load ('''code=exited, status=1/FAILURE''')
}}
If the {{ic|Process ID}} is not listed, just restart the failed service with {{ic|systemctl restart systemd-modules-load}}

'''3.''' Now we have the process id (PID) to investigate this error in depth. Enter the following command with the current {{ic|Process ID}} (here: 15630):
{{hc|1=$ journalctl _PID=15630|2=
-- Logs begin at Sa 2013-05-25 10:31:12 CEST, end at So 2013-08-25 11:51:17 CEST. --
Aug 25 11:48:13 mypc systemd-modules-load[15630]: '''Failed to find module 'blacklist usblp''''
Aug 25 11:48:13 mypc systemd-modules-load[15630]: '''Failed to find module 'install usblp /bin/false'''' 
}}

'''4.''' We see that some of the kernel module configs have wrong settings. Therefore we have a look at these settings in {{ic|/etc/modules-load.d/}}:
{{hc|$ ls -Al /etc/modules-load.d/|
...
-rw-r--r--   1 root root    79  1. Dez 2012  blacklist.conf
-rw-r--r--   1 root root     1  2. Mär 14:30 encrypt.conf
-rw-r--r--   1 root root     3  5. Dez 2012  printing.conf
-rw-r--r--   1 root root     6 14. Jul 11:01 realtek.conf
-rw-r--r--   1 root root    65  2. Jun 23:01 virtualbox.conf
...
}}

'''5.''' The {{ic|Failed to find module 'blacklist usblp'}} error message might be related to a wrong setting inside of {{ic|blacklist.conf}}. Lets deactivate it with inserting a trailing '''#''' before each option we found via step 3:
{{hc|/etc/modules-load.d/blacklist.conf|
'''#''' blacklist usblp
'''#''' install usblp /bin/false
}}

'''6.''' Now, try to start {{ic|systemd-modules-load}}:
 # systemctl start systemd-modules-load
If it was successful, this should not prompt anything. If you see any error, go back to step 3 and use the new PID for solving the errors left.

If everything is ok, you can verify that the service was started successfully with:
{{hc|$ systemctl status systemd-modules-load|2=
systemd-modules-load.service - Load Kernel Modules
   Loaded: '''loaded''' (/usr/lib/systemd/system/systemd-modules-load.service; static)
   Active: '''active (exited)''' since So 2013-08-25 12:22:31 CEST; 34s ago
     Docs: man:systemd-modules-load.service(8)
           man:modules-load.d(5)
 Process: 19005 ExecStart=/usr/lib/systemd/systemd-modules-load (code=exited, status=0/SUCCESS)
Aug 25 12:22:31 mypc systemd[1]: '''Started Load Kernel Modules'''.
}}

=== Diagnosing boot problems ===

''systemd'' has several options for diagnosing problems with the boot process. See [[boot debugging]] for more general instructions and options to capture boot messages before ''systemd'' takes over the [[boot process]]. Also see the [https://freedesktop.org/wiki/Software/systemd/Debugging/ systemd debugging documentation].

=== Diagnosing a service ===

If some ''systemd'' service misbehaves or you want to get more information about what is happening, set the {{ic|SYSTEMD_LOG_LEVEL}} [[environment variable]] to {{ic|debug}}. For example, to run the ''systemd-networkd'' daemon in debug mode:

Add a [[#Drop-in files|drop-in file]] for the service adding the two lines:

 [Service]
 Environment=SYSTEMD_LOG_LEVEL=debug

Or equivalently, set the environment variable manually:

 # SYSTEMD_LOG_LEVEL=debug /lib/systemd/systemd-networkd

then [[restart]] ''systemd-networkd'' and watch the journal for the service with the {{ic|-f}}/{{ic|--follow}} option.

=== Shutdown/reboot takes terribly long ===

If the shutdown process takes a very long time (or seems to freeze) most likely a service not exiting is to blame. ''systemd'' waits some time for each service to exit before trying to kill it. To find out if you are affected, see [https://freedesktop.org/wiki/Software/systemd/Debugging/#shutdowncompleteseventually this article].

=== Short lived processes do not seem to log any output ===

If {{ic|journalctl -u foounit}} does not show any output for a short lived service, look at the PID instead. For example, if {{ic|systemd-modules-load.service}} fails, and {{ic|systemctl status systemd-modules-load}} shows that it ran as PID 123, then you might be able to see output in the journal for that PID, i.e. {{ic|journalctl -b _PID&#61;123}}. Metadata fields for the journal such as {{ic|_SYSTEMD_UNIT}} and {{ic|_COMM}} are collected asynchronously and rely on the {{ic|/proc}} directory for the process existing. Fixing this requires fixing the kernel to provide this data via a socket connection, similar to {{ic|SCM_CREDENTIALS}}. In short, it is a [https://github.com/systemd/systemd/issues/2913 bug]. Keep in mind that immediately failed services might not print anything to the journal as per design of systemd.

=== Boot time increasing over time ===

After using {{ic|systemd-analyze}} a number of users have noticed that their boot time has increased significantly in comparison with what it used to be. After using {{ic|systemd-analyze blame}} [[NetworkManager]] is being reported as taking an unusually large amount of time to start. 

The problem for some users has been due to {{ic|/var/log/journal}} becoming too large. This may have other impacts on performance, such as for {{ic|systemctl status}} or {{ic|journalctl}}. As such the solution is to remove every file within the folder (ideally making a backup of it somewhere, at least temporarily) and then setting a journal file size limit as described in [[Systemd/Journal#Journal size limit]].

=== systemd-tmpfiles-setup.service fails to start at boot ===

Starting with systemd 219, {{ic|/usr/lib/tmpfiles.d/systemd.conf}} specifies ACL attributes for directories under {{ic|/var/log/journal}} and, therefore, requires ACL support to be enabled for the filesystem the journal resides on.

See [[Access Control Lists#Enabling ACL]] for instructions on how to enable ACL on the filesystem that houses {{ic|/var/log/journal}}.

=== systemd version printed on boot is not the same as installed package version ===

You need to [[Mkinitcpio#Image_creation_and_activation|regenerate your initramfs]] and the versions should match. 

{{Tip|1=A pacman hook can be used to automatically regenerate the initramfs every time {{pkg|systemd}} is upgraded. See [https://bbs.archlinux.org/viewtopic.php?id=215411 this forum thread] and [[Pacman#Hooks]].}}

=== Disable emergency mode on remote machine ===

You may want to disable emergency mode on a remote machine, for example, a virtual machine hosted at Azure or Google Cloud. It is because if emergency mode is triggered, the machine will be blocked from connecting to network.

 # systemctl mask emergency.service
 # systemctl mask emergency.target

== See also ==

*[[Wikipedia:systemd|Wikipedia article]]
*[https://www.freedesktop.org/wiki/Software/systemd systemd Official web site]
**[https://www.freedesktop.org/wiki/Software/systemd/Optimizations systemd optimizations]
**[https://www.freedesktop.org/wiki/Software/systemd/FrequentlyAskedQuestions systemd FAQ]
**[https://www.freedesktop.org/wiki/Software/systemd/TipsAndTricks systemd Tips and tricks]
*[https://www.freedesktop.org/software/systemd/man/ Manual pages]
*Other distributions
**[https://wiki.gentoo.org/wiki/Systemd Gentoo Wiki systemd page]
**[https://fedoraproject.org/wiki/Systemd Fedora Project - About systemd]
**[https://fedoraproject.org/wiki/How_to_debug_Systemd_problems Fedora Project - How to debug systemd problems]
**[https://fedoraproject.org/wiki/SysVinit_to_Systemd_Cheatsheet Fedora Project - SysVinit to systemd cheatsheet]
**[[debian:systemd|Debian Wiki systemd page]]
*[http://0pointer.de/blog/projects/systemd.html Lennart's blog story], [http://0pointer.de/blog/projects/systemd-update.html update 1], [http://0pointer.de/blog/projects/systemd-update-2.html update 2], [http://0pointer.de/blog/projects/systemd-update-3.html update 3], [http://0pointer.de/blog/projects/why.html summary]
*[http://0pointer.de/public/systemd-ebook-psankar.pdf systemd for Administrators (PDF)]
*[https://www.digitalocean.com/community/tutorials/how-to-use-systemctl-to-manage-systemd-services-and-units How To Use Systemctl to Manage Systemd Services and Units ]
*[https://dvdhrm.wordpress.com/2013/08/24/session-management-on-linux/ Session management with systemd-logind]
*[[Emacs#Syntax highlighting for systemd Files|Emacs Syntax highlighting for Systemd files]]
*[http://www.h-online.com/open/features/Control-Centre-The-systemd-Linux-init-system-1565543.html Two] [http://www.h-online.com/open/features/Booting-up-Tools-and-tips-for-systemd-1570630.html part] introductory article in ''The H Open'' magazine.
