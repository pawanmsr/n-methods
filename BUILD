# Bazel build.
cc_import(
    name = "headers",
    hdrs = glob(["include/*.hpp"]),
    visibility = ["//visibility:private"],
)

cc_library(
    name = "n-methods",
    srcs = glob(["src/*.cpp"]),
    includes = ["include"],
    deps = ["headers"],
    visibility = ["//visibility:public"],
)
