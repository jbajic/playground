// Return Kth to Last: Implement an algorithm to find the kth to last element of
// a singly linked list.

#include <iostream>
#include <list>

#include "cci/utils.hpp"

// Assumption cannot use size
std::list<int> GetKthToLastElement(const std::list<int> &list, const int k) {
  int size{0};
  for (auto it = list.begin(); it != list.end(); ++it) {
    if (++size == k) {
      return {++it, list.end()};
    }
  }
  return {};
}

int main() {
  std::list<int> l1{1, 2, 3};
  std::list<int> l2{1, 2, 3, 4, 5, 6};
  std::list<int> l3{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> l4{9, 8, 7, 6, 5, 4, 3, 2, 1};

  PrintContainer(l2);
  PrintContainer(GetKthToLastElement(l2, 3));

  return 0;
}
