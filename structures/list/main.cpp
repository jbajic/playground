#include "structures/list/list.hpp"
#include <iostream>

int main() {
  std::cout << "Hello World!\n";
  ladida::structures::List<int> l;
  l.Add(1);
  l.Add(2);
  l.Add(3);
  l.Add(4);
  l.Add(5);
  for (const auto elem : l) {
    std::cout << elem << std::endl;
  }
  return 0;
}
