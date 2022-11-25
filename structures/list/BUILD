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
