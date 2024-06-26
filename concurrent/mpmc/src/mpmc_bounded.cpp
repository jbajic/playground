#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

constexpr auto MAX_QUEUE_SIZE = 100;
constexpr auto COUNTER_WORK = 100000;

template <typename T>
class BoundedQueue {
 public:
  BoundedQueue(size_t capacity) : max_capicity(capacity) {
    queue.reserve(capacity);
  }

  void Append(T num) {
    std::unique_lock<std::mutex> lock(mtx);
    no_full.wait(lock, [&]() { return queue.size() < max_capicity; });
    std::cout << "Appending " << num << std::endl;
    queue.push_back(num);
    lock.unlock();
    no_empty.notify_one();
  }

  int Pop() {
    std::unique_lock<std::mutex> lock(mtx);
    no_empty.wait(lock, [&]() { return !queue.empty(); });
    auto elem = queue.back();
    queue.pop_back();
    std::cout << "Popping " << elem << std::endl;
    no_full.notify_one();
    return elem;
  }

 private:
  std::mutex mtx;
  std::condition_variable no_empty;
  std::condition_variable no_full;
  std::vector<T> queue;
  size_t max_capicity;
};

int main() {
  size_t threads = std::thread::hardware_concurrency() / 2;
  assert(threads % 2 == 0);

  std::vector<std::thread> producers;
  producers.reserve(threads);
  std::vector<std::thread> consumers;
  consumers.reserve(threads);
  BoundedQueue<int> queue(MAX_QUEUE_SIZE);

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
