def register_all_toolchains():
    native.register_toolchains(
        "//toolchain/clang12-x86_64:clang_x86_64_linux_toolchain",
    )
