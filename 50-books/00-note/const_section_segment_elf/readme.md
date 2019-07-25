### Process of analysis
#### 1. Difference
	const char *ptr = "abc";  //ptr is a pointer to const char.
	char const *ptr;  
	const char arry = "abc";

	char * const ptr; //ptr is a const pointer to char.

#### 2. Test - Segment Fault
	/* seg fault : const char *p2cc = "aaa" */
	/* no fault  : const char p2cc[] = "aaa" */
	sprintf(p2cc,"3333");

#### 3.1 section ?
	.txt
	.data
	.bss

#### 3.2 Mem (some not properly)
	heap
	stack
	segment

#### 4. ELF
	elf - process (section)
	process - kernel (MMU)

