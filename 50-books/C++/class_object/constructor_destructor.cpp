/*
 * note "C++ basic - constructor/destructor" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ g++ --version
 * g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
 * Copyright (C) 2019 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux NanoPi-M4 4.19.111 #4 SMP PREEMPT Tue Oct 20 13:17:49 CST 2020 aarch64 aarch64 aarch64 GNU/Linux
 * ;
 * 
 * Init : Sun Apr 18 18:55:16 CST 2021
 *  	COPY FROM : https://www.runoob.com/cplusplus/cpp-constructor-destructor.html;
 * Update : Sun Apr 18 18:55:16 CST 2021
 * 	Add debug printing before "constructor" and after "destructor";
 *  
 * Update
 *
 */



#include <iostream>

using namespace std;

class Line
{
	public:
		void setLength( double len );
		double getLength( void );
		Line(double len);	// 这是构造函数声明
		~Line();		// 这是析构函数声明

	private:
		double length;
};

// 成员函数定义，包括构造函数
Line::Line( double len)
{
	cout << "Object is being created, length = " << len << endl;
	length = len;
}
Line::~Line(void)
{
	cout << "Object is being deleted" << endl;
}

void Line::setLength( double len )
{
	length = len;
}

double Line::getLength( void )
{
	return length;
}

int test_func( void )
{
	Line line(10.0);

	// 获取默认设置的长度
	cout << "Length of line : " << line.getLength() <<endl;
	// 再次设置长度
	line.setLength(6.0); 
	cout << "Length of line : " << line.getLength() <<endl;

	return 0;
}

// 程序的主函数
int main( void )
{
	cout << __func__ << ", " <<__LINE__ << endl;
	test_func();
	cout << __func__ << ", " <<__LINE__ << endl;

	return 0;
}

