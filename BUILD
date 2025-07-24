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


cc_test(
    name = "test-primes",
    srcs = ["test/simple_test.cpp"],
    deps = ["//:n-methods"],
    args = ["primes"],
)

cc_test(
    name = "test-exponentiation",
    srcs = ["test/simple_test.cpp"],
    deps = ["//:n-methods"],
    args = ["exponentiation"],
)

cc_test(
    name = "test-gcd",
    srcs = ["test/simple_test.cpp"],
    deps = ["//:n-methods"],
    args = ["gcd"],
)

cc_test(
    name = "test-sort",
    srcs = ["test/simple_test.cpp"],
    deps = ["//:n-methods"],
    args = ["sort"],
)

cc_test(
    name = "test-modulo",
    srcs = ["test/simple_test.cpp"],
    deps = ["//:n-methods"],
    args = ["modulo"],
)
