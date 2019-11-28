## doc_create_lib/
generate lib\*.so
app load lib\*.so

## doc_link_lib/
link apps with lib\*.so

## elf-loader_symbol -> ../../80-userspace_programming/00-libc_sample/man3_dlfcn_dlopen/elf-loader/
elf loader

## sample_app_use_lib_backtrace_related/
sample - link app with libbacktrace.so

## sample_make_lib_executable -> sample_app_use_lib_backtrace_related/lib_shared//
make lib\*.so executable
