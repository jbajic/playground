// Successor: Write an algorithm to find the "next" node (i.e., in-order
// successor) of a given node in a binary search tree. You may assume that each
// node has a link to its parent.

#include <iostream>
#include <queue>

template <typename T>
struct Node {
  T data;
  Node<T>* left;
  Node<T>* parent;
  Node<T>* right;
};

// InOrder successor
//          A
//     B          C
//  E     F    G     H
// Inorder: EBFAGCH
// e.g. Assuming given node is F, the next one is G
template <typename T>
Node<T>* GetSuccessor(Node<T>* node) {
  if (node->right) {
    // The most right child node of right subtree
    auto current_node = node->right;
    while (current_node->left != nullptr) {
      current_node = current_node->left;
    }
    return current_node;
  }
  // As long as current node is right child of the parent
  auto current_node = node;
  auto parent_node = node->parent;
  while (parent_node != nullptr && parent_node->left != current_node) {
    current_node = parent_node;
    parent_node = current_node->parent;
  }
  return parent_node;
  // TODO We have reached top node, now we go down
}

int main() {
  //            15
  //        7       22
  //      5   10  20   25
  //    3  6 8
  Node<int64_t> head{.data = 15, .parent = nullptr};
  head.right = new Node<int64_t>{.data = 22, .parent = &head};
  head.left = new Node<int64_t>{.data = 7, .parent = &head};

  head.left->right = new Node<int64_t>{.data = 10, .parent = head.left};
  head.left->left = new Node<int64_t>{.data = 5, .parent = head.left};
  head.right->right = new Node<int64_t>{.data = 25, .parent = head.right};
  head.right->left = new Node<int64_t>{.data = 20, .parent = head.right};

  head.left->left->left =
      new Node<int64_t>{.data = 3, .parent = head.left->left};
  head.left->left->right =
      new Node<int64_t>{.data = 6, .parent = head.left->left};
  head.left->right->left =
      new Node<int64_t>{.data = 8, .parent = head.left->right};

  std::cout << "Successor of " << head.left->left->data
            << " is: " << GetSuccessor(head.left->left)->data << std::endl;
  std::cout << "Successor of " << head.left->left->left->data
            << " is: " << GetSuccessor(head.left->left->left)->data
            << std::endl;
  std::cout << "Successor of " << head.left->right->left->data
            << " is: " << GetSuccessor(head.left->right->left)->data
            << std::endl;
  return 0;
}
