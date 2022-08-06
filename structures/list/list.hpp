#pragma once

#include <iostream>
#include <iterator>

namespace ladida::structures {

template <typename T>
struct Node {
  Node(T data) : data{data} {}
  T data;
  Node *next{nullptr};
  Node *prev{nullptr};
};

template <typename T>
class List final {
 public:
  struct Iterator;

  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = Iterator;
  using const_iterator = Iterator;
  // using reverse_iterator = const Iterator;
  // using const_reverse_iterator = const Iterator;

  List() = default;

  ~List() {
    if (head == nullptr) {
      return;
    }
    auto *current = head;
    while (current != nullptr) {
      head = current->next;
      delete current;
      current = head;
    }
  }

  List(const List &) = delete;
  List(List &&) noexcept = delete;
  List &operator=(const List &) = delete;
  List operator=(const List &&) noexcept = delete;

  void PushBack(T data) {
    if (head == nullptr) {
      head = tail = new Node(data);
    } else if (head == tail) {
      auto *new_node = new Node(data);
      tail = new_node;
      head->next = tail;
      tail->prev = head;
    } else {
      auto *new_node = new Node(data);
      new_node->prev = tail;
      tail->next = new_node;
      tail = new_node;
    }
    ++size;
  }

  void PushFront(T data) {
    if (head == nullptr) {
      head = tail = new Node(data);
    } else if (head == tail) {
      auto *new_node = new Node(data);
      head = new_node;
      tail->prev = head;
      head->next = tail;
    } else {
      auto *new_node = new Node(data);
      new_node->next = head;
      head->prev = new_node;
      head = new_node;
    }
    ++size;
  }

  T PopFront() {
    auto *current = tail;
    auto value = tail->data;
    tail = tail->prev;
    tail->next = nullptr;
    delete current;
    --size;
    return value;
  }

  T PopBack() {
    auto *current = head;
    auto value = head->data;
    head = head->next;
    head->prev = nullptr;
    delete current;
    --size;
    return value;
  }

  size_t Size() const noexcept { return size; }

  Iterator begin() const { return Iterator(head); }

  Iterator end() const { return Iterator(nullptr); }

  const Iterator cbegin() const { return Iterator(head); }

  const Iterator cend() const { return Iterator(nullptr); }

  struct Iterator final {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    Iterator(Node<T> *base_node) : base_node{base_node} {}

    reference operator*() { return base_node->data; }

    pointer operator->() { return &base_node->data; }

    // Prefix
    Iterator operator++() {
      base_node = base_node->next;
      return *this;
    }

    // Postfix
    Iterator operator++(int) {
      auto curr = *this;
      base_node = base_node->next;
      return curr;
    }

    // // Prefix for reverse iteration
    //   Iterator operator--() {
    //     base_node = base_node->prev;
    //     return *this;
    //   }

    //   // Postfix
    //   Iterator operator--(int) {
    //     auto curr = *this;
    //     base_node = base_node->prev;
    //     return curr;
    //   }

    friend bool operator==(const Iterator &lhs, const Iterator &rhs) noexcept {
      return lhs.base_node == rhs.base_node;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) noexcept {
      return lhs.base_node != rhs.base_node;
    }

   private:
    Node<T> *base_node;
  };
  Node<T> *head{nullptr};
  Node<T> *tail{nullptr};
  size_t size{0};
};
}  // namespace ladida::structures
