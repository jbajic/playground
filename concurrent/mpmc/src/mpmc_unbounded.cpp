#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

constexpr auto COUNTER_WORK = 100000;

/// When the queue is unbounded it can be handled with single cond variable
/// since we do not have to handle cases where queue is full or empty
template <typename T>
class UnboundedQueue {
 public:
  void Append(T num) {
    std::cout << "Waiting to append" << std::endl;
    std::unique_lock<std::mutex> lock(mtx);
    queue.push_back(num);
    cond.notify_one();
    lock.unlock();
  }

  int Pop() {
    std::cout << "Waiting to pop" << std::endl;
    std::unique_lock<std::mutex> lock(mtx);
    cond.wait(lock, [&]() { return !queue.empty(); });
    auto elem = queue.back();
    queue.pop_back();
    std::cout << "Popping " << elem << std::endl;
    return elem;
  }

 private:
  std::mutex mtx;
  std::condition_variable cond;
  std::vector<T> queue;
  size_t max_capacity;
};

int main() {
  size_t threads = std::thread::hardware_concurrency() / 2;
  assert(threads % 2 == 0);

  std::vector<std::thread> producers;
  producers.reserve(threads);
  std::vector<std::thread> consumers;
  consumers.reserve(threads);
  UnboundedQueue<int> queue;

  for (size_t i = 0; i < threads; ++i) {
    producers.emplace_back([&queue]() {
      std::random_device r;
      std::default_random_engine e1(r());
      std::uniform_int_distribution<int> uniform_dist(0, 1000);

      auto counter = COUNTER_WORK;
      while (counter != 0) {
        queue.Append(uniform_dist(e1));
        counter--;
      }
    });
  }
  std::cout << "Produces finished" << std::endl;
  for (size_t i = 0; i < threads; ++i) {
    consumers.emplace_back([&queue]() {
      auto counter = COUNTER_WORK;
      while (counter != 0) {
        queue.Pop();
        --counter;
      }
    });
  }

  // Wrap up
  for (auto &producer_thread : producers) {
    producer_thread.join();
  }
  for (auto &consumer_thread : consumers) {
    consumer_thread.join();
  }
  return 0;
}
