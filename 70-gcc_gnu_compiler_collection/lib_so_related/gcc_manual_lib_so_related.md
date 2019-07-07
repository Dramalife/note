##### man gcc
	Compilation can involve up to four stages: preprocessing, compilation proper, assembly and linking, always in that order.  GCC is
	capable of preprocessing and compiling several files either into several assembler input files, or into one assembler input file; then
	each assembler input file produces an object file, and linking combines all the object files (those newly compiled, and those specified
	as input) into an executable file.



##### -fpic
	Generate position-independent code (PIC) suitable for use in a shared library, if supported for the target machine.  Such code
	accesses all constant addresses through a global offset table (GOT).  The dynamic loader resolves the GOT entries when the program
	starts (the dynamic loader is not part of GCC; it is part of the operating system).  If the GOT size for the linked executable
	exceeds a machine-specific maximum size, you get an error message from the linker indicating that -fpic does not work; in that case,
	recompile with -fPIC instead.  (These maximums are 8k on the SPARC and 32k on the m68k and RS/6000.  The 386 has no such limit.)

	Position-independent code requires special support, and therefore works only on certain machines.  For the 386, GCC supports PIC for
	System V but not for the Sun 386i.  Code generated for the IBM RS/6000 is always position-independent.

	When this flag is set, the macros "__pic__" and "__PIC__" are defined to 1.

##### -fPIC
	If supported for the target machine, emit position-independent code, suitable for dynamic linking and avoiding any limit on the size
	of the global offset table.  This option makes a difference on the m68k, PowerPC and SPARC.

	Position-independent code requires special support, and therefore works only on certain machines.

	When this flag is set, the macros "__pic__" and "__PIC__" are defined to 2.

##### -shared
	Produce a shared object which can then be linked with other objects to form an executable.  Not all systems support this option.
	For predictable results, you must also specify the same set of options used for compilation (-fpic, -fPIC, or model suboptions) when
	you specify this linker option.[1]


