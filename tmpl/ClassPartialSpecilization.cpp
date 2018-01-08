// 测试 class template 的偏特化
#include <iostream>
using namespace std;

template <typename T, typename U>
class TestClass {
public:
  TestClass() {
    cout << "T, U\n";
  }
};

template <typename T>
class TestClass<T *, T *> {
public:
  TestClass() {
      cout << "T *, T *\n";
  }
};

template <typename T>
class TestClass<const T *, T *> {
public:
  TestClass() {
      cout << "const T *, T *\n";
  }
};

// 偏特化与全特化的区别：
// 全特化的模板参数列表应当是空的。
template <>
class TestClass<int, char> {
public:
  TestClass() {
    cout << "Specilization: int, char\n";
  }
};

int main(int argc, char **argv) {
  TestClass<int, int> x1;
  TestClass<int, char> x2;
  TestClass<int *, int *> x3;
  TestClass<char *, char *> x4;
  TestClass<const char *, char *> x5;
  return 0;
}
