// Queue via Stacks: Implement a MyQueue class which implements a queue using
// two stacks.
#include <array>
#include <iostream>

template <typename T, size_t n>
class Stack {
 public:
  Stack() = default;
  Stack(std::initializer_list<T> l) {
    for (auto elem : l) {
      Push(std::move(elem));
    }
  }

  void Push(T data) {
    if (size == n) {
      throw std::runtime_error("Cannot push any more elements!");
    }
    elems[size++] = data;
  }

  void Pop() {
    if (size > 0) {
      --size;
    } else {
      throw std::runtime_error("Cannot pop any more elements!");
    }
  }

  T Peak() {
    if (size > 0) {
      return elems[size - 1];
    }
    throw std::runtime_error("Cannot peak, there are no elements!");
  }

  size_t Size() const { return size; }

 private:
  std::array<T, n> elems;
  size_t size{0};
};

template <typename T, size_t n>
class Queue {
 public:
  Queue() = default;

  void Push(T data) { s1.Push(data); }

  void Pop() {
    // Reverse stacks
    ReverseStacks();
    s2.Pop();
  }

  T Peak() {
    ReverseStacks();
    return s2.Peak();
  }

  size_t Size() const { return s1.Size() + s2.Size(); }

 private:
  void ReverseStacks() {
    while (s1.Size() > 0) {
      s2.Push(s1.Peak());
      s1.Pop();
    }
  }

  Stack<T, n> s1;
  Stack<T, n> s2;
};

int main() {
  Queue<int, 10> q;

  q.Push(1);
  std::cout << "Peak: " << q.Peak() << std::endl;
  q.Pop();

  q.Push(2);
  std::cout << "Peak: " << q.Peak() << std::endl;
  q.Pop();

  q.Push(3);
  q.Push(4);
  q.Push(5);
  q.Push(6);
  std::cout << "Peak: " << q.Peak() << std::endl;
  q.Pop();
  q.Pop();
  q.Pop();
  std::cout << "Peak: " << q.Peak() << std::endl;

  return 0;
}
