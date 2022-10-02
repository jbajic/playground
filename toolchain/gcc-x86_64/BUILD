package(default_visibility = ["//visibility:public"])
load(":cc_toolchain_config.bzl", "cc_toolchain_config")

cc_toolchain_config(name = "gcc_x86_64_toolchain_config")

cc_toolchain(
    name = "gcc_x86_64_toolchain",
    toolchain_identifier = "gcc_x86_64_toolchain",
    toolchain_config = ":gcc_x86_64_toolchain_config",
    all_files = ":gcc_x86_64_toolchain_config",
    compiler_files = ":gcc_x86_64_toolchain_config",
    dwp_files = ":gcc_x86_64_toolchain_config",
    linker_files = ":gcc_x86_64_toolchain_config",
    objcopy_files = ":gcc_x86_64_toolchain_config",
    strip_files = ":gcc_x86_64_toolchain_config",
    supports_param_files = 0,
)

cc_toolchain_suite(
    name = "gcc_suite",
    toolchains = {
        "x86_64": ":gcc_x86_64_toolchain",
    },
)

toolchain(
    name = "gcc_x86_64_linux_toolchain",
    exec_compatible_with = [
        "@platforms//os:linux",
        "@platforms//cpu:x86_64",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
        "@platforms//cpu:x86_64",
    ],
    toolchain = ":gcc_x86_64_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
