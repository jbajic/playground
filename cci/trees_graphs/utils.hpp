#include <cmath>
#include <iostream>
#include <list>

template <typename T>
struct Node {
  Node(T data) : data{data} {}
  T data;
  Node<T>* left{nullptr};
  Node<T>* right{nullptr};
};

inline bool IsInteger(float k) { return std::floor(k) == k; }

template <typename T>
void PrintBTS(Node<T>* node) {
  std::list<Node<T>*> queue;
  queue.push_back(node);
  size_t counter{0};
  while (!queue.empty()) {
    const auto node = queue.front();
    queue.pop_front();
    ++counter;
    if (counter != 1) {
      if (IsInteger(std::log2(counter))) {
        std::cout << std::endl;
      }
    }
    std::cout << node->data << ", ";

    if (node->left != nullptr) {
      queue.push_back(node->left);
    }
    if (node->right != nullptr) {
      queue.push_back(node->right);
    }
  }
}
