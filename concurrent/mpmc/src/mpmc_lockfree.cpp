#include <atomic>
#include <iostream>
#include <memory>

constexpr auto MAX_QUEUE_SIZE = 100;
constexpr auto COUNTER_WORK = 100000;

template <typename T>
class UnboundedLockFreeQueue {
 public:
  /*
   * We now review all the steps in detail. An enqueuer creates a new node with
   * the new value to be enqueued (Line 33), reads tail, and finds the node that
   * appears to be last (Lines 35–36). To verify that node is indeed last, it
   * checks whether that node has a successor (Line 39). If so, the thread
   * attempts to append the new node by calling compare_exchange_weak() (Line 41). (A
   * compare_exchange_weak() is required because other threads may be trying the same
   * thing.) If the compare_exchange_weak() succeeds, the thread uses a second
   * compare_exchange_weak() to advance tail to the new node (Line 43). Even if this
   * second compare_exchange_weak() call fails, the thread can still return successfully
   * because, as we will see, the call fails only if some other thread “helped”
   * it by advancing tail. If the tail node has a successor (Line 46), then the
   * method tries to “help” other threads by advancing tail to refer directly to
   * the successor (Line 47) before trying again to insert its own node. This
   * enq() is total, meaning that it never waits for a dequeuer. A successful
   * enq() is linearized at the instant where the executing thread (or a
   * concurrent helping thread) calls compare_exchange_weak() to redirect the tail field
   * to the new node at Line 47
   *
   * The Art of Multiprocessprogramming, 10.5 Chapter (Unbounded Lock Free Queue)
   */
  void Push(const T& data) {
    auto node = std::make_shared(data);
    while (true) {
      Node last = tail.load(std::memory_order_relaxed);
      Node next = last.next.load(std::memory_order_relaxed);
      // Check if somebody already changed tail, if so retry
      if (last == tail.load(std::memory_order_relaxed)) {
        if (next == nullptr) {
          // Set the next pointer to the new node
          if (last.next.compare_exchange_weak(next, node)) {
            // Update the new tail with the new node
            tail.compare_exchange_weak(last, node);
            return;
          }
        } else {
          // We help other threads by advancing the current tail to the next one
          tail.compare_exchange_weak(last, next);
        }
      }
    }
  }

 private:
  struct Node {
    Node(T data) : data{data} {}

    std::atomic<Node*> next;
    std::shared_ptr<T> data;
  };

  std::atomic<Node*> head;
  std::atomic<Node*> tail;
};

int main() {
  std::cout << "Hello World!" << std::endl;

  return 0;
}
