// Palindrome: Implement a function to check if a linked list is a palindrome.
#include <iostream>
#include <list>
#include <stack>

#include "cci/utils.hpp"

template<typename T>
struct Node {
  Node(T data) : data{std::move(data)} {}

  T data;
  Node<T>* next{nullptr};
};

template<typename T>
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

template <typename T>
bool IsPalindrome3(Node<T>* head) {
  Node<T>* reverse_head{nullptr};

  // Reverse list
  auto* current_head = head;
  while (current_head != nullptr) {
    auto* new_node = new Node(current_head->data);
    new_node->next = reverse_head;
    reverse_head = new_node;
    current_head = current_head->next;
  }
  // Check if palindrome
  current_head = head;
  while(current_head != nullptr) {
    if(current_head->data != reverse_head->data) {
      return false;
    }
    current_head = current_head->next;
    reverse_head = reverse_head->next;
  }
  return true;
}

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

   std::cout << "STD lists" << std::endl;
    PrintContainer(l1);
    PrintContainer(l2);
    PrintContainer(l3);
    PrintContainer(l4);
    std::cout << static_cast<int>(IsPalindrome(l1)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome(l2)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome(l3)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome(l4)) << std::endl;

    std::cout << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l1)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l2)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l3)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome2(l4)) << std::endl;
    std::cout << std::endl;

    std::cout << "Singly linked lists" << std::endl;
    Node<int>* head1 = new Node<int>(1);
    PushFront(&head1, 2);
    PushFront(&head1, 3);
    PushFront(&head1, 4);
    PrintSinglyLinkedList(head1);
    Node<int>* head2 = new Node<int>(1);
    PushFront(&head2, 2);
    PushFront(&head2, 2);
    PushFront(&head2, 1);
    PrintSinglyLinkedList(head2);
    Node<int>* head3 = new Node<int>(1);
    PushFront(&head3, 2);
    PushFront(&head3, 3);
    PushFront(&head3, 2);
    PushFront(&head3, 1);
    PrintSinglyLinkedList(head3);

    std::cout << std::endl;
    std::cout << static_cast<int>(IsPalindrome3<int>(head1)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome3<int>(head2)) << std::endl;
    std::cout << static_cast<int>(IsPalindrome3<int>(head3)) << std::endl;
    return 0;
}
