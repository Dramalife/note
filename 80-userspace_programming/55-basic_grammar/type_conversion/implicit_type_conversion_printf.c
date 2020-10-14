#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*****
 * 例：
 * long型数据内存拷贝到数组中，以16进制查看每个字节的数据，有时出现如“ffffffe2”的数据。
 * 实际数据没有问题，问题出在printf("%x")时的隐式类型转换(char -> int).
 *
 * 重点：
 * 隐式类型转换(char -> int);
 */

int main(void)
{
	printf("size_long=%d\n", (int)sizeof(long));

	long l1 = 123456; // hex:0x1E240

	char al1[8] = {0};
	//uint8_t al1[8] = {0};

	memcpy(al1, &l1, sizeof(l1));

	long l2 = 0;
	memcpy(&l2, al1, sizeof(l2));


	printf("l1=%ld,l2=%ld,al1={0x%02x %02x %02x %02x %02x %02x %02x %02x}\n", l1, l2
			,(uint8_t)al1[7]
			,(uint8_t)al1[6]
			,(uint8_t)al1[5]
			,(uint8_t)al1[4]
			,(uint8_t)al1[3]
			,(uint8_t)al1[2]
			,(uint8_t)al1[1]
			,(uint8_t)al1[0]
	      );

	printf("\nR:\n");
	printf("%x \n", al1[1]);		// ffffffe2
	printf("%x \n", (int)al1[1]);		//
	printf("%x \n", (uint8_t)al1[1]);	// e2
	printf("%x \n", (int) ((uint8_t)al1[1]));	// e2
	printf("%d \n", al1[1]);		// -30

	return 0;
}
