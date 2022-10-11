package(default_visibility = ["//visibility:public"])

load(":cc_toolchain_config.bzl", "cc_toolchain_config")

cc_toolchain_config(name = "clang_x86_64_toolchain_config")

cc_toolchain(
    name = "clang_x86_64_toolchain",
    all_files = ":clang_x86_64_toolchain_config",
    compiler_files = ":clang_x86_64_toolchain_config",
    dwp_files = ":clang_x86_64_toolchain_config",
    linker_files = ":clang_x86_64_toolchain_config",
    objcopy_files = ":clang_x86_64_toolchain_config",
    strip_files = ":clang_x86_64_toolchain_config",
    supports_param_files = 0,
    toolchain_config = ":clang_x86_64_toolchain_config",
    toolchain_identifier = "clang_x86_64_toolchain",
)

cc_toolchain_suite(
    name = "clang_suite",
    toolchains = {
        "x86_64": ":clang_x86_64_toolchain",
    },
)

toolchain(
    name = "clang_x86_64_linux_toolchain",
    exec_compatible_with = [
        "@platforms//os:linux",
        "@platforms//cpu:x86_64",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
        "@platforms//cpu:x86_64",
    ],
    toolchain = ":clang_x86_64_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
