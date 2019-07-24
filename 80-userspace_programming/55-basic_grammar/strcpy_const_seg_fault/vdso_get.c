/*

   $cat /proc/self/maps
   ...
   b7fdc000-b7fde000 r-xp 00000000 00:00 0          [vdso]
   ...

   dump linux-vdso.so.1(linux-gate.so.1) from "/proc/self/mem"

   Ref Url:https://blog.csdn.net/luozhaotian/article/details/79609077
   Ref Url:https://blog.csdn.net/maimang1001/article/details/17331731

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vdso_get(int argc, char **argv)
{
	char buf[256], *mem;
	const char *range_name;
	FILE *rd, *wr;
	long long start_addr, end_addr;

	/* Open file for writing the vdso data to */
	if (argc != 3)
	{
		fprintf(stderr,
				"Usage: %s <file> <string>\n"
				"\t<file>: File to write the vdso data to.\n"
				"\t<string>: Name of the mapped in region, e.g. vdso\n",
				argv[0]);

		abort();
	}

	range_name = argv[2];

	if (!(wr = fopen(argv[1], "w")))
	{
		perror("Error: fopen() - output file");
		abort();
	}

	/* Get this process' memory layout */
	if (!(rd = fopen("/proc/self/maps", "r")))
	{
		perror("Error: fopen() - /proc/self/maps");
		abort();
	}

	/* Find the line in /proc/self/maps that contains
	   the substring [vdso] * */
	while (fgets(buf, sizeof(buf), rd))
	{
		if (strstr(buf, range_name))
			break;
	}

	fclose(rd);

	/* Locate the end memory range for [vdso] */
	end_addr = strtoll((strchr(buf, '-') + 1), NULL, 16);

	/* Terminate the string so we can get the start
	   address really easily * */
	*(strchr(buf, '-')) = '\0';
	start_addr = strtoll(buf, NULL, 16);

	fwrite((void*)start_addr, 1, end_addr-start_addr, wr);
	fclose(wr);

	printf("Start: %p\nEnd: %p\nBytes: %d\n",
			(void *)start_addr, (void *)end_addr, (int)(end_addr -
				start_addr));

	return 0;
}

