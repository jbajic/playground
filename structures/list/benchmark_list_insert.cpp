#include <benchmark/benchmark.h>

#include <list>

#include "structures/list/list.hpp"

//##################################
//  Insert - PushBack
//##################################
static void BM_BenchmarkListInsertPushBack(benchmark::State& state) {
  // Perform setup here
  ladida::structures::List<int64_t> list;
  for (auto _ : state) {
    for (auto j{0}; j < state.range(0); ++j) {
      list.PushBack(j);
    }
  }
}

static void BM_BenchmarkStdListInsertPushBack(benchmark::State& state) {
  // Perform setup here
  std::list<int64_t> list;
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.push_back(j);
    }
  }
}

//##################################
//  Insert - PushFront
//##################################

static void BM_BenchmarkListInsertPushFront(benchmark::State& state) {
  ladida::structures::List<int64_t> list;
  for (auto _ : state) {
    for (auto j{0}; j < state.range(0); ++j) {
      list.PushFront(j);
    }
  }
}

static void BM_BenchmarkStdListInsertPushFront(benchmark::State& state) {
  std::list<int64_t> list;
  for (auto _ : state) {
    for (auto j{0}; j < state.range(0); ++j) {
      list.push_front(j);
    }
  }
}

BENCHMARK(BM_BenchmarkListInsertPushBack)
    ->RangeMultiplier(10)
    ->Range(1000, 10000000)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_BenchmarkStdListInsertPushBack)
    ->RangeMultiplier(10)
    ->Range(1000, 10000000)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_BenchmarkListInsertPushFront)
    ->RangeMultiplier(10)
    ->Range(1000, 10000000)
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_BenchmarkStdListInsertPushFront)
    ->RangeMultiplier(10)
    ->Range(1000, 10000000)
    ->Unit(benchmark::kMillisecond);

// Run the benchmark
BENCHMARK_MAIN();
