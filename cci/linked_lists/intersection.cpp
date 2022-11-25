// Given two (singly) linked lists, determine if the two lists intersect. Return
// the inter­secting node. Note that the intersection is defined based on
// reference, not value.That is, if the kth node of the first linked list is the
// exact same node (by reference) as the jth node of the second linked list,
// then they are intersecting.
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

// Keep a set of all encountered node pointers
template <typename T>
Node<T>* FindIntersection(Node<T>* head1, Node<T>* head2) {
  std::unordered_set<Node<T>*> nodes;
  auto current_node = head1;
  while (current_node != nullptr) {
    nodes.insert(current_node);
    current_node = current_node->next;
  }

  current_node = head2;
  while (current_node != nullptr) {
    if (const auto it = nodes.find(current_node); it != nodes.end()) {
      return *it;
    }
    current_node = current_node->next;
  }
  return nullptr;
}

// Keep a set of all encountered node pointers
template <typename T>
Node<T>* FindIntersection2(Node<T>* head1, Node<T>* head2) {
  // Determine if there is intersection
  // bother lists must ha ve the same end node
  auto end_node1 = head1;
  size_t list_1{0};
  while (end_node1 != nullptr) {
    end_node1 = end_node1->next;
    ++list_1;
  }

  auto end_node2 = head2;
  size_t list_2{0};
  while (end_node2 != nullptr) {
    end_node2 = end_node2->next;
    ++list_2;
  }
  if (end_node1 != end_node2) {
    return nullptr;
  }

  // Now we know there is intersection
  auto current_node_1 = head1;
  auto current_node_2 = head2;

  // If one is longer then other we set the longer list at the same starting
  // position as shorter list
  if (list_1 > list_2) {
    for (size_t i{0}; i < list_1 - list_2; ++i) {
      current_node_1 = current_node_1->next;
    }
  } else if (list_1 < list_2) {
    for (size_t i{0}; i < list_2 - list_1; ++i) {
      current_node_2 = current_node_2->next;
    }
  }
  while (current_node_1 != nullptr) {
    if (current_node_1 == current_node_2) {
      break;
    }
    current_node_1 = current_node_1->next;
    current_node_2 = current_node_2->next;
  }
  return current_node_1;
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

  Node<int>* head3 = new Node<int>(1);
  head3->next = new Node<int>(2);
  head3->next->next = new Node<int>(3);
  head3->next->next->next = head1->next->next;

  std::cout << "First list: ";
  PrintSinglyLinkedList(head1);
  std::cout << "Second list: ";
  PrintSinglyLinkedList(head2);
  std::cout << "Third list: ";
  PrintSinglyLinkedList(head3);

  const auto run_intersection =
      [](std::function<Node<int>*(Node<int>*, Node<int>*)> intersection_fun,
         Node<int>* l1, Node<int>* l2) {
        if (auto* intersection = intersection_fun(l1, l2);
            intersection != nullptr) {
          std::cout << "Intersection at " << intersection->data << std::endl;
        } else {
          std::cout << "No intersection" << std::endl;
        }
      };

  std::cout << "Intersection between 1 and 2: ";
  run_intersection(FindIntersection<int>, head1, head2);

  std::cout << "Intersection between 2 and 3: ";
  run_intersection(FindIntersection<int>, head2, head3);

  std::cout << "Intersection between 1 and 3: ";
  run_intersection(FindIntersection<int>, head1, head3);

  std::cout << "Method2: " << std::endl;
  std::cout << "Intersection between 1 and 2: ";
  run_intersection(FindIntersection2<int>, head1, head2);

  std::cout << "Intersection between 2 and 3: ";
  run_intersection(FindIntersection2<int>, head2, head3);

  std::cout << "Intersection between 1 and 3: ";
  run_intersection(FindIntersection2<int>, head1, head3);

  return 0;
}
