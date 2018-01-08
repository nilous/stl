// 测试在 class template 中 static data members 的初值设定
#include <iostream>
using namespace std;

template <typename T>
class TestClass {
public:
  static int data_;
};

int TestClass<int>::data_ = 1;
int TestClass<char>::data_ = 2;

int main(int argc, char **argv) {
  cout << TestClass<int>::data_ << '\n';
  cout << TestClass<char>::data_ << '\n';

  return 0;
}
