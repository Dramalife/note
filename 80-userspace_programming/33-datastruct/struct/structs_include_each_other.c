

struct B;    //对结构体B进行不完整声明

//结构体A中包含指向结构体B的指针
struct A
{
	struct B *partner;
	//other members;
};

//结构体B中包含指向结构体A的指针，在A声明完后，B也随之进行声明
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
