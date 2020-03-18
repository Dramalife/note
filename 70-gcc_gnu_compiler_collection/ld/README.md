## 1 gcc -Wl,<option>

### 1.1 as-needed
```
       --as-needed
       --no-as-needed
           This option affects ELF DT_NEEDED tags for dynamic libraries mentioned on the command line after the
           --as-needed option.  Normally the linker will add a DT_NEEDED tag for each dynamic library mentioned on
           the command line, regardless of whether the library is actually needed or not.  --as-needed causes a
           DT_NEEDED tag to only be emitted for a library that at that point in the link satisfies a non-weak
           undefined symbol reference from a regular object file or, if the library is not found in the DT_NEEDED
           lists of other needed libraries, a non-weak undefined symbol reference from another needed dynamic
           library.  Object files or libraries appearing on the command line after the library in question do not
           affect whether the library is seen as needed.  This is similar to the rules for extraction of object files
           from archives.  --no-as-needed restores the default behaviour.
```
```
...x.so : undefined reference to `shm_open'
```

## 2 gcc -Xlinker <option>

### 2.1 --unresolved-symbols=method
```
--unresolved-symbols=method
Determine how to handle unresolved symbols.  There are four possible values for method:

ignore-all
Do not report any unresolved symbols.

report-all
Report all unresolved symbols.  This is the default.

ignore-in-object-files
Report unresolved symbols that are contained in shared libraries, but ignore them if they come from regular object files.

ignore-in-shared-libs
Report unresolved symbols that come from regular object files, but ignore them if they come from shared libraries.  This can be useful when
creating a dynamic binary and it is known that all the shared libraries that it should be referencing are included on the linker's command
line.

The behaviour for shared libraries on their own can also be controlled by the --[no-]allow-shlib-undefined option.

Normally the linker will generate an error message for each reported unresolved symbol but the option --warn-unresolved-symbols can change this
to a warning.
```

