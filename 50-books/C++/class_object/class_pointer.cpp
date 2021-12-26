/*
 * note "C++ class pointer" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 *
 * This file is part of [note](https://github.com/Dramalife/note.git)
 *
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 *
 * $ uname -a
 * Linux iZ2zeeq1jai7e6qn7xqrnuZ 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1
 * 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 *
 * Init : Sun Dec 26 10:57:15 CST 2021
 *  * ;
 * Update : Sun Dec 26 10:57:15 CST 2021
 *
 * Update
 *
 */
#include <iostream>

using namespace std;

class Box {
 public:
  // 构造函数定义
  Box(double l = 2.0, double b = 2.0, double h = 2.0) {
    cout << "Constructor called." << endl;
    length = l;
    breadth = b;
    height = h;
  }
  double Volume() { return length * breadth * height; }

 private:
  double length;   // Length of a box
  double breadth;  // Breadth of a box
  double height;   // Height of a box
};

int main(void) {
  Box Box1(3.3, 1.2, 1.5);  // Declare box1
  Box Box2(8.5, 6.0, 2.0);  // Declare box2
  Box* ptrBox;              // Declare pointer to a class.

  // 保存第一个对象的地址
  ptrBox = &Box1;

  // 现在尝试使用成员访问运算符来访问成员
  cout << "Volume of Box1: " << ptrBox->Volume() << endl;

  // 保存第二个对象的地址
  ptrBox = &Box2;

  // 现在尝试使用成员访问运算符来访问成员
  cout << "Volume of Box2: " << ptrBox->Volume() << endl;

  return 0;
}
