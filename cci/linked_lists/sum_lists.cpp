// Sum Lists: You have two numbers represented by a linked list, where each node
// contains a single digit. The digits are stored in reverse order, such that
// the 1 's digit is at the head of the list. Write a function that adds the two
// numbers and returns the sum as a linked list.

#include <iostream>
#include <list>
#include <map>

#include "cci/utils.hpp"

std::list<int> SumLists(std::list<int> &l1, std::list<int> &l2) {
  std::list<int> sum;
  auto it1 = l1.begin();
  auto it2 = l2.begin();
  int pass{0};
  while (it1 != l1.end() || it2 != l2.end()) {
    if (it1 != l1.end()) {
      pass += *it1;
      ++it1;
    }
    if (it2 != l2.end()) {
      pass += *it2;
      ++it2;
    }
    sum.push_back(pass % 10);
    pass = pass / 10;
  }
  if (pass) {
    sum.push_back(pass % 10);
  }
  return sum;
}

std::list<int> SumLists2(std::list<int> &l1, std::list<int> &l2) {
  std::list<int> sum;
  int pass{0};
  auto it1 = l1.rbegin();
  auto it2 = l2.rbegin();
  while (it1 != l1.rend() || it2 != l2.rend()) {
    if (it1 != l1.rend()) {
      pass += *it1;
      ++it1;
    }
    if (it2 != l2.rend()) {
      pass += *it2;
      ++it2;
    }
    sum.push_front(pass % 10);
    pass = pass / 10;
  }
  if (pass) {
    sum.push_front(pass % 10);
  }
  return sum;
}

int main() {
  std::list<int> l1{5, 6, 1};
  std::list<int> l2{3, 2, 1};
  std::list<int> l3{9, 9, 9};
  std::list<int> l4{5, 5, 5};

  // Backwards
  std::cout << "Backwards:" << std::endl;
  PrintContainer(l1);
  PrintContainer(l2);
  std::cout << "=" << std::endl;
  PrintContainer(SumLists(l1, l2));
  std::cout << std::endl;

  PrintContainer(l1);
  PrintContainer(l3);
  std::cout << "=" << std::endl;
  PrintContainer(SumLists(l1, l3));
  std::cout << std::endl;

  PrintContainer(l3);
  PrintContainer(l4);
  std::cout << "=" << std::endl;
  PrintContainer(SumLists(l3, l4));

  // Forwards
  std::cout << "Forwards:" << std::endl;
  PrintContainer(l1);
  PrintContainer(l2);
  std::cout << "=" << std::endl;
  PrintContainer(SumLists2(l1, l2));
  std::cout << std::endl;

  PrintContainer(l1);
  PrintContainer(l3);
  std::cout << "=" << std::endl;
  PrintContainer(SumLists2(l1, l3));
  std::cout << std::endl;

  PrintContainer(l3);
  PrintContainer(l4);
  std::cout << "=" << std::endl;
  PrintContainer(SumLists2(l3, l4));

  return 0;
}
