CC:=gcc
SOURCE_PATH?="../src_sample/"

default:
	@echo "Usage:\nmake <target>!!!\n\n\n"
all: mem_leak stack_heap_out_of_bounds global_mem_overflow heap_use_after_free

mem_leak:
	$(CC) -o sample_mem_leak.out \
		$(SOURCE_PATH)/sample_mem_leak.c \
		-Wall -fsanitize=address -g

stack_heap_out_of_bounds:
	$(CC) -o sample_stack_heap_overflow.out \
		$(SOURCE_PATH)/sample_stack_heap_overflow.c \
		-Wall -fsanitize=address -g

# stack_use_after_scop:
# 	$(CC) -o sample_stack_use_after_scope.out \
# 	$(SOURCE_PATH)/sample_stack_use_after_scope.c \
# 	-Wall -fsanitize=address -g

global_mem_overflow:
	$(CC) -o sample_global_mem_overflow.out \
		$(SOURCE_PATH)/sample_global_mem_overflow.c \
		-Wall -fsanitize=address -g

heap_use_after_free:
	$(CC) -o sample_heap_use_after_free.out \
		$(SOURCE_PATH)/sample_heap_use_after_free.c \
		-Wall -fsanitize=address -g


clean:
	rm -rvf ./*.out
