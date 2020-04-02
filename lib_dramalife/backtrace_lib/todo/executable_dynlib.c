
/*
 * Make the lib executable
 */
#if (defined PROVIDE_MAIN_FUNCTION_IN_LIB) && (1 == PROVIDE_MAIN_FUNCTION_IN_LIB)

//MIF:Macro In File
#define MIF_REPLACE_RETURN_WITH_EXIT	0

// Designate ld in lib source
#if (defined DESIGNATE_LD_IN_LIB_FILE) && (1 == DESIGNATE_LD_IN_LIB_FILE)
//x86
asm(".pushsection .interp,\"a\"\n"
#if (defined __x86_64__) && (1 == __x86_64__)
		"        .string \"/lib/x86_64-linux-gnu/ld-2.27.so\"\n"
#elif (defined __i686__) && (1 == __i686__)
		"        .string \"/lib/i386-linux-gnu/ld-linux.so.2\"\n"
#else
#error NOT SUPPORTED YET !
#endif
		".popsection");
//ARM - TODO
//		(defined __ARM_EABI__) && (1 == __ARM_EABI__)
//		"        .string \"/lib/arm-linux-gnueabihf/ld-2.24.so\"\n"
#endif//DESIGNATE_LD_IN_LIB_FILE

/*
 * Add "main()" in library source, (and add "-Wl,-emain" option to gcc), Seg fault. 
 * (set PROVIDE_MAIN_FUNCTION_IN_LIB = 1 at ld option)
 *	Reason : library function "printf()" analysis err(gdb).
 * 	$ ./libbacktrace_funcs.so
 * 	Segmentation fault (core dumped)
 * Add "main()" in library source, and designate ld, printf ok, but Seg fault. 
 * (set PROVIDE_MAIN_FUNCTION_IN_LIB = 1 at ld option)
 *	Reason : lose standard exit function "_exit()", replace "return 0" with "_exit(0)" will fix this!
 *	$ /lib/x86_64-linux-gnu/ld-2.27.so ./libbacktrace_funcs.so
 * 	main,93.
 * 	Segmentation fault (core dumped)
 * Replace "return 0" with "_exit(0)" in "main()", and designate ld, printf ok, no fault, but depend on ld. 
 * (set MIF_REPLACE_RETURN_WITH_EXIT = 1 in this file)
 * 	$ /lib/x86_64-linux-gnu/ld-2.27.so ./libbacktrace_funcs.so
 * 	main,93.
 */
int main(void)
{
	printf("%s,%d. \n",__func__,__LINE__);
#if (0 == MIF_REPLACE_RETURN_WITH_EXIT)
	return 0;
#else
	_exit(0);
#endif
}

#if (defined PROVIDE_START_FUNCTION_IN_LIB) && (1 == PROVIDE_START_FUNCTION_IN_LIB)
void _start(void)
{
	int ret;
	ret = main();
	_exit(ret);
}
#endif//PROVIDE_START_FUNCTION_IN_LIB
#endif//PROVIDE_MAIN_FUNCTION_IN_LIB
