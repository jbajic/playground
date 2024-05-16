#include <benchmark/benchmark.h>

#include <cassert>
#include <cstddef>
#include <latch>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>

constexpr auto MAX_QUEUE_SIZE = 100;

static void BM_MultipleProducersMultipleConsumersMutex(
    benchmark::State &state) {
  size_t threads = std::thread::hardware_concurrency() / 2;
  struct LockedQueue {
    std::mutex mtx;
    std::vector<int> queue;
    bool finished;
  };

  assert(threads % 2 == 0);

  for (auto _ : state) {
    std::vector<std::thread> producers;
    producers.reserve(threads);
    std::vector<std::thread> consumers;
    consumers.reserve(threads);
    LockedQueue queue;
    queue.finished = false;
    queue.queue.reserve(MAX_QUEUE_SIZE);

    for (size_t i = 0; i < threads; ++i) {
      producers.emplace_back([&queue]() {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, 1000);

        auto counter = 10000;
        while (counter != 0) {
          {
          auto guard = std::lock_guard<std::mutex>(queue.mtx);
          if (queue.queue.size() < MAX_QUEUE_SIZE) {
              queue.queue.push_back(uniform_dist(e1));
            }
            counter--;
          }
        }
      });
    }
    for (size_t i = 0; i < threads; ++i) {
      consumers.emplace_back([&queue]() {
        while (true) {
          auto guard = std::lock_guard<std::mutex>(queue.mtx);
          if (!queue.queue.empty()) {
            queue.queue.pop_back();
          }
          if (queue.finished) {
            return;
          }
        }
      });
    }

    // Wrap up
    for (auto &producer_thread : producers) {
      producer_thread.join();
    }
    {
      auto guard = std::lock_guard<std::mutex>(queue.mtx);
      queue.finished = true;
    }
    for (auto &consumer_thread : consumers) {
      consumer_thread.join();
    }
  }
}

BENCHMARK(BM_MultipleProducersMultipleConsumersMutex);

BENCHMARK_MAIN();
