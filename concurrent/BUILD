cc_library(
    name = "consumer_producer",
    srcs = ["consumer_producer.hpp"],
    linkopts = ["-lpthread"]
)

cc_test(
    name = "test_consumer_producer",
    srcs = [
        "test_consumer_producer.cpp",
    ],
    deps = [
        ":consumer_producer",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
