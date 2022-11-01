cc_library(
    name = "utils",
    srcs = ["utils.hpp"],
    linkopts = [
        "-lm"
    ]
)

cc_binary(
    name = "route",
    srcs = ["route.cpp"],
)

cc_binary(
    name = "minimal_tree",
    srcs = ["minimal_tree.cpp"],
    deps = [":utils"]
)

cc_binary(
    name = "list_of_depths",
    srcs = ["list_of_depths.cpp"],
    deps = [":utils"]
)

cc_binary(
    name = "check_balanced",
    srcs = ["check_balanced.cpp"],
    deps = [":utils"]
)

cc_binary(
    name = "validate_bst",
    srcs = ["validate_bst.cpp"],
    deps = [":utils"]
)

cc_binary(
    name = "successor",
    srcs = ["successor.cpp"],
)
