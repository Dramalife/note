#### 1. Download

```
see "NOTE/tools/00-source_code_of_tools/clone_expat-2.2.0.sh"
```

#### 2. Configure && Make && Install

```bash
# cd expat
./buildconf.sh
./configure
make -j4
sudo make installlib
```

##### 2.1 error-doc(sudo make install)

```bash
make -C doc xmlwf.1
make[1]: Entering directory '/home/dramalife/note/70-gcc_gnu_compiler_collection/crosstool-ng/libexpat/expat/doc'
docbook2x-man xmlwf.xml
make[1]: docbook2x-man: Command not found
Makefile:13: recipe for target 'XMLWF.1' failed
make[1]: *** [XMLWF.1] Error 127
make[1]: Leaving directory '/home/dramalife/note/70-gcc_gnu_compiler_collection/crosstool-ng/libexpat/expat/doc'
Makefile:81: recipe for target 'doc/xmlwf.1' failed
make: *** [doc/xmlwf.1] Error 2
```
