// https://www.cnblogs.com/damaohai/p/11606950.html
#include <stdio.h>
#include <stdint.h>

#pragma pack(1)
typedef struct {
	/*��Ա����*/
	int a;     //����4 < 1 **��1����**��ƫ����Ϊ0�����λ������[0,3]
	char b;    //����1 = 1 **��1����**��ƫ����Ϊ4�����λ������[4]
	short c;   //����2 > 1 **��1����**��ƫ����Ϊ5�����λ������[5,6]
	char d;    //����1 = 1 **��1����**��ƫ����Ϊ6�����λ������[7]
	/*�������*/
	//�������ϵ�� = min������ϵ��1������Ա����4�� = 1��������룬�����СΪ8��
}test_pack1;
#pragma pack()


#pragma pack(2)
typedef struct {   /*��Ա����*/
	int a;     //����4 > 2 **��2����**��ƫ����Ϊ0�����λ������[0,3]
	char b;    //����1 < 2 **��1����**��ƫ����Ϊ4�����λ������[4]
	short c;   //����2 = 2 **��2����**��ƫ����Ҫ������2�ı���6�����λ������[6,7]
	char d;    //����1 < 2 **��1����**��ƫ����Ϊ7�����λ������[8]�����Ÿ��ֽ�
	/*�������*/
	//�������ϵ�� = min������ϵ��2������Ա����4�� = 2����9������2�ı���10�������СΪ10��
}test_pack2;
#pragma pack()

#pragma pack(4)
typedef struct {   /*��Ա����*/
	int a;     //����4 = 4 **��4����**��ƫ����Ϊ0�����λ������[0,3]
	char b;    //����1 < 4 **��1����**��ƫ����Ϊ4�����λ������[4]
	short c;   //����2 < 4 **��2����**��ƫ����Ҫ������2�ı���6�����λ������[6,7]
	char d;    //����1 < 4 **��1����**��ƫ����Ϊ7�����λ������[8]���ܴ�СΪ9
	/*�������*/
	//�������ϵ�� = min������ϵ��4������Ա����4�� = 4����9������4�ı���12�������СΪ12��
}test_pack4;
#pragma pack()

#pragma pack(8)
typedef struct {   /*��Ա����*/
	int a;     //����4 < 8 **��4����**��ƫ����Ϊ0�����λ������[0,3]
	char b;    //����1 < 8 **��1����**��ƫ����Ϊ4�����λ������[4]
	short c;   //����2 < 8 **��2����**��ƫ����Ҫ������2�ı���6�����λ������[6,7]
	char d;    //����1 < 8 **��1����**��ƫ����Ϊ7�����λ������[8]���ܴ�СΪ9
	/*�������*/
	//�������ϵ�� = min������ϵ��8������Ա����4�� = 4����9������4�ı���12�������СΪ12��
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

