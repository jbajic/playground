// List of Depths: Given a binary tree, design an algorithm which creates a
// linked list of all the nodes at each depth (e.g., if you have a tree with
// depth D, you'll have D linked lists).

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <list>

#include "cci/trees_graphs/utils.hpp"

template <typename T>
std::list<std::list<Node<T>*>> GetLevels(Node<T>* head) {
  if (head == nullptr) {
    return {};
  }
  std::list<std::list<Node<T>*>> levels;
  std::list<Node<T>*> queue;
  queue.push_back(head);
  int counter{0};
  int last_counter{0};
  std::list<Node<T>*> current_level;
  while (!queue.empty()) {
    const auto elem = queue.front();
    queue.pop_front();
    current_level.push_back(elem);
    if (elem->left != nullptr) {
      queue.push_back(elem->left);
    }
    if (elem->right != nullptr) {
      queue.push_back(elem->right);
    }
    ++counter;
    if (counter > last_counter && IsInteger(std::log2(counter))) {
      levels.push_back(current_level);
      last_counter = counter;
      current_level.clear();
      counter = 0;
    }
  }
  if (!current_level.empty()) {
    levels.push_back(current_level);
  }
  return levels;
}

template <typename T>
void PrintLevels(const std::list<std::list<Node<T>*>>& levels) {
  int level_num{1};
  for (const auto& level : levels) {
    std::cout << "Level " << level_num << ": ";
    for (const auto& elem : level) {
      std::cout << elem->data << ", ";
    }
    std::cout << std::endl;
    ++level_num;
  }
}

int main() {
  Node<int64_t> head(1);
  head.left = new Node<int64_t>(10);
  head.right = new Node<int64_t>(11);
  head.right->right = new Node<int64_t>(15);
  head.right->left = new Node<int64_t>(12);

  auto levels1 = GetLevels(&head);
  PrintLevels(levels1);
  return 0;
}