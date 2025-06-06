#! /usr/bin/bash

set -e

CMAKE_BUILD_TYPE="Debug"

BUILD_TOOL="cmake" # This project uses cmake.
# Other build tools: meson, bazel, premake, etc.
BUILD_FLAGS="-Wdev -DBUILD_GMOCK=OFF -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE" # "-GNinja"
# Cache is usually generated by unix makefile generator
#   but Ninja is quicker at times. Ninja is also used by meson.
# Ninja Docs https://ninja-build.org/
CONFIG_FLAGS="--config $CMAKE_BUILD_TYPE"

TEST_TOOL="ctest"
TEST_FLAGS="--rerun-failed --output-on-failure"

PROCESSORS=0

display_options() {
    echo "Syntax: bash build.sh [options]"
    echo "Options"
    echo "  -h  Print this Help."
    echo "  -r  Remove previous build."
    echo "  -c  Regenerate build tree and targets."
    echo
}

remove_build() {
    if [ -d ./build/ ] ; then
        echo "Previous build found. Removing."
        echo
        rm -r ./build/*
    fi
}

clean_build() {
    BUILD_FLAGS="${BUILD_FLAGS} --fresh"
    CONFIG_FLAGS="${CONFIG_FLAGS} --clean-first"
}

pre_process() {
    # Used by google_test.
    export CMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE
    # FIXME: find alternative to exporting env variable.

    local GNU_PROCESSORS="nproc --all"
    local UNIX_PROCESSORS="sysctl -n hw.logicalcpu"
    if [ $PROCESSORS -lt 0 ] ; then
        echo "Parallel execution!"
    elif $UNIX_PROCESSORS &>/dev/null ; then
        PROCESSORS=$($UNIX_PROCESSORS)
    elif $GNU_PROCESSORS &>/dev/null ; then
        PROCESSORS=$($GNU_PROCESSORS)
    fi

    if [ $PROCESSORS -gt 1 ] ; then
        local PARALLEL_FLAG="--parallel ${PROCESSORS}"
        CONFIG_FLAGS="${CONFIG_FLAGS} ${PARALLEL_FLAG}"
        TEST_FLAGS="${TEST_FLAGS} ${PARALLEL_FLAG}"
        PROCESSORS=-1
    fi
}

# Build
if command -v $BUILD_TOOL &>/dev/null ; then
    while getopts rch flag ; do
        case $flag in
            r) # remove build directory
                remove_build
                exit;;
            c) # clean build
                clean_build;;
            h) # show help and exit
                display_options
                exit;;
            \?) # show help but continue
                display_options;;
        esac
    done

    pre_process;
    echo "Building using $BUILD_TOOL!"
    # Prepare for build.
    $BUILD_TOOL $BUILD_FLAGS -S . -B ./build/
    # Build.
    $BUILD_TOOL --build build $CONFIG_FLAGS
    echo
else
    echo "Build tool not found!"
    exit 1;
fi

# Test
if command -v $TEST_TOOL &>/dev/null ; then
    pre_process;
    echo "Testing using $TEST_TOOL!"
    cd build && $TEST_TOOL $TEST_FLAGS
    echo
else
    echo "Test tool not found!"
    exit 0;
fi
