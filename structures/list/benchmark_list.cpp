#include <benchmark/benchmark.h>

#include "structures/list/list.hpp"

static void BM_BenchmarkInsert(benchmark::State& state) {
  // Perform setup here
  ladida::structures::List<int64_t> list;
  for (auto _ : state) {
    // This code gets timed
    for (auto j{0}; j < state.range(0); ++j) {
      list.PushBack(j);
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_BenchmarkInsert)
    ->Arg(1000);

// Run the benchmark
BENCHMARK_MAIN();
