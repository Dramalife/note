
### 1. Configure && Make

```bash
# 64 Bit only
./configure --disable-multilib
./configure --disable-multilib --prefix=/usr/local/gcc-6/
make -j4

```


### 2. ERRORs

#### 2.1 recipe for target 'xxx' failed :

```text
The virtual machine out of memory.
Try "make -j1" !!!
```

#### 2.2 error: dereferencing pointer to incomplete type ¡®struct ucontext¡¯

vi x86_64-pc-linux-gnu/libgcc/md-unwind-support.h +61

```diff
- struct ucontext *uc_ = context->cfa;
+ struct ucontext_t *uc_ = context->cfa; 
```

#### 2.3 msgfmt: error while loading shared libraries: libgettextsrc-0.19.8.1.so: cannot open shared object file: No such file or directory

```log
$ find /usr/ -name "*gettext*"
...
/usr/local/lib/libgettextsrc-0.19.8.1.so
...

$ msgfmt --version
msgfmt: error while loading shared libraries: libgettextlib-0.19.8.1.so: cannot open shared object file: No such file or directory

$ ldd /usr/local/bin/msgfmt 
	linux-vdso.so.1 (0x00007ffdf0727000)
	libgettextsrc-0.19.8.1.so => /usr/lib/libgettextsrc-0.19.8.1.so (0x00007efdba12d000)
	libgettextlib-0.19.8.1.so => not found
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007efdb9d3c000)
	libgettextlib-0.19.8.1.so => /usr/local/lib/libgettextlib-0.19.8.1.so (0x00007efdb99a9000)
	libiconv.so.2 => /usr/local/lib/libiconv.so.2 (0x00007efdb96c4000)
	/lib64/ld-linux-x86-64.so.2 (0x00007efdba58f000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007efdb9326000)
	libtinfo.so.5 => /lib/x86_64-linux-gnu/libtinfo.so.5 (0x00007efdb90fc000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007efdb8edd000)

# src and lib !!!
$ sudo ln -s /usr/local/lib/libgettextsrc-0.19.8.1.so /usr/lib/libgettextsrc-0.19.8.1.so
$ sudo ln -s /usr/local/lib/libgettextlib-0.19.8.1.so /usr/lib/libgettextlib-0.19.8.1.so
```

#### 2.4 aggregate ¡®sigaltstack handler_stack¡¯ has incomplete type and cannot be defined

```bash
../../.././libsanitizer/sanitizer_common/sanitizer_stoptheworld_linux_libcdep.cc: In function ¡®int __sanitizer::TracerThread(void*)¡¯:
../../.././libsanitizer/sanitizer_common/sanitizer_stoptheworld_linux_libcdep.cc:270:22: error: aggregate ¡®sigaltstack handler_stack¡¯ has incomplete type and cannot be defined
	struct sigaltstack handler_stack;
			   ^~~~~~~~~~~~~
Makefile:477: recipe for target 'sanitizer_stoptheworld_linux_libcdep.lo' failed
```

##### 2.4.0 [Ref Url : llvm.org](https://reviews.llvm.org/D35246)

##### 2.4.1 sanitizer_linux.h +24 +33

```diff
#include "sanitizer_platform.h"
#if SANITIZER_FREEBSD || SANITIZER_LINUX
#include "sanitizer_common.h"
#include "sanitizer_internal_defs.h"
#include "sanitizer_posix.h"
#include "sanitizer_platform_limits_posix.h"

struct link_map;  // Opaque type returned by dlopen().
- struct sigaltstack;

namespace __sanitizer {
	// Dirent structure for getdents(). Note that this structure is different from
	// the one in <dirent.h>, which is used by readdir().
	struct linux_dirent;

	// Syscall wrappers.
	uptr internal_getdents(fd_t fd, struct linux_dirent *dirp, unsigned int count);
-	uptr internal_sigaltstack(const struct sigaltstack* ss,
-			struct sigaltstack* oss);
+	uptr internal_sigaltstack(const void* ss, void* oss);

	uptr internal_sigprocmask(int how, __sanitizer_sigset_t *set,
			__sanitizer_sigset_t *oldset);

	// Linux-only syscalls.
#if SANITIZER_LINUX
	uptr internal_prctl(int option, uptr arg2, uptr arg3, uptr arg4, uptr arg5);
	// Used only by sanitizer_stoptheworld. Signal handlers that are actually used
	// (like the process-wide error reporting SEGV handler) must use
```

##### 2.4.2 sanitizer_linux.cc +634

```diff
#if SANITIZER_LINUX
	uptr internal_prctl(int option, uptr arg2, uptr arg3, uptr arg4, uptr arg5) {
		return internal_syscall(SYSCALL(prctl), option, arg2, arg3, arg4, arg5);
	}
#endif

-	uptr internal_sigaltstack(const struct sigaltstack *ss,
-		struct sigaltstack *oss) {
+	uptr internal_sigaltstack(const void *ss, void *oss) {

		return internal_syscall(SYSCALL(sigaltstack), (uptr)ss, (uptr)oss);
	}

	int internal_fork() {
#if SANITIZER_USES_CANONICAL_LINUX_SYSCALLS
		return internal_syscall(SYSCALL(clone), SIGCHLD, 0);
#else
		return internal_syscall(SYSCALL(fork));
```

##### 2.4.3 sanitizer_stoptheworld_linux_libcdep.cc +290

```diff
RAW_CHECK(AddDieCallback(TracerThreadDieCallback));
RAW_CHECK(AddDieCallback(TracerThreadDieCallback));

ThreadSuspender thread_suspender(internal_getppid(), tracer_thread_argument);
// Global pointer for the signal handler.
thread_suspender_instance = &thread_suspender;

// Alternate stack for signal handling.
InternalScopedBuffer<char> handler_stack_memory(kHandlerStackSize);
- struct sigaltstack handler_stack;
+ stack_t handler_stack;
internal_memset(&handler_stack, 0, sizeof(handler_stack));
handler_stack.ss_sp = handler_stack_memory.data();
handler_stack.ss_size = kHandlerStackSize;
internal_sigaltstack(&handler_stack, nullptr);

// Install our handler for synchronous signals. Other signals should be
// blocked by the mask we inherited from the parent thread.
```

##### 2.3.4 tsan_platform_linux.cc +291

```diff
#if !SANITIZER_GO
// Extract file descriptors passed to glibc internal __res_iclose function.
// This is required to properly "close" the fds, because we do not see internal
// closes within glibc. The code is a pure hack.
int ExtractResolvFDs(void *state, int *fds, int nfd) {
#if SANITIZER_LINUX && !SANITIZER_ANDROID
	int cnt = 0;
-	__res_state *statp = (__res_state*)state;
+	struct __res_state *statp = (struct __res_state*)state;
	for (int i = 0; i < MAXNS && cnt < nfd; i++) {
		if (statp->_u._ext.nsaddrs[i] && statp->_u._ext.nssocks[i] != -1)
			fds[cnt++] = statp->_u._ext.nssocks[i];
	}
	return cnt;
#else
	return 0;
#endif
```


#### 2.5 invalid use of incomplete type ¡®struct _Jv_catch_fpe(int, siginfo_t*, void*)::ucontext¡¯

```bash
In file included from ../.././libjava/prims.cc:26:0:
../.././libjava/prims.cc: In function ¡®void _Jv_catch_fpe(int, siginfo_t*, void*)¡¯:
./include/java-signal.h:32:26: error: invalid use of incomplete type ¡®struct _Jv_catch_fpe(int, siginfo_t*, void*)::ucontext¡¯
   gregset_t &_gregs = _uc->uc_mcontext.gregs;    \
		    	  ^
# struct ucontext > struct ucontext_t
```

#### 2.6 libiconv.so.2

```bash
sudo ln -s /usr/local/lib/libiconv.so.2 /usr/lib/libiconv.so.2
```

### 3. Finished

```bash
dramalife@server:~/note/70-gcc_gnu_compiler_collection/crosstool-ng/bin-gcc-6.3.0 $ ./bin/gcc --version
gcc (GCC) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

#### 4. Install Error(can not change "prefix" that in "Makefile" directly)

```bash
 /bin/mkdir -p '/usr/local/gcc-6/lib/../lib64'
  /bin/bash ./libtool   --mode=install /usr/bin/install -c   libcc1.la '/usr/local/gcc-6/lib/../lib64'
  libtool: install: error: cannot install `libcc1.la' to a directory not ending in /usr/local/lib/../lib64
  Makefile:375: recipe for target 'install-cc1libLTLIBRARIES' failed

# Re-configure :
# "./configure --disable-multilib --prefix=/usr/local/gcc-6/"
# if you want to change "prefix".
```
