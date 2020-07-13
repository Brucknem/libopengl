load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "windowing-test",
    srcs = ["windowing-test.cc"],
    deps = [
        "//include:glad",
        "//lib:lib",
        ],
    copts = ["-Iinclude", "-Ilib"],
)