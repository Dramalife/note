#include <iostream>
using namespace std;

class ol_printData {
 public:
  void ol_print(int i) { cout << "int: " << i << endl; }

  void ol_print(double f) { cout << "double: " << f << endl; }

  void ol_print(char c[]) { cout << "char: " << c << endl; }
};

/* Symbols: (ol_printData)
 * $ nm overloading.cc.out | grep ol_print
 * 00000000000012e4 W _ZN12ol_printData8ol_printEPc
 * 0000000000001290 W _ZN12ol_printData8ol_printEd
 * 0000000000001246 W _ZN12ol_printData8ol_printEi
 */
int main(void) {
  ol_printData pd;

  // 输出整数
  pd.ol_print(5);
  // 输出浮点数
  pd.ol_print(500.263);
  // 输出字符串
  char c[] = "Hello C++";
  pd.ol_print(c);

/* Get type string of variable */
#if 1  // C++
  printf("::%s\n", typeid(typeof(pd)).name());
#else  // C
// SEE: ../../../lib_dramalife/string_related_lib/
#endif

  return 0;
}
