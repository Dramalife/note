> \# note "SBC kernel build (ROCK PI 4)" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Source : [wiki.radxa.com](https://wiki.radxa.com),[page](https://wiki.radxa.com/Rockpi4/dev/kernel-mainline)  
\#  
\# Init : 2019.09.15;  
\# Update   
\#  
  


<p>ROCK Pi 4 is officially supported in mainline kernel since v5.1 thanks to developer Akash Gajjar from Mentor. Below is how to build it on a X86 Linux host PC and run on ROCK Pi 4.
</p>

<h3><span class="mw-headline" id="Get_the_mainline_kernel_source">Get the mainline kernel source</span></h3>
<pre>   wget <a rel="nofollow" class="external free" href="https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/snapshot/linux-5.2-rc6.tar.gz">https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/snapshot/linux-5.2-rc6.tar.gz</a>
   tar -xvzf linux-5.2-rc6.tar.gz
   cd linux-5.1.15/
</pre>
<h3><span class="mw-headline" id="Install_toolchain_from_Linaro">Install toolchain from Linaro</span></h3>
<pre>   wget <a rel="nofollow" class="external free" href="https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-linux-gnu/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz">https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-linux-gnu/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz</a>
   sudo tar xvf gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz  -C /usr/local/
   export ARCH=arm64
   export CROSS_COMPILE=/usr/local/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
</pre>
<h3><span class="mw-headline" id="Build_kernel">Build kernel</span></h3>
<pre>   make menuconfig
</pre>
<ul>
<li>In the menu-config TUI: 
</li>
</ul>
<pre>*Navigate to Platform selection  ---&gt; Rockchip Platforms
*Select Rockchip Platforms
</pre>
<pre>   make -j6
</pre>
<p>copy <b>arch/arm64/boot/Image</b> and <b>arch/arm64/boot/dts/rk3399-rock-pi-4.dtb</b> to your ROCK Pi 4.
</p><p><b>If you run on debian you should Install the latest u-boot and kernel before Install mainline kernel on ROCK Pi 4.</b>
</p>
<h2><span class="mw-headline" id="Install_the_latest_u-boot_and_kernel">Install the latest u-boot and kernel</span></h2>
<pre>   apt-get install rockpi4b-rk-u-boot-latest
</pre>
<p>Manually run the u-boot flash script
</p>
<pre>   /usr/local/sbin/rockpi4b_upgrade_bootloader.sh
</pre>
<p><br />
Type <b>YES</b> to perform the uboot.img flashing.
</p><p>then install kernel  
</p>
<pre>   apt-get install linux-base
   apt-get install linux-4.4-latest
</pre>
<p><br />
After installation, check file <b>/boot/extlinux/extlinux.conf</b>. It lists all kernel version installed in ROCK Pi. The kernel corresponding to the first label is the newest version and the first boot option.
</p>
<h4><span class="mw-headline" id="Install_it_on_ROCK_Pi_4.">Install it on ROCK Pi 4.</span></h4>
<pre>   rockpi4# cp Image rk3399-rock-pi-4.dtb /boot/
   rockpi4#vi /boot/extlinux/extlinux.conf
</pre>
<ul>
<li>Change the contents to:
</li>
</ul>
<pre>  label kernel-mainline
  kernel /Image
  fdt /rk3399-rock-pi-4.dtb
  append earlycon=uart8250,mmio32,0xff1a0000 swiotlb=1 coherent_pool=1m earlyprintk console=ttyS2,1500000n8 rw root=PARTUUID=b921b045-1d rootfstype=ext4 init=/sbin/init rootwait
</pre>
<p>Reboot you will have the new kernel booting.
</p>

