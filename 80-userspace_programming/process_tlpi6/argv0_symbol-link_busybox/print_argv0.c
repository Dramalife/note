/*
 * URL	: https://github.com/dramalife/note.git
 * DATE	: 2020.03.10
 * BY	: Dramalife@live.com
 */
#include <stdio.h>

int main(int argc, char **argv)
{
	if(argc != 0)
		printf("ARGV[0]=%s \n",argv[0]);
	else
		return 0;

	printf(
			"Sample: \n"
			"ln -s a.out busyxxxping \n"
			"./busyxxxping \n"
	      );

	return 0;
}
