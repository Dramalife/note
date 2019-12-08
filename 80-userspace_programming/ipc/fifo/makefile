default : all


ELF = fifo_seqnum_client fifo_seqnum_server
DEP_OBJ = dep_files/func_dep.o

$(ELF) : $(DEP_OBJ)

fifo_seqnum_client.o :
	gcc -c fifo_seqnum_client.c -I dep_files/

fifo_seqnum_server.o :
	gcc -c fifo_seqnum_server.c -I dep_files/

all : $(ELF)

clean :
	rm -rvf $(ELF)
	rm -f $(DEP_OBJ)
	rm -rvf ./*.o
