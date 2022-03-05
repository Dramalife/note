# http://blog.chinaunix.net/uid-20648944-id-4005866.html

all: .prepare .compile .copy_sym .strip .addsection
clean: .prepare

.prepare:
	rm -rvf test_symbol*
.compile:
	make -C as_sample test.symbol
	cp as_sample/test_symbol.out ./
.copy_sym:
	objcopy --only-keep-debug test_symbol.out test_symbol.debug
.strip:
	cp test_symbol.out test_symbol.stripped
	strip test_symbol.stripped
.addsection:
	objcopy --add-gnu-debuglink=test_symbol.debug test_symbol.addsection
	objdump -s -j .gnu_debuglink test_symbol.addsection

gdb.not_stripped:
	gdb test_symbol.out
gdb.stripped_spec_sym:
	gdb -s test_symbol.debug -e test_symbol.stripped
gdb.stripped:
	gdb -e test_symbol.stripped
gdb.addsection:
	gdb test_symbol.addsection
