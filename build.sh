#! /usr/bin/bash

set -e

CMAKE_BUILD_TYPE="Debug"

# Used by google_test.
export CMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE
# FIXME: find alternative to exporting env variable.

BUILD_TOOL="cmake" # This project uses cmake.
# Other build tools: meson, bazel, premake, etc.
BUILD_FLAGS="-Wdev -DBUILD_GMOCK=OFF -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE" # "-GNinja"
# Cache is usually generated by unix makefile generator
# but Ninja is quicker at times. Ninja is also used by meson.
# Ninja Docs https://ninja-build.org/
CONFIG_FLAGS="--config $CMAKE_BUILD_TYPE"
TEST_FLAGS="--rerun-failed --output-on-failure"
# TODO: populate preset

display_options() {
    echo "Syntax: bash build.sh [options]"
    echo "Options"
    echo "  -h  Print this Help."
    echo "  -c  Force build from scratch."
    echo
}

clean_build() {
    if [ -d ./build/ ] ; then
        echo "Previous build found. Removing."
        echo
        rm -r ./build/*
        # FIXME: use flag for fresh build instead.
        # TODO: add --fresh flag for cmake version 3.24+.
    fi
}

if command -v $BUILD_TOOL &>/dev/null ; then
    while getopts hc flag ; do
        case $flag in
            c) # remove build directory
                clean_build;;
            h) # show help and exit
                display_options
                exit;;
            \?) # show help but continue
                display_options;;
        esac
    done

    echo "Building using $BUILD_TOOL!"
else
    echo "Build tool not found!"
    exit 1;
fi

# Prepare for build.
$BUILD_TOOL $BUILD_FLAGS -S . -B ./build/
# Build.
$BUILD_TOOL --build build $CONFIG_FLAGS

# Test
cd build && ctest $TEST_FLAGS

# Clean up
unset CMAKE_BUILD_TYPE
