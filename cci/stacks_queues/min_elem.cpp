// Stack Min: How would you design a stack which, in addition to push and pop,
// has a function min which returns the minimum element? Push, pop and min
// should all operate in 0(1) time.

#include <array>
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
 public:
  Stack() = default;
  Stack(std::initializer_list<T> l) {
    for (auto elem : l) {
      Push(std::move(elem));
    }
  }

  void Push(T data) {
    if (size == 0 || data < min_element) {
      min_element = data;
    }
    if (size == kMaxStackSize) {
      throw std::runtime_error("Cannot push any more elements!");
    }
    elems[size++] = data;
  }

  void Pop() {
    if (size > 0) {
      if (elems[size] == min_element) {
        min_element =
            *std::min_element(elems.begin(), elems.begin() + size - 1);
      }
      --size;
    } else {
      throw std::runtime_error("Cannot pop any more elements!");
    }
  }

  T min() const noexcept { return min_element; }

 private:
  constexpr static auto kMaxStackSize{100};
  std::array<T, kMaxStackSize> elems;
  size_t size{0};
  T min_element;
};

int main() {
  Stack<int> s1{1, 2, 3, 4, 5, 6, 0, 1, -2};
  s1.Pop();
  s1.Pop();
  s1.Pop();

  std::cout << s1.min() << std::endl;
  return 0;
}