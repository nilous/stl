// 测试 class template 之内可否再有 template (members)
// 显然现代的编译器都应该支持了。
#include <iostream>
using namespace std;

class alloc {
};

template <typename T, typename Alloc = alloc>
class vector {
public:
  typedef T value_type;
  typedef value_type *iterator;

  template <typename I>
  void insert(iterator position, I first, I last) {
    cout << "insert()\n";
  }
};

int main(int argc, char **argv) {
  int ia[5] = { 0, 1, 2, 3, 4 };

  vector<int> v;
  vector<int>::iterator i;
  v.insert(i, ia, ia + 5);
  return 0;
}
