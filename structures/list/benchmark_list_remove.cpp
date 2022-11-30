#include <benchmark/benchmark.h>

#include <list>

#include "structures/list/list.hpp"

//##################################
//  Remove - PopFront
//##################################

static void BM_BenchmarkListPopFront(benchmark::State& state) {
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

static void BM_BenchmarkStdListPopFront(benchmark::State& state) {
  // Perform setup here
  std::list<int64_t> list;
  for (auto j{0}; j < state.range(0); ++j) {
    list.push_back(j);
  }
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.pop_front();
    }
  }
}

//##################################
//  Remove - PopBack
//##################################

static void BM_BenchmarkListPopBack(benchmark::State& state) {
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

static void BM_BenchmarkStdListPopBack(benchmark::State& state) {
  // Perform setup here
  std::list<int64_t> list;
  for (auto j{0}; j < state.range(0); ++j) {
    list.push_back(j);
  }
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.pop_back();
    }
  }
}

BENCHMARK(BM_BenchmarkListPopFront)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000000);

BENCHMARK(BM_BenchmarkStdListPopFront)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000000);

BENCHMARK(BM_BenchmarkListPopBack)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000000);

BENCHMARK(BM_BenchmarkStdListPopBack)
    ->RangeMultiplier(10)
    ->Range(1000, 1000000000);

// Run the benchmark
BENCHMARK_MAIN();
