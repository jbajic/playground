add_executable(mpmc_bench mpmc.cpp)
target_link_libraries(mpmc_bench benchmark::benchmark)

