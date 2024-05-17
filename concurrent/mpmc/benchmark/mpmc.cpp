#include <benchmark/benchmark.h>

#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <thread>
#include <vector>

constexpr auto COUNTER_WORK = 1000000;

template <typename T>
struct MutexQueue {
  MutexQueue() {}

  MutexQueue(size_t max_capacity) : max_capacity(max_capacity) {
    queue.reserve(max_capacity);
  }

  void Append(T num) { queue.push_back(num); }

  T Pop() {
    auto elem = queue.back();
    queue.pop_back();
    return elem;
  }

  std::mutex mtx;
  std::vector<T> queue;
  size_t max_capacity;
};

template <typename T>
class UnboundedQueue {
 public:
  void Append(T num) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push_back(num);
    cond.notify_one();
    lock.unlock();
  }

  int Pop() {
    std::unique_lock<std::mutex> lock(mtx);
    cond.wait(lock, [&]() { return !queue.empty(); });
    auto elem = queue.back();
    queue.pop_back();
    return elem;
  }

 private:
  std::mutex mtx;
  std::condition_variable cond;
  std::vector<T> queue;
  size_t max_capacity;
};

template <typename T>
class BoundedQueue {
 public:
  BoundedQueue(size_t capacity) : max_capicity(capacity) {
    queue.reserve(capacity);
  }

  void Append(T num) {
    std::unique_lock<std::mutex> lock(mtx);
    no_full.wait(lock, [&]() { return queue.size() < max_capicity; });
    queue.push_back(num);
    lock.unlock();
    no_empty.notify_one();
  }

  int Pop() {
    std::unique_lock<std::mutex> lock(mtx);
    no_empty.wait(lock, [&]() { return !queue.empty(); });
    auto elem = queue.back();
    queue.pop_back();
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

static void BM_MPMC_UnboundedMutex(benchmark::State &state) {
  size_t threads = std::thread::hardware_concurrency() / 2;

  assert(threads % 2 == 0);

  for (auto _ : state) {
    std::vector<std::thread> producers;
    producers.reserve(threads);
    std::vector<std::thread> consumers;
    consumers.reserve(threads);
    MutexQueue<int> queue;

    for (size_t i = 0; i < threads; ++i) {
      producers.emplace_back([&queue]() {
        auto counter = COUNTER_WORK;
        while (counter != 0) {
          auto guard = std::lock_guard<std::mutex>(queue.mtx);
          queue.Append(counter);
          --counter;
        }
      });
    }
    for (size_t i = 0; i < threads; ++i) {
      consumers.emplace_back([&queue]() {
        auto counter = COUNTER_WORK;
        while (counter != 0) {
          auto guard = std::lock_guard<std::mutex>(queue.mtx);
          if (!queue.queue.empty()) {
            queue.Pop();
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

static void BM_MPMC_BoundedMutex(benchmark::State &state) {
  size_t threads = std::thread::hardware_concurrency() / 2;

  assert(threads % 2 == 0);

  for (auto _ : state) {
    std::vector<std::thread> producers;
    producers.reserve(threads);
    std::vector<std::thread> consumers;
    consumers.reserve(threads);
    MutexQueue<int> queue(state.range(0));

    for (size_t i = 0; i < threads; ++i) {
      producers.emplace_back([&queue]() {
        auto counter = COUNTER_WORK;
        while (counter != 0) {
          {
            auto guard = std::lock_guard<std::mutex>(queue.mtx);
            if (queue.queue.size() < queue.max_capacity) {
              auto num = counter;
              queue.Append(num);
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
            queue.Pop();
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

static void BM_MPMC_Unbounded(benchmark::State &state) {
  size_t threads = std::thread::hardware_concurrency() / 2;
  assert(threads % 2 == 0);

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<std::thread> producers;
    producers.reserve(threads);
    std::vector<std::thread> consumers;
    consumers.reserve(threads);
    UnboundedQueue<int> queue;

    state.ResumeTiming();
    for (size_t i = 0; i < threads; ++i) {
      producers.emplace_back([&queue]() {
        auto counter = COUNTER_WORK;
        while (counter != 0) {
          queue.Append(counter);
          counter--;
        }
      });
    }
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
  }
}

static void BM_MPMC_Bounded(benchmark::State &state) {
  size_t threads = std::thread::hardware_concurrency() / 2;
  assert(threads % 2 == 0);

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<std::thread> producers;
    producers.reserve(threads);
    std::vector<std::thread> consumers;
    consumers.reserve(threads);
    BoundedQueue<int> queue(state.range(0));

    state.ResumeTiming();
    for (size_t i = 0; i < threads; ++i) {
      producers.emplace_back([&queue]() {
        auto counter = COUNTER_WORK;
        while (counter != 0) {
          queue.Append(counter);
          counter--;
        }
      });
    }
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
  }
}

BENCHMARK(BM_MPMC_UnboundedMutex)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_MPMC_BoundedMutex)
    ->RangeMultiplier(10)
    ->Range(10, 1000)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_MPMC_BoundedMutex)
    ->RangeMultiplier(10)
    ->Range(10, 1000)
    ->Unit(benchmark::kMillisecond)
    ->MeasureProcessCPUTime();

BENCHMARK(BM_MPMC_Unbounded)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_MPMC_Unbounded)
    ->Unit(benchmark::kMillisecond)
    ->MeasureProcessCPUTime();

BENCHMARK(BM_MPMC_Bounded)
    ->RangeMultiplier(10)
    ->Range(10, 1000)
    ->Unit(benchmark::kMillisecond);
BENCHMARK(BM_MPMC_Bounded)
    ->RangeMultiplier(10)
    ->Range(10, 1000)
    ->Unit(benchmark::kMillisecond)
    ->MeasureProcessCPUTime();

BENCHMARK_MAIN();
