#include <cassert>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

constexpr auto MAX_QUEUE_SIZE = 100;
constexpr auto COUNTER_WORK = 100000;

int main() {
  size_t threads = std::thread::hardware_concurrency() / 2;
  struct LockedQueue {
    std::mutex mtx;
    std::vector<int> queue;
  };

  assert(threads % 2 == 0);
  std::vector<std::thread> producers;
  producers.reserve(threads);
  std::vector<std::thread> consumers;
  consumers.reserve(threads);

  LockedQueue queue;
  queue.queue.reserve(MAX_QUEUE_SIZE);

  for (size_t i = 0; i < threads; ++i) {
    producers.emplace_back([&queue]() {
      std::random_device r;
      std::default_random_engine e1(r());
      std::uniform_int_distribution<int> uniform_dist(0, 1000);

      auto counter = COUNTER_WORK;
      while (counter != 0) {
        {
          auto guard = std::lock_guard<std::mutex>(queue.mtx);
          if (queue.queue.size() < MAX_QUEUE_SIZE) {
            auto num = uniform_dist(e1);
            std::cout << "Producer producing " << num << std::endl;
            queue.queue.push_back(num);
          }
          --counter;
        }
      }
    });
  }
  for (size_t i = 0; i < threads; ++i) {
    consumers.emplace_back([&queue]() {
      auto counter = COUNTER_WORK;
      while (counter != 0) {
        auto guard = std::lock_guard<std::mutex>(queue.mtx);
        if (!queue.queue.empty()) {
          auto num = queue.queue.back();
          queue.queue.pop_back();
          std::cout << "Consumer consuming " << num << std::endl;
        }
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
}
