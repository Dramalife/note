/*
 * note "C++ static members" related file
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
 * Init : Sun Dec 26 10:55:31 CST 2021
 *   Copy from: https://www.runoob.com/cplusplus/cpp-static-members.html;
 * Update : Sun Dec 26 10:55:31 CST 2021
 *
 * Update
 *
 */
#include <iostream>

using namespace std;

class Box {
 public:
  static int objectCount;
  // 构造函数定义
  Box(double l = 2.0, double b = 2.0, double h = 2.0) {
    cout << "Constructor called." << endl;
    length = l;
    breadth = b;
    height = h;
    // 每次创建对象时增加 1
    objectCount++;
  }
  double Volume() { return length * breadth * height; }
  static int getCount() { return objectCount; }

 private:
  double length;   // 长度
  double breadth;  // 宽度
  double height;   // 高度
};

// 初始化类 Box 的静态成员
int Box::objectCount = 0;

int main(void) {
  // 在创建对象之前输出对象的总数
  cout << "Inital Stage Count: " << Box::getCount() << endl;

  Box Box1(3.3, 1.2, 1.5);  // 声明 box1
  Box Box2(8.5, 6.0, 2.0);  // 声明 box2

  // 在创建对象之后输出对象的总数
  cout << "Final Stage Count: " << Box::getCount() << endl;

  return 0;
}
