CC:=gcc

default:
	@echo "Usage:\nmake <target>!!!\n\n\n"

mem_leak:
	$(CC) -o sample_mem_leak.out \
	sample_mem_leak.c \
	-Wall -fsanitize=address -g

stack_heap_out_of_bounds:
	$(CC) -o sample_stack_heap_overflow.out \
	sample_stack_heap_overflow.c \
	-Wall -fsanitize=address -g

# stack_use_after_scop:
# 	$(CC) -o sample_stack_use_after_scope.out \
# 	sample_stack_use_after_scope.c \
# 	-Wall -fsanitize=address -g

global_mem_overflow:
	$(CC) -o sample_global_mem_overflow.out \
	sample_global_mem_overflow.c \
	-Wall -fsanitize=address -g

heap_use_after_free:
	$(CC) -o sample_heap_use_after_free.out \
	sample_heap_use_after_free.c \
	-Wall -fsanitize=address -g


clean:
	rm -rvf ./*.out
