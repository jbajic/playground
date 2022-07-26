#pragma once

#include <iostream>
#include <iterator>

namespace ladida::structures {

template <typename T> struct Node {
  Node(T data) : data{data} {}
  T data;
  Node *next{nullptr};
  Node *prev{nullptr};
};

template <typename T> class List final {
public:
  struct Iterator;
  List() = default;

  ~List() {
    if (head == nullptr) {
      return;
    }
    Node<T> *current = head->next;
    while (head != nullptr) {
      delete head;
      head = current;
      current = head->next;
    }
  }

  List(const List &) = delete;
  List(List &&) noexcept = delete;
  List &operator=(const List &) = delete;
  List operator=(const List &&) noexcept = delete;

  void Add(T data) {
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
  }

  Iterator begin() const { return Iterator(head); }

  Iterator end() const { return Iterator(nullptr); }

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
};
} // namespace ladida::structures
