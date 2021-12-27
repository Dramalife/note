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
  // ���캯������
  Box(double l = 2.0, double b = 2.0, double h = 2.0) {
    cout << "Constructor called." << endl;
    length = l;
    breadth = b;
    height = h;
    // ÿ�δ�������ʱ���� 1
    objectCount++;
  }
  double Volume() { return length * breadth * height; }
  static int getCount() { return objectCount; }

 private:
  double length;   // ����
  double breadth;  // ���
  double height;   // �߶�
};

// ��ʼ���� Box �ľ�̬��Ա
int Box::objectCount = 0;

int main(void) {
  // �ڴ�������֮ǰ������������
  cout << "Inital Stage Count: " << Box::getCount() << endl;

  Box Box1(3.3, 1.2, 1.5);  // ���� box1
  Box Box2(8.5, 6.0, 2.0);  // ���� box2

  // �ڴ�������֮��������������
  cout << "Final Stage Count: " << Box::getCount() << endl;

  return 0;
}
