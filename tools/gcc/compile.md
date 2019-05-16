## crosstool(交叉工具)
编译器 -- 指令集架构 -- 处理器架构 -- CPU型号 ？

### 1. 处理器架构
四大 CPU 架构：ARM，X86，MIPS，PowerPC

### 2. 指令集架构（ISA)
包括机器指令和汇编指令  
RISC: 指令少，指令单周期执行，目标代码更大；ARM，MIPS，PowerPC
CISC: 指令复杂，指令周期长，目标代码多；X86，

#### 2.1 指令集架构-ARM
|Architecture |Family|
|--|--|
|ARMv1 |ARM1 |
|ARMv2 |ARM2, ARM3 |
|ARMv3 |ARM6, ARM7 |
|ARMv4 |StrongARM,ARM7TDMI, ARM9TDMI |
|ARMv5 |ARM7EJ, ARM9E, ARM10E, XScale |
|ARMv6 |ARM11, Cortex-M |
|ARMv7 |Cortex-A, Cortex-M, Cortex-R |
|ARMv8 | |

### 3. 编译器(汇编)，指令集架构（机器码，汇编） 与 处理器架构三者关系

### 4. CPU info
#### 4.1 RPI
```bash
root@NETAC-SERVER:/usr # cat /proc/cpuinfo 
processor	: 0
model name	: ARMv7 Processor rev 4 (v7l)
BogoMIPS	: 38.40
Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae evtstrm crc32 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xd03
CPU revision	: 4

processor	: 1
model name	: ARMv7 Processor rev 4 (v7l)
BogoMIPS	: 38.40
Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae evtstrm crc32 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xd03
CPU revision	: 4

processor	: 2
model name	: ARMv7 Processor rev 4 (v7l)
BogoMIPS	: 38.40
Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae evtstrm crc32 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xd03
CPU revision	: 4

processor	: 3
model name	: ARMv7 Processor rev 4 (v7l)
BogoMIPS	: 38.40
Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae evtstrm crc32 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xd03
CPU revision	: 4

Hardware	: BCM2835
Revision	: a22082
Serial		: 0000000096f521d8

```

#### 4.2 OPI(全志H2)
```bash
root@OrangePizero:~ # cat /proc/cpuinfo 
Processor	: ARMv7 Processor rev 5 (v7l)
processor	: 0
BogoMIPS	: 11858.82

processor	: 1
BogoMIPS	: 11858.82

processor	: 2
BogoMIPS	: 11858.82

processor	: 3
BogoMIPS	: 11858.82

Features	: swp half thumb fastmult vfp edsp thumbee neon vfpv3 tls vfpv4 idiva idivt 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xc07
CPU revision	: 5

Hardware	: sun8i
Revision	: 0000
Serial		: 148778310c521000008f

```

### 5. Errors(busybox compile)

```bash
gcc: error trying to exec 'cc1': execvp: No such file or directory  
```
/usr/lib  

```bash
a.c:1:19: fatal error: stdio.h: No such file or directory
 #include <stdio.h>
```
/lib

