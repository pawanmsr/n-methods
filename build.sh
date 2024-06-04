#! /usr/bin/bash

set -e

display_options() {
    echo "Syntax: bash build.sh [options]"
    echo "Options"
    echo "  -h  Print this Help."
    echo "  -c  Force build from scratch."
    echo
}

clean_build() {
    echo "Removing previous build (if exists)."
    echo
    rm -r ./build/*
}

BUILD_TOOL="cmake" # This project uses cmake.
# Other build tools: meson, bazel, premake, etc.

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
cmake -S . -B ./build/
# Build.
cmake --build build

# Test
cd build && ctest
