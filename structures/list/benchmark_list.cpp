#include <benchmark/benchmark.h>

#include <list>

#include "structures/list/list.hpp"

static void BM_BenchmarkInsertPushBack(benchmark::State& state) {
  // Perform setup here
  ladida::structures::List<int64_t> list;
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.PushBack(j);
    }
  }
}

static void BM_BenchmarkInsertPushFront(benchmark::State& state) {
  // Perform setup here
  ladida::structures::List<int64_t> list;
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.PushFront(j);
    }
  }
}

static void BM_BenchmarkSTDInsertPushBack(benchmark::State& state) {
  // Perform setup here
  std::list<int64_t> list;
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.push_back(j);
    }
  }
}

static void BM_BenchmarkSTDInsertPushFront(benchmark::State& state) {
  // Perform setup here
  std::list<int64_t> list;
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.push_front(j);
    }
  }
}

static void BM_BenchmarkPopFront(benchmark::State& state) {
  // Perform setup here
  ladida::structures::List<int64_t> list;
  for (auto j{0}; j < state.range(0); ++j) {
    list.PushBack(j);
  }
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.PopFront();
    }
  }
}

static void BM_BenchmarkPopBack(benchmark::State& state) {
  // Perform setup here
  ladida::structures::List<int64_t> list;
  for (auto j{0}; j < state.range(0); ++j) {
    list.PushBack(j);
  }
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.PopBack();
    }
  }
}

BENCHMARK(BM_BenchmarkInsertPushBack)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000)
    ->Arg(100000000);

BENCHMARK(BM_BenchmarkInsertPushFront)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000)
    ->Arg(100000000);

BENCHMARK(BM_BenchmarkSTDInsertPushBack)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000)
    ->Arg(100000000);

BENCHMARK(BM_BenchmarkSTDInsertPushFront)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000)
    ->Arg(100000000);

BENCHMARK(BM_BenchmarkPopFront)->Arg(100000000);

BENCHMARK(BM_BenchmarkPopBack)->Arg(100000000);

// Run the benchmark
BENCHMARK_MAIN();
