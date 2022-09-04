#include <iostream>
#include <algorithm>

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
  l.PushFront(-10);
  l.PushFront(-11);
  l.PushBack(6);
  std::cout << "Hello World!\n";
  std::cout << "Size:" << l.Size() << std::endl;
  for (const auto elem : l) {
    std::cout << elem << ", ";
  }
  std::cout << std::endl;
  std::cout << "Hello World!\n";
  l.PopBack();
  l.PopBack();

  std::cout << "After popping" << std::endl;
  for (const auto elem : l) {
    std::cout << elem << ", ";
  }
  std::cout << std::endl;

  std::cout << "After popping iterator" << std::endl;
  for (auto it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  std::cout << "After popping reverse iterator" << std::endl;
  std::cout << l.tail_->data << std::endl;
  for (auto it = l.rbegin(); it != l.rend(); ++it) {
    std::cout << *it << ", " << std::endl;
  }
  std::cout << std::endl;
  std::for_each(l.rbegin(), l.rend(), [](const int n) { std::cout << n << ' '; });


  return 0;
}
