// Validate BST: Implement a function to check if a binary tree is a binary
// search tree.

#include <cstdint>
#include <iostream>
#include <optional>

#include "cci/trees_graphs/utils.hpp"

template <typename T>
bool CheckBST(Node<T>* head, std::optional<int64_t> min,
              std::optional<int64_t> max) {
  if (head == nullptr) {
    return true;
  }
  if (min && head->data <= min) {
    return false;
  }
  if (max && head->data > max) {
    return false;
  }
  return CheckBST(head->left, min, head->data) &&
         CheckBST(head->right, head->data, max);
}

// BST is a tree that satisfies the following conditions:
// 1. It is a binary tree therefore every node has two leafs
// 2. All left descendants of are smaller then the parent node, and all right
// descendants are bigger then the parent node
template <typename T>
bool ValidateBST(Node<T>* head) {
  if (head == nullptr) {
    return true;
  }
  return CheckBST(head, std::nullopt, std::nullopt);
}

int main() {
  Node<int64_t> head(15);
  head.left = new Node<int64_t>(7);
  head.right = new Node<int64_t>(22);
  std::cout << std::boolalpha << ValidateBST(&head) << std::endl;

    head.left->right = new Node<int64_t>(10);
    head.left->left = new Node<int64_t>(5);
    head.right->right = new Node<int64_t>(25);
    head.right->left = new Node<int64_t>(20);
    std::cout << std::boolalpha << ValidateBST(&head) << std::endl;

    head.left->left->left = new Node<int64_t>(3);
    std::cout << std::boolalpha << ValidateBST(&head) << std::endl;

    head.right->left->left = new Node<int64_t>(14);
    std::cout << std::boolalpha << ValidateBST(&head) << std::endl;

  return 0;
}
