# Running benchmarks

Install google benchmark and perf support


```bash
cmake -DCMAKE_BUILD_TYPE=Release .. 
make
sudo ./benchmark/mpmc_bench --benchmark_repetitions=3 --benchmark_perf_counters="CYCLES,INSTRUCTIONS"
```
