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
    linkopts = ["-lm"],
    tags = [
        "benchmark",
        "ds",
    ],
    deps = [
        "//structures/list",
        "@google_benchmark//:benchmark_main",
    ],
)

cc_test(
    name = "benchmark_list_insert",
    srcs = [
        "benchmark_list_insert.cpp",
    ],
    args = [
        "--benchmark_out=benchmark_list_insert.json",
        "--benchmark_out_format=json",
    ],
    linkopts = ["-lm"],
    tags = [
        "benchmark",
        "ds",
    ],
    deps = [
        "//structures/list",
        "@google_benchmark//:benchmark_main",
    ],
)

cc_test(
    name = "benchmark_list_remove",
    srcs = [
        "benchmark_list_remove.cpp",
    ],
    args = [
        "--benchmark_out=benchmark_list_remove.json",
        "--benchmark_out_format=json",
    ],
    linkopts = ["-lm"],
    tags = [
        "benchmark",
        "ds",
    ],
    deps = [
        "//structures/list",
        "@google_benchmark//:benchmark_main",
    ],
)
