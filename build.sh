
# Remove previous build.
# Ideally one should only remove cmake_cache.
rm -r build

# Prepare for build.
cmake -S . -B ./build/
# Build.
cmake --build build

# Test
cd build && ctest
