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
        "//lib:OpenGLObject3D",
        ],
    copts = ["-Iinclude", "-Ilib/hdr"],
)

cc_library(
    name = "OpenGLObject3D",
    srcs = ["OpenGLObject3D.cc"],
    hdrs = ["OpenGLObject3D.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//include:glad",
        "//lib:linkopts",
        "//lib:shaders",
        ],
    copts = ["-Iinclude", "-Ilib/hdr"],
)

cc_library(
    name = "shaders",
    srcs = ["shader.cc"],
    hdrs = ["shader.h"],
    visibility = ["//visibility:public"],
    data = [
        "//shaders:shaders",
    ],
    deps = [
        "//include:glad",
        "//lib:linkopts",
        ],
    copts = ["-Iinclude", "-Ilib/hdr", "-Ishaders"],
)

cc_library(
    name = "lib",
    deps = [
        "//lib:windowing",
        "//lib:linkopts",
        "//lib:OpenGLObject3D",
        "//lib:shaders",
        ],
    visibility = ["//visibility:public"],
)