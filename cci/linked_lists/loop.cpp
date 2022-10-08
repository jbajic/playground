// Loop Detection: Given a circular linked list, implement an algorithm that
// returns the node at the beginning of the loop.

#include <functional>
#include <iostream>
#include <unordered_set>

template <typename T>
struct Node {
  Node(T data) : data{std::move(data)} {}

  T data;
  Node<T>* next{nullptr};
};

template <typename T>
void PushFront(Node<T>** head, T data) {
  Node<T>* new_node = new Node<T>(std::move(data));
  new_node->next = *head;
  *head = new_node;
}

template <typename T>
void PrintSinglyLinkedList(Node<T>* head) {
  auto* current = head;
  while (current != nullptr) {
    std::cout << current->data << ", ";
    current = current->next;
  }
  std::cout << std::endl;
}

// Use two pointers
template <typename T>
Node<T>* FindLoopNode2(Node<T>* head) {
  auto slow_ptr = head;
  auto fast_ptr = head;
  bool collision{false};
  // detect loop
  while (fast_ptr != nullptr) {
    slow_ptr = slow_ptr->next;
    fast_ptr = fast_ptr->next;
    if (fast_ptr != nullptr) {
      fast_ptr = fast_ptr->next;
    }
    if (slow_ptr == fast_ptr) {
      // Collision point
      collision = true;
      break;
    }
  }
  if (!collision) {
    return nullptr;
  }
  // Restart slow ptr and move them at same pace, the next
  // collision point is start node of loop
  slow_ptr = head;
  while (slow_ptr != fast_ptr) {
    slow_ptr = slow_ptr->next;
    fast_ptr = fast_ptr->next;
  }
  // This is start of loop
  return slow_ptr;
}

// Use set
template <typename T>
Node<T>* FindLoopNode(Node<T>* head) {
  std::unordered_set<Node<T>*> nodes;
  auto current_node = head;
  while (current_node != nullptr) {
    if (nodes.contains(current_node)) {
      return current_node;
    }
    nodes.insert(current_node);
    current_node = current_node->next;
  }

  return nullptr;
}

int main() {
  Node<int>* head1 = new Node<int>(1);
  head1->next = new Node<int>(2);
  head1->next->next = new Node<int>(3);
  head1->next->next->next = new Node<int>(4);

  Node<int>* head2 = new Node<int>(1);
  head2->next = new Node<int>(2);
  head2->next->next = new Node<int>(3);
  head2->next->next->next = new Node<int>(4);
  head2->next->next->next->next = head2->next;

  Node<int>* head3 = new Node<int>(1);
  head3->next = new Node<int>(2);
  head3->next->next = head3;

  Node<int>* head4 = new Node<int>(1);
  head4->next = new Node<int>(2);
  head4->next->next = new Node<int>(3);
  head4->next->next->next = new Node<int>(4);
  head4->next->next->next->next = new Node<int>(5);
  head4->next->next->next->next->next = new Node<int>(6);
  head4->next->next->next->next->next->next = head4->next->next->next->next;

  const auto find_loop = [](std::function<Node<int>*(Node<int>*)> loop_fun,
                            Node<int>* l1) {
    if (auto* loop_node = loop_fun(l1); loop_node != nullptr) {
      std::cout << "Loop node at " << loop_node->data << std::endl;
    } else {
      std::cout << "No loop" << std::endl;
    }
  };

  std::cout << "First list: ";
  find_loop(FindLoopNode<int>, head1);
  std::cout << "Second list: ";
  find_loop(FindLoopNode<int>, head2);
  std::cout << "Third list: ";
  find_loop(FindLoopNode<int>, head3);
  std::cout << "Fourth list: ";
  find_loop(FindLoopNode<int>, head4);

  std::cout << "Second Method: " << std::endl;
  std::cout << "First list: ";
  find_loop(FindLoopNode2<int>, head1);
  std::cout << "Second list: ";
  find_loop(FindLoopNode2<int>, head2);
  std::cout << "Third list: ";
  find_loop(FindLoopNode2<int>, head3);
  std::cout << "Fourth list: ";
  find_loop(FindLoopNode2<int>, head4);

  return 0;
}