all:client server
client: .prepare
	gcc -o client.out client.c count.c -I ./include_libubox/ -I ./include_ubus/ -lubus -lubox
server: .prepare
	gcc -o server.out server.c count.c -I ./include_libubox/ -I ./include_ubus/ -lubus -lubox

.prepare:
	ln -sf ../../../../lib_dramalife/extern_headers/include_libubox/ .
	ln -sf ../../../../lib_dramalife/extern_headers/include_ubus/ .


clean:
	rm -rvf ./*.out
	rm -f include_libubox
	rm -f include_ubus
