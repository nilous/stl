// 测试 class template 可否拥有 non-type template 参数

#include <iostream>
using namespace std;

class alloc {};

inline size_t __deque_buf_size(size_t n, size_t sz) {
  return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
  typedef __deque_iterator<T, T &, T *, BufSiz> iterator;
  typedef __deque_iterator<T, const T &, const T *, BufSiz> const_iterator;

  static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }
};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
  typedef __deque_iterator<T, T &, T *, BufSiz> iterator;
};

// int (&)[N] 表示：一个 int[N] 类型的引用
template <size_t N>
/*constexpr*/ size_t ArraySize(int (&)[N]) {  // C++11中，通过 constexpr 关键字，这种实现方式亦可保证结果是常量。
  return N;
}

// ArraySize() 的另一种实现方式：
// 这种方式保证了结果是常量。
template <size_t N>
struct type_of_size {
  typedef char type[N];
};
template <typename T, size_t Size>
typename type_of_size<Size>::type &sizeof_array_helper(T (&)[Size]);
#define sizeof_array(array) sizeof(sizeof_array_helper(array))

int main(int argc, char **argv) {
  cout << deque<int>::iterator::buffer_size() << '\n';
  cout << deque<int, alloc, 64>::iterator::buffer_size() << '\n';

  int x[5];
  cout << ArraySize(x) << '\n';

  // 这里报错：经过传参以后，T[] 会“退化”为 T *。但在那之前，进行类型检查时，显然二者是区别对待的。
  //int *p = x;
  //ArraySize(p);

  cout << sizeof_array(x) << '\n';

  return 0;
}
