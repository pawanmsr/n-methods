Algorithms
==========

Common Algorithms and Templates.  
Personal. Educational. Quick Reference.  

Non-formal - Casual.

Build
-----

Build using CMake.

```shell
# Run build script.
bash build.sh [options: -h|c]
# Note: for minor modifications, run without flags
# or options to use build cache for quicker builds.

```

Notes and More
--------------

Source code in [src](/src/) for sport programming, assessments and limited use of STLs.  

| Operations (1 sec) | Time Complexity         |
| ------------------ | ----------------------- |
| 10^7               | O(N) May be accepted    |
| 10^6               | O(N)                    |
| 10^5               | O(N * log(N))           |
| 10^3               | O(N ^ 2)                |
| 10^2               | O(N ^ 3)                |
| 10^9               | O(log(N)) or O(sqrt(N)) |

`builtin` functions are often pre-optimized by the compiler.

Use small functions at the top of the solution. Append larger functions or group of functions, with declarations at the top, but don't be finicky about style - there are no reviews. Prefer bottom-up iterative in favor of top-down recursive. Lookout for sneaky signed overflows. Use C-style io and initializations for slightly quicker execution. Constant access time for large arrays (upwards of ten power six) increases dramatically - prefer hashmaps. Besides algorithms and data structures, also work with number theory and algebra.  

Run the build before copying the source templates into the solution. At least add basic tests for all new implementations.
Tests in [test](/test/) and method signatures in [include](/include/). Run CTest to verify and trust source code.

<pre>
.
+-- build / bin
|   - binaries
+-- doc
|   - documentation
|   +-- asset
|   |    - graphics
+-- include
|   - headers
+-- lib
|   - external libraries
+-- play
|   - templates
|   - scripts
+-- src
|   - source code
+-- test
|   - unit tests

</pre>

Problem scripts in play.

Note to self: archive (or delete, if and) when all milestones have been touched at least once.

I seek refuge in my fields of study to recharge, re-orient and organise my mind. This casual repository also contains some of my scattered thoughts (that others may find useful, especially those in adversity) bourne out of my studies and interaction. Selectively disregard it. No more casual additions are intended.  

Appreciation
------------

TODO.

Course notes, books, online platforms, blogs, and tutorials.
Citations in respective source code docstring.  
