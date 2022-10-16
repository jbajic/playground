// Sort Stack: Write a program to sort a stack such that the smallest items are
// on the top. You can use an additional temporary stack, but you may not copy
// the elements into any other data structure (such as an array). The stack
// supports the following operations: push, pop, peek, and is Empty.

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
    throw std::runtime_error("Cannot peak there are no elements!");
  }

  // Two additional stacks
  void Sort() {
    if (size == 0) {
      return;
    }
    // Hanoi problem
    Stack<T, n> ordered_stack;
    Stack<T, n> aux_stack;

    while (size > 0) {
      auto min_elem = Peak();
      Pop();
      while (size > 0) {
        const auto elem = Peak();
        Pop();
        if (elem < min_elem) {
          aux_stack.Push(min_elem);
          min_elem = elem;
        } else {
          aux_stack.Push(elem);
        }
      }
      ordered_stack.Push(min_elem);
      while (aux_stack.Size() > 0) {
        Push(aux_stack.Peak());
        aux_stack.Pop();
      }
    }
    *this = std::move(ordered_stack);
  }

  // One stack
  void Sort2() {
    if (size == 0) {
      return;
    }
    Stack<T, n> aux_stack;
    auto current_size{size};
    while (current_size > 0) {
      auto min_elem = Peak();
      Pop();
      auto current_size2 = current_size - 1;
      while (current_size2 > 0) {
        const auto current_elem = Peak();
        Pop();
        if (current_elem < min_elem) {
          aux_stack.Push(min_elem);
          min_elem = current_elem;
        } else {
          aux_stack.Push(current_elem);
        }
        --current_size2;
      }
      Push(min_elem);
      --current_size;
      while (aux_stack.Size() > 0) {
        Push(aux_stack.Peak());
        aux_stack.Pop();
      }
    }
  }

  size_t Size() const noexcept { return size; }

 private:
  std::array<T, n> elems;
  size_t size{0};
};

int main() {
  std::cout << "Hello World!" << std::endl;
  Stack<int, 10> stack;
  stack.Push(5);
  stack.Push(1);
  stack.Push(6);
  stack.Push(3);
  stack.Push(2);
  stack.Push(10);
  stack.Push(7);
  stack.Sort2();

  std::cout << "Ordering: " << std::endl;
  while (stack.Size() > 0) {
    std::cout << stack.Peak() << ", ";
    stack.Pop();
  }
  std::cout << std::endl;

  return 0;
}