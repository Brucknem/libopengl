load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "windowing-test",
    srcs = ["windowing-test.cc"],
    deps = [
        "//include:glad",
        "//lib:windowing",
        ],
    copts = ["-Iinclude", "-Ilib"],
    tags = ["local"]
)

cc_binary(
    name = "single-orange-square",
    srcs = ["single-orange-square.cc"],
    deps = [
        "//include:glad",
        "//lib:lib",
        ],
    copts = ["-Iinclude", "-Ilib"],
    tags = ["local"]
)