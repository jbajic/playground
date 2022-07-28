#include <iostream>

#include "structures/list/list.hpp"

int main() {
  std::cout << "Hello World!\n";
  ladida::structures::List<int> l;
  l.PushBack(1);
  l.PushBack(2);
  l.PushBack(3);
  l.PushBack(4);
  l.PushBack(5);
  l.PushFront(0);
  l.PushFront(11);
  for (const auto elem : l) {
    std::cout << elem << std::endl;
  }
  l.PopBack();
  l.PopBack();
  l.PopFront();
  l.PopFront();

  std::cout << "After popping" << std::endl;
  for (const auto elem : l) {
    std::cout << elem << std::endl;
  }
  return 0;
}
