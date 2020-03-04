gcc -Wl,<option>

as-needed
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
