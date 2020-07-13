load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "linkopts",
    linkopts = ["-lglut", "-lGLU", "-lGL", "-lglfw", "-lX11", "-lpthread", "-lXrandr", "-lXi", "-ldl"],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "windowing",
    srcs = ["windowing.cc"],
    hdrs = ["windowing.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//include:glad",
        "//lib:linkopts",
        ],
    copts = ["-Iinclude", "-Ilib/hdr"],
)

cc_library(
    name = "lib",
    deps = [
        "//lib:windowing",
        "//lib:linkopts"
        ],
    visibility = ["//visibility:public"],
)