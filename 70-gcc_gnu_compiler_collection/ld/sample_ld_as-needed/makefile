# 
#  [note](github.com/dramalife/note.git)
#  Dramalife@live.com
#  Init : 2020.03.04
# 

all : dynlib app_out

app_out:
	gcc -o app.out app.c -Wl,-rpath=. -L. -lxxx -lrt

dynlib:
	gcc -o libxxx.so libxxx.c -fPIC -shared

clean:
	rm -rvf ./*.out ./*.so


######### Targets for testing !!! #########
# Target - no "-lrt"
app_err_lrt:
	gcc -o app.out app.c -Wl,-rpath=. -L. -lxxx
# Target - add "-Wl,--as-needed"
app_err_asneeded:
	gcc -o app.out app.c -L. -Wl,-rpath=. -Wl,--as-needed -lrt -lxxx
