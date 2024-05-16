#include <benchmark/benchmark.h>

#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

constexpr auto MAX_QUEUE_SIZE = 100;
constexpr auto COUNTER_WORK = 100000;

class LockedQueueCond {
 public:
  void append(int num) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push_back(num);
    lock.unlock();
    cond.notify_one();
  }

  int pop() {
    std::unique_lock<std::mutex> lock(mtx);
    cond.wait(lock, [&]() { return !queue.empty(); });
    auto elem = queue.back();
    queue.pop_back();
    return elem;
  }

  void reserve(size_t capacity) { queue.reserve(capacity); }

 private:
  std::mutex mtx;
  std::condition_variable cond;
  std::vector<int> queue;
};

static void BM_MultipleProducersMultipleConsumersMutex(
    benchmark::State &state) {
  size_t threads = std::thread::hardware_concurrency() / 2;
  struct LockedQueue {
    std::mutex mtx;
    std::vector<int> queue;
  };

  assert(threads % 2 == 0);

  for (auto _ : state) {
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
            queue.queue.pop_back();
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
}

static void BM_MultipleProducersMultipleConsumersCond(benchmark::State &state) {
  size_t threads = std::thread::hardware_concurrency() / 2;
  assert(threads % 2 == 0);

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<std::thread> producers;
    producers.reserve(threads);
    std::vector<std::thread> consumers;
    consumers.reserve(threads);
    LockedQueueCond queue;
    queue.reserve(MAX_QUEUE_SIZE);

    state.ResumeTiming();
    for (size_t i = 0; i < threads; ++i) {
      producers.emplace_back([&queue]() {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, 1000);

        auto counter = COUNTER_WORK;
        while (counter != 0) {
          queue.append(uniform_dist(e1));
          counter--;
        }
      });
    }
    for (size_t i = 0; i < threads; ++i) {
      consumers.emplace_back([&queue]() {
        auto counter = COUNTER_WORK;
        while (counter != 0) {
          queue.pop();
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
}

BENCHMARK(BM_MultipleProducersMultipleConsumersMutex);
BENCHMARK(BM_MultipleProducersMultipleConsumersCond);

BENCHMARK_MAIN();
