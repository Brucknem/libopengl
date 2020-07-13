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
    name = "opengl_object_3d",
    srcs = ["opengl_object_3d.cc"],
    hdrs = ["opengl_object_3d.h"],
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
        "//lib:opengl_object_3d",
        "//lib:shaders",
        ],
    visibility = ["//visibility:public"],
)