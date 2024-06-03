Algorithms
==========

Common Algorithms and Templates.  
Personal. Educational. Quick Reference.  

Directory Structure
-------------------

<pre>
+-- bin
|   - binaries
+-- doc
|   - documentation
+-- include
|   - headers
+-- lib
|   - external libraries
+-- play
|   - templates
+-- src
|   - source code
+-- test
|   - unit tests
</pre>

Build
-----

Build using CMake.

```shell

# Write build files and build the lib.
cmake -S . -B ./build/
cmake --build build

# Visit build and run CTest.
cd build && ctest

```
