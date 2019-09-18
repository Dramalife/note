Source Url : https://wiki.archlinux.org/index.php/Systemd-resolved

{{Lowercase title}}
[[Category:Domain Name System]]
[[Category:Multicast DNS]]
{{Related articles start}}
{{Related|systemd-networkd}}
{{Related|Domain name resolution}}
{{Related|Avahi}}
{{Related articles end}}
[https://www.freedesktop.org/wiki/Software/systemd/resolved/ systemd-resolved] is a [[systemd]] service that provides network name resolution to local applications via a [[D-Bus]] interface, the {{ic|resolve}} [[Name Service Switch|NSS]] service ({{man|8|nss-resolve}}), and a local DNS stub listener on {{ic|127.0.0.53}}. See {{man|8|systemd-resolved}} for the usage.

== Installation ==

''systemd-resolved'' is a part of the {{Pkg|systemd}} package that is [[install]]ed by default.

== Configuration ==

''systemd-resolved'' provides resolver services for [[Wikipedia:Domain Name System|Domain Name System (DNS)]] (including [[Wikipedia:Domain Name System Security Extensions|DNSSEC]] and [[Wikipedia:DNS over TLS|DNS over TLS]]), [[Wikipedia:Multicast DNS|Multicast DNS (mDNS)]] and [[Wikipedia:Link-Local Multicast Name Resolution|Link-Local Multicast Name Resolution (LLMNR)]].

The resolver can be configured by editing {{ic|/etc/systemd/resolved.conf}} and/or drop-in ''.conf'' files in {{ic|/etc/systemd/resolved.conf.d/}}. See {{man|5|resolved.conf}}.

To use ''systemd-resolved'' [[start]] and [[enable]] {{ic|systemd-resolved.service}}.

{{Tip|To understand the context around the choices and switches, one can turn on detailed debug information for ''systemd-resolved'' as described in [[systemd#Diagnosing a service]].}}

=== DNS ===

''systemd-resolved'' has four different modes for handling the [[Domain name resolution]] (the four modes are described in {{man|8|systemd-resolved|/ETC/RESOLV.CONF}}). We will focus here on the two most relevant modes.

# Using the systemd DNS stub file - the systemd DNS stub file {{ic|/run/systemd/resolve/stub-resolv.conf}} contains the local stub {{ic|127.0.0.53}} as the only DNS server and a list of search domains. This is the '''recommended''' mode of operation. The service users are advised to redirect the {{ic|/etc/resolv.conf}} file to the local stub DNS resolver file {{ic|/run/systemd/resolve/stub-resolv.conf}} managed by ''systemd-resolved''. This propagates the systemd managed configuration to all the clients. This can be done by replacing {{ic|/etc/resolv.conf}} with a symbolic link to the systemd stub: {{bc|# ln -sf /run/systemd/resolve/stub-resolv.conf /etc/resolv.conf}}
# Preserving ''resolv.conf'' - this mode preserves {{ic|/etc/resolv.conf}} and ''systemd-resolved'' is simply a client of this file. This mode is less disruptive as {{ic|/etc/resolv.conf}} can continue to be managed by other packages.

{{Note|The mode of operation of ''systemd-resolved'' is detected automatically, depending on whether {{ic|/etc/resolv.conf}} is a symlink to the local stub DNS resolver file or contains server names.}}

==== Setting DNS servers ====

{{Tip|In order to check the DNS actually used by ''systemd-resolved'', the command to use is:

	$ resolvectl status

 }}

===== Automatically =====

''systemd-resolved'' will work out of the box with a [[network manager]] using {{ic|/etc/resolv.conf}}. No particular configuration is required since ''systemd-resolved'' will be detected by following the {{ic|/etc/resolv.conf}} symlink. This is going to be the case with [[systemd-networkd]] or [[NetworkManager]].

However, if the [[DHCP]] and [[VPN]] clients use the [[Wikipedia:resolvconf|resolvconf]] program to set name servers and search domains (see [[openresolv#Users]] for a list of software that use ''resolvconf''), the additional package {{Pkg|systemd-resolvconf}} is needed to provide the {{ic|/usr/bin/resolvconf}} symlink.

{{Note|''systemd-resolved'' has a limited ''resolvconf'' interface and may not work with all the clients, see {{man|1|resolvectl|COMPATIBILITY WITH RESOLVCONF(8)}} for more information.}}

===== Manually =====

In local DNS stub mode, alternative DNS servers are provided in the {{man|5|resolved.conf}} file:

{{hc|/etc/systemd/resolved.conf.d/dns_servers.conf|2=
	[Resolve]
		DNS=91.239.100.100 89.233.43.71
 }}

{{Note|[[Network manager]]s have their own DNS settings that override ''systemd-resolved'''s default.}}

===== Fallback =====

If ''systemd-resolved'' does not receive DNS server addresses from the [[network manager]] and no DNS servers are configured [[#Manually|manually]] then ''systemd-resolved'' falls back to the fallback DNS addresses to ensure that DNS resolution always works.

{{Note|1=The fallback DNS are in this order: [[Alternative DNS services#Cloudflare|Cloudflare]], [[Alternative DNS services#Quad9|Quad9]] (without filtering and without DNSSEC) and [[Alternative DNS services#Google|Google]]; see the [https://git.archlinux.org/svntogit/packages.git/tree/trunk/PKGBUILD?h=packages/systemd#n103 systemd PKGBUILD] where the servers are defined.}}

The addresses can be changed by setting {{ic|1=FallbackDNS=}} in {{man|5|resolved.conf}}. E.g.:

{{hc|/etc/systemd/resolved.conf.d/fallback_dns.conf|2=
	[Resolve]
		FallbackDNS=127.0.0.1 ::1
 }}

To disable the fallback DNS funtionality set the {{ic|1=FallbackDNS}} option without specifying any addresses:

{{hc|/etc/systemd/resolved.conf.d/fallback_dns.conf|2=
	[Resolve]
		FallbackDNS=
 }}

==== DNSSEC ====

By default [[DNSSEC]] validation will only be enabled if the upstream DNS server supports it. If you want to always validate DNSSEC, thus breaking DNS resolution with name servers that do not support it, set {{ic|1=DNSSEC=true}}:

{{hc|/etc/systemd/resolved.conf.d/dnssec.conf|2=
	[Resolve]
		DNSSEC=true
 }}

{{Tip|If your DNS server does not support DNSSEC and you experience problems with the default allow-downgrade mode (e.g. [https://github.com/systemd/systemd/issues/10579 systemd issue 10579]), you can explicitly disable systemd-resolved's DNSSEC support by setting {{ic|1=DNSSEC=false}}.}}

Test DNSSEC validation by querying a domain with a invalid signature:

{{hc|$ resolvectl query sigfail.verteiltesysteme.net|
	sigfail.verteiltesysteme.net: resolve call failed: DNSSEC validation failed: invalid
 }}

Now test a domain with valid signature:

{{hc|$ resolvectl query sigok.verteiltesysteme.net|
	sigok.verteiltesysteme.net: 134.91.78.139

		-- Information acquired via protocol DNS in 266.3ms.
		-- Data is authenticated: yes
 }}

==== DNS over TLS ====

{{Expansion|How to test if DNS over TLS is used?}}

{{Warning|systemd-resolved only validates the DNS server certificate if it is issued for the server's IP address (a rare occurrence). DNS server certificates without an IP address are not checked making ''systemd-resolved'' vulnerable to man-in-the-middle attacks. See [https://github.com/systemd/systemd/issues/9397 systemd issue 9397].}}

DNS over TLS is disabled by default. To enable it change the {{ic|1=DNSOverTLS=}} setting in the {{ic|[Resolve]}} section in {{man|5|resolved.conf}}.

{{hc|/etc/systemd/resolved.conf.d/dns_over_tls.conf|2=
	[Resolve]
		DNSOverTLS=yes
 }}

{{Note|The used DNS server must support DNS over TLS otherwise all DNS requests will fail.}}

=== mDNS ===

''systemd-resolved'' is capable of working as a [[Wikipedia:Multicast DNS|multicast DNS]] resolver and responder.

The resolver provides [[hostname]] resolution using a "''hostname''.local" naming scheme.

mDNS will only be activated for the connection if both the systemd-resolved's global setting ({{ic|1=MulticastDNS=}} in {{man|5|resolved.conf}}) and the [[Network manager|network manager's]] per-connection setting is enabled. By default ''systemd-resolved'' enables mDNS responder, but both [[systemd-networkd]] and [[NetworkManager]] do not enable it for connections:

* For [[systemd-networkd]] the setting is {{ic|1=MulticastDNS=}} in the {{ic|[Network]}} section. See {{man|5|systemd.network}}.
* For [[NetworkManager]] the setting is {{ic|1=mdns=}} in the {{ic|[connection]}} section, see {{man|5|nm-settings}}. The values are {{ic|0}} - disabled, {{ic|1}} - resolver only, {{ic|2}} - resolver and responder. [https://cgit.freedesktop.org/NetworkManager/NetworkManager/tree/libnm-core/nm-setting-connection.h#n102]

{{Note|If [[Avahi]] has been installed, consider [[disabling]] {{ic|avahi-daemon.service}} and {{ic|avahi-daemon.socket}} to prevent conflicts with ''systemd-resolved''.}}

{{Tip|The default for all [[NetworkManager]] connections can be set by creating a configuration file in {{ic|/etc/NetworkManager/conf.d/}} and setting {{ic|1=connection.mdns=}} in the {{ic|[connection]}} section. For example the following will enable mDNS resolver for all connections:

	{{hc|/etc/NetworkManager/conf.d/mdns.conf|2=
		 [connection]
			 connection.mdns=1
	 }}

	See {{man|5|NetworkManager.conf}}.
 }}

If you plan to use mDNS and use a [[firewall]], make sure to open UDP port {{ic|5353}}.

=== LLMNR ===

[[Wikipedia:Link-Local Multicast Name Resolution|Link-Local Multicast Name Resolution]] is a [[hostname]] resolution protocol created by Microsoft.

LLMNR will only be activated for the connection if both the systemd-resolved's global setting ({{ic|1=LLMNR=}} in {{man|5|resolved.conf}}) and the [[Network manager|network manager's]] per-connection setting is enabled. By default ''systemd-resolved'' enables LLMNR responder; [[systemd-networkd]] and [[NetworkManager]] enable it for connections.

* For [[systemd-networkd]] the setting is {{ic|1=LLMNR=}} in the {{ic|[Network]}} section. See {{man|5|systemd.network}}.
* For [[NetworkManager]] the setting is {{ic|1=llmnr=}} in the {{ic|[connection]}} section, see {{man|5|nm-settings}}. The values are {{ic|0}} - disabled, {{ic|1}} - resolver only, {{ic|2}} - resolver and responder.

{{Tip|The default for all [[NetworkManager]] connections can be set by creating a configuration file in {{ic|/etc/NetworkManager/conf.d/}} and setting {{ic|1=connection.llmnr=}} in the {{ic|[connection]}} section. For example the following will disable LLMNR for all connections:

	{{hc|/etc/NetworkManager/conf.d/llmnr.conf|2=
		 [connection]
			 connection.llmnr=0
	 }}

	See {{man|5|NetworkManager.conf}}.
 }}

If you plan to use LLMNR and use a [[firewall]], make sure to open UDP and TCP ports {{ic|5355}}.

== Lookup ==

To query DNS records, mDNS or LLMNR hosts you can use the ''resolvectl'' utility.

For example, to query a DNS record:

{{hc|$ resolvectl query archlinux.org|
	archlinux.org: 2a01:4f8:172:1d86::1
		138.201.81.199

		-- Information acquired via protocol DNS in 48.4ms.
		-- Data is authenticated: no
 }}

See {{man|1|resolvectl|EXAMPLES}} for more examples.

