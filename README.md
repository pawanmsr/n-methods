Algorithms
==========

Common Algorithms and Templates.  
Personal. Educational. Quick Reference.  

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

Documentation
-------------

[Sport Programming](/doc/sport-programming.md).  
If bored, then have **[fun](/doc/fun.md)**!  

Implementations Pending:

- [ ] Splines
- [ ] Splay tree
- [ ] Interpolation
- [ ] Geometry and Mesh (2D)
- [ ] . . . 
- [ ] (Redo with) Parallel processing

@pawanmsr: archive (or delete, if and) when all milestones have been touched at least once.

Appreciation
------------

TODO.

Course notes, books, online platforms, blogs, and tutorials.
Citations in respective source code docstring.  
