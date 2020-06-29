// https://www.cnblogs.com/damaohai/p/11606950.html
#include <stdio.h>
#include <stdint.h>

#pragma pack(1)
typedef struct {
	/*成员对齐*/
	int a;     //长度4 < 1 **按1对齐**；偏移量为0；存放位置区间[0,3]
	char b;    //长度1 = 1 **按1对齐**；偏移量为4；存放位置区间[4]
	short c;   //长度2 > 1 **按1对齐**；偏移量为5；存放位置区间[5,6]
	char d;    //长度1 = 1 **按1对齐**；偏移量为6；存放位置区间[7]
	/*整体对齐*/
	//整体对齐系数 = min（对齐系数1，最大成员长度4） = 1，无需对齐，整体大小为8；
}test_pack1;
#pragma pack()


#pragma pack(2)
typedef struct {   /*成员对齐*/
	int a;     //长度4 > 2 **按2对齐**；偏移量为0；存放位置区间[0,3]
	char b;    //长度1 < 2 **按1对齐**；偏移量为4；存放位置区间[4]
	short c;   //长度2 = 2 **按2对齐**；偏移量要提升到2的倍数6；存放位置区间[6,7]
	char d;    //长度1 < 2 **按1对齐**；偏移量为7；存放位置区间[8]；共九个字节
	/*整体对齐*/
	//整体对齐系数 = min（对齐系数2，最大成员长度4） = 2，将9提升到2的倍数10，整体大小为10；
}test_pack2;
#pragma pack()

#pragma pack(4)
typedef struct {   /*成员对齐*/
	int a;     //长度4 = 4 **按4对齐**；偏移量为0；存放位置区间[0,3]
	char b;    //长度1 < 4 **按1对齐**；偏移量为4；存放位置区间[4]
	short c;   //长度2 < 4 **按2对齐**；偏移量要提升到2的倍数6；存放位置区间[6,7]
	char d;    //长度1 < 4 **按1对齐**；偏移量为7；存放位置区间[8]；总大小为9
	/*整体对齐*/
	//整体对齐系数 = min（对齐系数4，最大成员长度4） = 4，将9提升到4的倍数12，整体大小为12；
}test_pack4;
#pragma pack()

#pragma pack(8)
typedef struct {   /*成员对齐*/
	int a;     //长度4 < 8 **按4对齐**；偏移量为0；存放位置区间[0,3]
	char b;    //长度1 < 8 **按1对齐**；偏移量为4；存放位置区间[4]
	short c;   //长度2 < 8 **按2对齐**；偏移量要提升到2的倍数6；存放位置区间[6,7]
	char d;    //长度1 < 8 **按1对齐**；偏移量为7；存放位置区间[8]，总大小为9
	/*整体对齐*/
	//整体对齐系数 = min（对齐系数8，最大成员长度4） = 4，将9提升到4的倍数12，整体大小为12；
}test_pack8;
#pragma pack()

test_pack1 pack1 = {0x11111111, 0x22, 0x3333, 0x44};
uint8_t *ptrPack1 = (uint8_t *)&pack1;
test_pack2 pack2 = {0x11111111, 0x22, 0x3333, 0x44};
uint8_t *ptrPack2 = (uint8_t *)&pack2;
test_pack4 pack4 = {0x11111111, 0x22, 0x3333, 0x44};
uint8_t *ptrPack4 = (uint8_t *)&pack4;
test_pack8 pack8 = {0x11111111, 0x22, 0x3333, 0x44};
uint8_t *ptrPack8 = (uint8_t *)&pack8;

int main(int argc, char *argv[])
{
	int i = 0;
	printf("#pragma pack(1) \tsize:%2d,\t", sizeof(pack1));
	for(i=0; i<sizeof(pack1); i++)
	{
		printf("%02x", ptrPack1[i]);
	}
	printf("\r\n");

	printf("#pragma pack(2) \tsize:%2d,\t", sizeof(pack2));
	for(i=0; i<sizeof(pack2); i++)
	{
		printf("%02x", ptrPack2[i]);
	}
	printf("\r\n");

	printf("#pragma pack(4) \tsize:%2d,\t", sizeof(pack4));
	for(i=0; i<sizeof(pack4); i++)
	{
		printf("%02x", ptrPack4[i]);
	}
	printf("\r\n");

	printf("#pragma pack(8) \tsize:%d,\t", sizeof(pack8));
	for(i=0; i<sizeof(pack8); i++)
	{
		printf("%02x", ptrPack8[i]);
	}
	printf("\r\n"); 
	return 0;
}

