CFLAGS+=-fPIC -shared

SUBDIRS=system_lib ipc_lib

OBJS:=


all clean:
	make $(SUBDIRS) TARGET=$@

$(SUBDIRS):print
	make -C $@ separately-complile-to-objects
	OBJS=$@/build/objs/$@.o

print:
	echo "$(TARGET)"
	echo "$(OBJS)"
