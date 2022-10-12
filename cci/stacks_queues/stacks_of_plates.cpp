// Stack of Plates: Imagine a (literal) stack of plates. If the stack gets too
// high, it might topple. Therefore, in real life, we would likely start a new
// stack when the previous stack exceeds some threshold. Implement a data
// structure SetOfStacks that mimics this. SetO-fStacks should be composed of
// several stacks and should create a new stack once the previous one exceeds
// capacity. SetOfStacks. push() and SetOfStacks. pop() should behave
// identically to a single stack (that is, pop () should return the same values
// as it would if there were just a single stack).

#include <array>
#include <iostream>

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
    if (size == kMaxStackSize) {
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

 private:
  constexpr static auto kMaxStackSize{3};
  std::array<T, kMaxStackSize> elems;
  size_t size{0};
};

template <typename T, size_t n>
class SetOfStacks {
 public:
  SetOfStacks() = default;

  void Push(T data) {
    if (size == 3 * n) {
      throw std::runtime_error("Stacks size exceeded!");
    }
    stacks[static_cast<int>(size / n)].Push(data);
    ++size;
  }

  void Pop() {
    if (size == 0) {
      throw std::runtime_error("Cannot pop any more elements!");
    }
    stacks[static_cast<int>(size / n)].Pop();
    --size;
  }

  T Peak() {
    if (size > 0) {
      return stacks[static_cast<int>((size - 1) / n)].Peak();
    }
    throw std::runtime_error("Cannot peak here are no elements!");
  }

 private:
  std::array<Stack<T>, n> stacks;
  size_t size{0};
};

int main() {
  SetOfStacks<int, 3> s;
  s.Push(1);
  s.Push(2);
  s.Push(3);
  s.Push(4);
  s.Push(5);
  std::cout << s.Peak() << std::endl;
  s.Pop();
  std::cout << s.Peak() << std::endl;
  s.Pop();
  std::cout << s.Peak() << std::endl;
  return 0;
}
