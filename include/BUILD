load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "glad",
    srcs = ["glad.c"],
    hdrs = ["glad/glad.h", "KHR/khrplatform.h"],
    copts = ["-Iinclude"],
    visibility = ["//visibility:public"]
)