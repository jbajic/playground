// Minimal Tree: Given a sorted (increasing order) array with unique integer
// elements, write an algo­rithm to create a binary search tree with minimal
// height.

#include <array>
#include <cmath>
#include <iostream>
#include <list>

#include "cci/trees_graphs/utils.hpp"

template <typename T, size_t n>
void AddNode(const std::array<T, n>& arr, const int64_t min, const int64_t max,
             Node<T>** node) {
  if (min > max) {
    return;
  }
  const auto mid = static_cast<int>((min + max) / 2);
  *node = new Node(arr[mid]);
  (*node)->data = arr[mid];
  // Add left
  AddNode(arr, min, mid - 1, &(*node)->left);
  // Add right
  AddNode(arr, mid + 1, max, &(*node)->right);
}

template <typename T, size_t n>
auto CreateBTS(const std::array<T, n> arr) {
  Node<T>* head{nullptr};
  AddNode(arr, 0, n, &head);
  return head;
}

int main() {
  std::array a1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  //   std::array a1{-10, -9, -8, -7, -6, -5};

  auto bts = CreateBTS<int, 9>(a1);
  PrintBTS(bts);
  std::cout << std::endl;
  return 0;
}
