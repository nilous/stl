// 编译器进行重载决议时，优先选择更加特化的版本进行匹配。
// 如果没有匹配，才选择更通用的版本。
#include <iostream>
using namespace std;

template <typename T>
void f(T) {
  cout << "Less specialized function called\n";
}

template <typename T>
void f(T *) {
  cout << "More specialized function called\n";
}

template <typename T>
void f(const T *) {
  cout << "Even more specialized function for const T * called\n";
}

// 报错：f1() 重复定义
// int / const int 不构成重载
//void f1(int, int) {}
//void f1(int, const int) {}

// int & / const int & 可以构成重载
//void f2(int &) {}
//void f2(const int &) {}

// 亦即，只有参数是 pointer 或 reference 时，才把参数的 const-ness 作为重载依据。

int main(int argc, char **argv) {
  int i = 0;
  const int j = i;
  int *p = &i;
  const int *c = &j;

  f(i);  // less
  f(j);  // less
  f(p);  // more
  f(c);  // even more
  return 0;
}
