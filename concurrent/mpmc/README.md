# Running benchmarks

Install google benchmark and perf support


```bash
cmake -DCMAKE_BUILD_TYPE=Release .. 
make
sudo ./benchmark/mpmc_bench --benchmark_repetitions=3 --benchmark_perf_counters="CYCLES,INSTRUCTIONS"
```

Use --benchmark_filter=<regex> to run specific benchmarks

Interesting perf counters:
 * CYCLES,
 * INSTRUCTIONS

## Observations:
* Using random in multihreaded testing environment is actually bad since random itself
takes a lock on a global state causing additional overhead when testing mutex
overheads. (https://ashvardanian.com/posts/google-benchmark/#hardware-performance-counters)

