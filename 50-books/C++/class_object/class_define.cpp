/*
 * note "C++ basic - class" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ g++ --version
 * g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux iZ2zeeq1jai7e6qn7xqrnuZ 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Sat Apr 10 17:30:03 CST 2021
 * 	COPY FROM : https://www.runoob.com/cplusplus/cpp-classes-objects.html
 * Update : Sat Apr 10 17:30:03 CST 2021
 * 	Add pointer "this";
 *  
 * Update
 *
 */



#include <iostream>

using namespace std;

class Box
{
	public:
		double length;   // 长度
		double breadth;  // 宽度
		double height;   // 高度
		// 成员函数声明
		double get(void);
		void set( double len, double bre, double hei );
};
// 成员函数定义
double Box::get(void)
{
	return this->length * this->breadth * this->height;
}

void Box::set( double len, double bre, double hei)
{
	this->length = len;
	this->breadth = bre;
	this->height = hei;
}
int main( void )
{
	Box Box1;        // 声明 Box1，类型为 Box
	Box Box3;        // 声明 Box3，类型为 Box
	double volume = 0.0;     // 用于存储体积

	// box 1 详述
	Box1.height = 5.0; 
	Box1.length = 6.0; 
	Box1.breadth = 7.0;

	// box 1 的体积
	volume = Box1.height * Box1.length * Box1.breadth;
	cout << "Box1 的体积：" << volume <<endl;


	// box 3 详述
	Box3.set(16.0, 8.0, 12.0); 
	volume = Box3.get(); 
	cout << "Box3 的体积：" << volume <<endl;
	return 0;
}

