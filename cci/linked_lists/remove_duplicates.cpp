// Write code to remove duplicates from an unsorted linked list.

#include <iostream>
#include <list>
#include <map>

#include "cci/utils.hpp"

// No temp buffer allowed
void RemoveDuplicates2(std::list<int> &l) {
  for (auto it = l.begin(); it != l.end(); ++it) {
    for (auto it2 = std::next(it); it2 != l.end();) {
      if (*it == *it2) {
        it2 = l.erase(it2);
      } else {
        ++it2;
      }
    }
  }
}

// Using map
void RemoveDuplicates(std::list<int> &l) {
  std::map<int, int> elems;
  for (const auto &elem : l) {
    if (elems.contains(elem)) {
      elems[elem]++;
    } else {
      elems[elem] = 1;
    }
  }
  for (auto it = l.begin(); it != l.end();) {
    if (elems[*it] > 1) {
      elems[*it] -= 1;
      it = l.erase(it);
    } else {
      ++it;
    }
  }
}

int main() {
  std::list<int> l1{1, 2, 3};
  std::list<int> l2{1, 2, 3, 4, 5, 6};
  std::list<int> l3{1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
  std::list<int> l4{1, 2, 1, 3, 4, 2, 5, 6, 3, 1, 3};

  std::cout << "Before removing duplicates:" << std::endl;
  PrintContainer(l1);
  PrintContainer(l2);
  PrintContainer(l3);
  PrintContainer(l4);

  // RemoveDuplicates(l1);
  // RemoveDuplicates(l2);
  // RemoveDuplicates(l3);
  // RemoveDuplicates(l4);

  RemoveDuplicates2(l1);
  RemoveDuplicates2(l2);
  RemoveDuplicates2(l3);
  RemoveDuplicates2(l4);

  std::cout << "After removing duplicates:" << std::endl;
  PrintContainer(l1);
  PrintContainer(l2);
  PrintContainer(l3);
  PrintContainer(l4);
  return 0;
}
