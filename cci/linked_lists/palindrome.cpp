// Palindrome: Implement a function to check if a linked list is a palindrome.
#include <iostream>
#include <list>
#include <stack>

#include "cci/utils.hpp"

// TODO Solve by reversing pointers, cannot use std list

// single linked list with stack
bool IsPalindrome2(const auto& list) {
    std::stack<int> elems;
    size_t i{0};
    bool is_odd = list.size() % 2 != 0;
    for(auto current_elem:list) {
        if(i < list.size() / 2) {
            elems.push(current_elem);
        } else if (is_odd && i == list.size() / 2) {
          ++i;
          continue;
        } else {
          if (current_elem != elems.top()) {
            return false;
          }
            elems.pop();
        }
        ++i;
    }
    return true;
}

// doubly linked list
bool IsPalindrome(const auto& list) {
    auto it1 = list.begin();
    auto it2 = std::prev(list.end());
    while (std::distance(it1, it2) > 0) {
      if (*it1 != *it2) {
        return false;
      }
      ++it1;
      --it2;
    }
    return true;
}

int main() {
    std::list<int> l1{1,2,3};
    std::list<int> l2{1,2,1};
    std::list<int> l3{1, 2, 2, 1};
    std::list<int> l4{1, 2, 3, 1};

    std::cout << static_cast<int>(IsPalindrome(l1)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome(l2)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome(l3)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome(l4)) << std::endl;

    std::cout << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l1)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l2)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l3)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l4)) << std::endl;

    return 0;
}
