cc_library(
    name = "list",
    srcs = [
        "list.hpp",
    ],
)

cc_binary(
    name = "main",
    srcs = [
        "main.cpp",
    ],
    deps = [
        "//structures/list",
    ],
)

cc_test(
    name = "test_list",
    srcs = [
        "test_list.cpp",
    ],
    deps = [
        "//structures/list",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "benchmark_list",
    srcs = [
        "benchmark_list.cpp",
    ],
    deps = [
        "//structures/list",
        "@google_benchmark//:benchmark_main",
    ],
    tags = ["benchmark", "ds"]
)
