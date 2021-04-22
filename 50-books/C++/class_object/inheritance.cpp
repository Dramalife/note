/*
 * note "C++ basic - inheritance" related file
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
 * Init : Sun Apr 18 17:56:39 CST 2021
 * 	COPY FROM : https://www.runoob.com/cplusplus/cpp-class-access-modifiers.html;
 * Update : Sun Apr 18 17:56:39 CST 2021
 *  
 * Update
 *
 */



#include<iostream>
#include<assert.h>

using namespace std;


class A{
	public:
		int a;
		A(){
			a1 = 1;
			a2 = 2;
			a3 = 3;
			a = 4;
		}
		void fun(){
			cout << a << endl;    //正确
			cout << a1 << endl;   //正确
			cout << a2 << endl;   //正确
			cout << a3 << endl;   //正确
		}
	public:
		int a1;
	protected:
		int a2;
	private:
		int a3;
};
class B : protected A{
	public:
		int a;
		B(int i){
			A();
			a = i;
		}
		void fun(){
			cout << a << endl;       //正确，public成员。
			cout << a1 << endl;       //正确，基类的public成员，在派生类中变成了protected，可以被派生类访问。
			cout << a2 << endl;       //正确，基类的protected成员，在派生类中还是protected，可以被派生类访问。
			cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
		}
};
int main(){
	B b(10);
	cout << b.a << endl;       //正确。public成员
	cout << b.a1 << endl;      //错误，protected成员不能在类外访问。
	cout << b.a2 << endl;      //错误，protected成员不能在类外访问。
	cout << b.a3 << endl;      //错误，private成员不能在类外访问。
	system("pause");
	return 0;
}

