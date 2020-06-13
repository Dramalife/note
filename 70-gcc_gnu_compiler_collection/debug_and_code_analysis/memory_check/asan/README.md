> https://github.com/google/sanitizers/wiki/AddressSanitizer

### 
- detected memory leaks
- heap-buffer-overflow
- stack-buffer-overflow
- global-buffer-overflow
- heap-use-after-free
- initialization-order-fiasco

###
|No|Source File|Description|
|--|--|--|
|0|sample_global_mem_overflow.c	  |global-buffer-overflow|
|1|sample_heap_use_after_free.c   |p-use-after-free	|
|2|sample_mem_leak.c              |detected memory leaks|
|3|sample_stack_heap_overflow.c   |heap-use-after-free	|
|4|sample_stack_use_after_scope.c |xxx|
