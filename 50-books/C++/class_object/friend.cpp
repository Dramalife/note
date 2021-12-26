/*
 * note "C++ basic - class - friend" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 *
 * This file is part of [note](https://github.com/Dramalife/note.git)
 *
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
 * Copyright (C) 2019 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.;
 *
 * $ uname -a
 * Linux NanoPi-M4 4.19.111 #4 SMP PREEMPT Tue Oct 20 13:17:49 CST 2020 aarch64
 * aarch64 aarch64 GNU/Linux
 * ;
 *
 * Init : Sat Apr 24 13:14:44 CST 2021
 *  	COPY FROM : https://www.runoob.com/cplusplus/cpp-friend-functions.html;
 * Update : Sat Apr 24 13:14:44 CST 2021
 * 	Add pri
 *
 */

#include <iostream>

using namespace std;

class Box {
 private:  // default
  double width;

 public:
  friend void printWidth(Box box);
  friend class BigBox;
  void setWidth(double wid);
};

class BigBox {
 public:
  void Print(int width, Box& box) {
    // BigBox是Box的友元类，它可以直接访问Box类的任何成员
    box.setWidth(width);
    cout << "Width of box : " << box.width << endl;
  }
};

// 成员函数定义
void Box::setWidth(double wid) {
  width = wid;
}

// 请注意：printWidth() 不是任何类的成员函数
void printWidth(Box box) {
  /* 因为 printWidth() 是 Box 的友元，它可以直接访问该类的任何成员 */
  cout << "Width of box : " << box.width << endl;
}

// 程序的主函数
int main() {
  Box box;
  BigBox big;

  // 使用成员函数设置宽度
  box.setWidth(10.0);

  // 使用友元函数输出宽度
  printWidth(box);

  // 使用友元类中的方法设置宽度
  big.Print(20, box);

  getchar();
  return 0;
}
