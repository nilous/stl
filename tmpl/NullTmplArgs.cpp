#include <iostream>
using namespace std;

class alloc {};

template <typename T, typename Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
  deque() { cout << "deque\n"; }
};

template <typename T, typename Sequence>
class stack;

// NOTE!:
// MSVC 1900: 运算符重载不需要这些前置声明亦可
// GCC 5.4: 运算符重载也一定要有前置声明，否则编译报错
// CLANG 8：要求有前置声明，否则编译没有问题，但运算符重载没有起作用，我们提供的版本不会被调用
//
// 总之，使用前置声明就对了。参见 C++ Primer 5e 中文版 p.589
template <typename T, typename Sequence>
bool operator==(const stack<T, Sequence> &x, const stack<T, Sequence> &y);

template <typename T, typename Sequence>
bool operator<(const stack<T, Sequence> &x, const stack<T, Sequence> &y);

// NOTE!: 但一般函数若没有前置声明，会报错
template <typename T, typename Sequence>
int compare(const stack<T, Sequence> &x, const stack<T, Sequence> &y);

template <typename T, typename Sequence = deque<T>>
class stack {
  Sequence c;

  // OK
  //friend bool operator==<T>(const stack<T> &, const stack<T> &);
  //friend bool operator==<T>(const stack<T> &, const stack<T> &);

  // OK
  //friend bool operator==<T>(const stack &, const stack &);
  //friend bool operator==<T>(const stack &, const stack &);

  // OK
  friend bool operator== <>(const stack &, const stack &);
  friend bool operator< <>(const stack &, const stack &);  // NOTE!: 两个 '<' 间若没有空格，在 MSVC 下会报错

  friend int compare<>(const stack &, const stack &);

  // NOT OK
  //friend bool operator==(const stack &, const stack &);
  //friend bool operator==(const stack &, const stack &);

public:
  stack() { cout << "stack\n"; }
};

template <typename T, typename Sequence>
bool operator==(const stack<T, Sequence> &x, const stack<T, Sequence> &y) {
  cout << "operator==\n";
  return true;
}

template <typename T, typename Sequence>
bool operator<(const stack<T, Sequence> &x, const stack<T, Sequence> &y) {
  cout << "operator<\n";
  return true;
}

template <typename T, typename Sequence>
int compare(const stack<T, Sequence> &x, const stack<T, Sequence> &y) {
  cout << "compare\n";
  return 0;
}


int main(int argc, char **argv) {
  stack<int> x, y;

  x == y; x < y;
  compare(x, y);
  return 0;
}
