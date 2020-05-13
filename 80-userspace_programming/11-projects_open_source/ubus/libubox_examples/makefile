INCLUDE=-I ./headers_libubox-2018-11-16-4382c76d/headers_libubox-2018-11-16-4382c76d/libubox

runqueue-sample: .prepare
	gcc -o runqueue-example.out runqueue-example.c $(INCLUDE) -lubox


INC_LIBUBOX=headers_libubox-2018-11-16-4382c76d
GIT_LIBUBOX=https://gitee.com/Dramalife/binary_compiled_gitee.git
.prepare:
	../../../../lib_dramalife/exec_files/git_sparse_clone.sh $(INC_LIBUBOX) $(GIT_LIBUBOX)

clean:
	rm -rvf ./*.out
	rm -rf $(INC_LIBUBOX)
