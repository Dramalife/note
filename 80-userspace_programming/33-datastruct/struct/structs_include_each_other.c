

struct B;    //�Խṹ��B���в���������

//�ṹ��A�а���ָ��ṹ��B��ָ��
struct A
{
	struct B *partner;
	//other members;
};

//�ṹ��B�а���ָ��ṹ��A��ָ�룬��A�������BҲ��֮��������
struct B
{
	struct A *partner;
	//other members;
};



//#if DL_NOTE_STRUCT_PART_BUILD == 1
int main(void)
//#else
//int main_structs_include_each_other(void)
//#endif
{
	return 0;
}
