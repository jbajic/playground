// First Common Ancestor: Design an algorithm and write code to find the first
// common ancestor of two nodes in a binary tree. Avoid storing additional nodes
// in a data structure. NOTE: This is not necessarily a binary search tree.

#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>

#include "cci/trees_graphs/utils.hpp"

template <typename T>
auto GetTraversalMap(const Node<T>* head, const Node<T>* node) {
  std::queue<const Node<T>*> queue;
  std::map<const Node<T>*, const Node<T>*> traversal_map;
  queue.push(head);
  while (!queue.empty()) {
    const auto current_node = queue.front();
    queue.pop();
    if (current_node == node) {
      break;
    }
    if (current_node->left) {
      traversal_map[current_node->left] = current_node;
      queue.push(current_node->left);
    }
    if (current_node->right) {
      queue.push(current_node->right);
      traversal_map[current_node->right] = current_node;
    }
  }
  return traversal_map;
}

template <typename T>
const Node<T>* GetCommonAncestor(const Node<T>* head, const Node<T>* first,
                                 const Node<T>* second) {
  // Reach first and second node, and keep a vector of visited nodes
  auto traversal_map_first = GetTraversalMap(head, first);
  auto traversal_map_second = GetTraversalMap(head, second);

  auto first_parent = traversal_map_first[first];
  while (true) {
    auto second_parent = traversal_map_second[second];
    while (true) {
      if (second_parent == first_parent) {
        return second_parent;
      }
      if (traversal_map_second.contains(second_parent)) {
        second_parent = traversal_map_second[second_parent];
      } else {
        break;
      }
    }
    if (traversal_map_first.contains(first_parent)) {
      first_parent = traversal_map_first[first_parent];
    } else {
      break;
    }
  }
  return nullptr;
}

int main() {
  //            15
  //        7       22
  //      5   10  20   25
  //    3  6 8
  Node<int64_t> head{15};
  head.right = new Node<int64_t>{22};
  head.left = new Node<int64_t>{7};

  head.left->right = new Node<int64_t>{10};
  head.left->left = new Node<int64_t>{5};
  head.right->right = new Node<int64_t>{25};
  head.right->left = new Node<int64_t>{20};

  head.left->left->left = new Node<int64_t>{3};
  head.left->left->right = new Node<int64_t>{6};
  head.left->right->left = new Node<int64_t>{8};

  const auto print_common_ancestor = [head_ptr = &head](const auto* first,
                                                        const auto* second) {
    std::cout << "Common ancestor of " << first->data << " and " << second->data
              << " is ";
    if (const auto ancestor = GetCommonAncestor(head_ptr, first, second);
        ancestor) {
      std::cout << ancestor->data;
    } else {
      std::cout << " no common ancestor";
    }
    std::cout << std::endl;
  };

  print_common_ancestor(head.left->right->left, head.right->left);

  return 0;
}
