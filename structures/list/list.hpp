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
 private:
  struct Iterator;

 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = Iterator;
  using const_iterator = Iterator;
  using reverse_iterator = iterator;
  using const_reverse_iterator = const_iterator;

  List() = default;

  ~List() {
    auto *current = head_;
    while (current != nullptr) {
      head_ = current->next;
      delete current;
      current = head_;
    }
  }

  List(const List &) = delete;
  List(List &&) noexcept = delete;
  List &operator=(const List &) = delete;
  List operator=(const List &&) noexcept = delete;

  void PushBack(T data) {
    if (head_ == nullptr) {
      head_ = tail_ = new Node(data);
    } else if (head_ == tail_) {
      auto *new_node = new Node(data);
      tail_ = new_node;
      head_->next = tail_;
      tail_->prev = head_;
    } else {
      auto *new_node = new Node(data);
      new_node->prev = tail_;
      tail_->next = new_node;
      tail_ = new_node;
    }
    ++size_;
  }

  void PushFront(T data) {
    if (head_ == nullptr) {
      head_ = tail_ = new Node(data);
    } else if (head_ == tail_) {
      auto *new_node = new Node(data);
      head_ = new_node;
      tail_->prev = head_;
      head_->next = tail_;
    } else {
      auto *new_node = new Node(data);
      new_node->next = head_;
      head_->prev = new_node;
      head_ = new_node;
    }
    ++size_;
  }

  T PopBack() {
    auto *current = tail_;
    auto value = tail_->data;
    tail_ = tail_->prev;
    tail_->next = nullptr;
    delete current;
    --size_;
    return value;
  }

  T PopFront() {
    auto *current = head_;
    auto value = head_->data;
    head_ = head_->next;
    head_->prev = nullptr;
    delete current;
    --size_;
    return value;
  }

  size_t Size() const noexcept { return size_; }

  iterator begin() const { return Iterator(head_); }

  iterator end() const { return Iterator(nullptr); }

  const_iterator cbegin() const { return Iterator(begin()); }

  const_iterator cend() const { return Iterator(end()); }

  reverse_iterator rbegin() const { return Iterator(tail_); }

  reverse_iterator rend() const { return Iterator(nullptr); }

  // const_reverse_iterator rcbegin() const { return reverse_iterator(cend()); }

  // const_reverse_iterator rcend() const { return reverse_iterator(cbegin()); }

 private:
  struct Iterator final {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    Iterator(Node<T> *base_node) : node_{base_node} {}

    reference operator*() { return node_->data; }

    pointer operator->() { return &node_->data; }

    // Prefix
    Iterator operator++() {
      // std::cout << "prefix ++" << node_->data << "\n";
      node_ = node_->next;
      return *this;
    }

    // Postfix
    Iterator operator++(int) {
      auto curr = *this;
      node_ = node_->next;
      return curr;
    }

    // Prefix for reverse iteration
    Iterator operator--() {
      // std::cout << "prefix --" << node_->data << "\n";
      node_ = node_->prev;
      return *this;
    }

    // Postfix
    Iterator operator--(int) {
      // std::cout << "postfix --\n";
      auto curr = *this;
      node_ = node_->prev;
      return curr;
    }

    friend bool operator==(const Iterator &lhs, const Iterator &rhs) noexcept {
      return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) noexcept {
      return lhs.node_ != rhs.node_;
    }

   private:
    Node<T> *node_;
  };

 public:
  Node<T> *head_{nullptr};
  Node<T> *tail_{nullptr};
  size_t size_{0};
};
}  // namespace ladida::structures
