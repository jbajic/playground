// Check Balanced: Implement a function to check if a binary tree is balanced.
// For the purposes of this question, a balanced tree is defined to be a tree
// such that the heights of the two subtrees of any node never differ by more
// than one.

#include <algorithm>
#include <iostream>
#include <optional>

#include "cci/trees_graphs/utils.hpp"

template <typename T>
int GetHeight(Node<T>* node) {
  if (node == nullptr) {
    return -1;
  }
  return std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

template <typename T>
bool CheckBalanced(Node<T>* head) {
  if (head == nullptr) {
    return true;
  }
  if (std::abs(GetHeight(head->left) - GetHeight(head->right)) > 1) {
    return false;
  }
  return CheckBalanced(head->left) && CheckBalanced(head->right);
}

template <typename T>
std::optional<int> CheckHeight2(Node<T>* node) {
  if (node == nullptr) {
    return -1;
  }
  auto left_subtree = CheckHeight2<T>(node->left);
  if (left_subtree == std::nullopt) {
    return std::nullopt;
  }
  auto right_subtree = CheckHeight2<T>(node->right);
  if (right_subtree == std::nullopt) {
    return std::nullopt;
  }
  const auto diff = std::abs(*left_subtree - *right_subtree);
  if (diff > 1) {
    return std::nullopt;
  }
  return std::max(*left_subtree, *right_subtree) + 1;
}

template <typename T>
bool CheckBalanced2(Node<T>* head) {
  if (head == nullptr) {
    return false;
  }
  return CheckHeight2(head) != std::nullopt;
}

int main() {
  Node<int64_t> head(1);
  const auto print_result = [&] {
    std::cout << std::boolalpha << "Method 1:" << CheckBalanced(&head)
              << ", Method 2:" << CheckBalanced2(&head) << std::endl;
  };

  head.left = new Node<int64_t>(2);
  head.right = new Node<int64_t>(3);
  head.right->left = new Node<int64_t>(4);
  head.right->right = new Node<int64_t>(5);
  print_result();

  head.right->right->left = new Node<int64_t>(6);
  head.right->right->right = new Node<int64_t>(7);
  print_result();

  head.left->right = new Node<int64_t>(8);
  head.left->left = new Node<int64_t>(9);
  head.left->right->left = new Node<int64_t>(10);
  head.left->right->right = new Node<int64_t>(11);
  print_result();

  head.left->right->right->right = new Node<int64_t>(12);
  head.left->right->right->right->right = new Node<int64_t>(13);
  print_result();

  return 0;
}
