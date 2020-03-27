```
sample_ld_related -> ../../ld/sample_ld_related/
```

### STEPs
```bash
$ nm libxxx.so
0000000000201030 B __bss_start
0000000000201030 b completed.7698
                 w __cxa_finalize@@GLIBC_2.2.5
0000000000000580 t deregister_tm_clones
0000000000000610 t __do_global_dtors_aux
0000000000200e18 t __do_global_dtors_aux_fini_array_entry
0000000000201028 d __dso_handle
0000000000200e20 d _DYNAMIC
0000000000201030 D _edata
0000000000201038 B _end
000000000000069c T _fini
0000000000000650 t frame_dummy
0000000000200e10 t __frame_dummy_init_array_entry
0000000000000790 r __FRAME_END__
00000000000006e0 r __func__.2445
000000000000065a T func_in_libxxx
0000000000201000 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
00000000000006f0 r __GNU_EH_FRAME_HDR
0000000000000528 T _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U printf@@GLIBC_2.2.5
00000000000005c0 t register_tm_clones
                 U shm_open
0000000000201030 d __TMC_END__

$ strip libxxx.so

$ nm libxxx.so
nm: libxxx.so: no symbols

$ make app_ok
Making app.out ...
gcc -o app.out app.c -L. -Wl,-rpath=.		-lxxx -lrt		-U_LIB_USE_VAR_DEFINED_BY_APP

$ ./app.out
File:app.c       ,Func:main          ,Line:17  . 
File:libxxx.c    ,Func:func_in_libxxx,Line:26  . 
```
