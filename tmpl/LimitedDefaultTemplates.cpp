// 测试 template 参数可否根据前一个 template 参数而设定默认值。
// 现代编译器都支持。

#include <iostream>

using namespace std;

class alloc {};

template <typename T, typename Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
  deque() { cout << "deque\n"; }
};

template <typename T, typename Sequence = deque<T>>
class stack {
public:
  stack() { cout << "stack\n"; }
};

int main(int argc, char **argv) {
  stack<int> x;
  return 0;
}
