template <typename T>
struct Node {
  Node(T data) : data{data} {}
  T data;
  Node *next{nullptr};
};

template <typename T>
class List final {
 public:
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
    } else {
      auto *new_node = new Node(data);
      tail->next = new_node;
      tail = new_node;
    }
  }

  void PushFront(T data) {
    if (head == nullptr) {
      head = tail = new Node(data);
    } else if (head == tail) {
      auto *new_node = new Node(data);
      head = new_node;
      head->next = tail;
    } else {
      auto *new_node = new Node(data);
      new_node->next = head;
      head = new_node;
    }
  }

  T PopFront() {
    auto *current = tail;
    auto value = tail->data;
    tail->next = nullptr;
    delete current;
    return value;
  }

  T PopBack() {
    auto *current = head;
    auto value = head->data;
    head = head->next;
    delete current;
    return value;
  }

  private:
  Node<T> *head{nullptr};
  Node<T> *tail{nullptr};
};
