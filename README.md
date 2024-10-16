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

### Logistics

Use own or familiar device or get familiar with available workstation. Make sure all keys work especially if keyboard is battered - if they all don't then make a note of disabled keys to avoid naming variables that spell with disabled letters - and try not to use on-screen keyboard or touch screens. Download the compressed file of the repository or use version control if available.

> [!IMPORTANT]
> Ascertain device specification specially when solution programs need to be run locally or results uploaded in absence of online judgement.
>
> Prefer 64 bit machine and install 64 bit compiler (if not pre-installed).

- Architecture and compiler compatibility
- Stack size and memory
- Stream buffer

### Milestones

Ratings are important, but learning and improvements are more important - consider blue as benchmark and try to reach above. Same goes for everything else. Register only if interested - unrated otherwise. Have fun!  

- [x] Become Cyan.  
- [ ] Become Blue.  
- [ ] Become Purple.  
    Frame it with caption:  
    "Now I have become Purple, a mixture of blue and red." :joy:  
- [ ] Edge off, but casually aim for other ranks.  
- [ ] Become Yellow (if it ever happens).  
    Frame it within a golden frame with caption:  
    "Mellow Master Me" :satisfied:  

Be impervious to AI agents. It is an art (albeit a difficult one)! Read instructions and checklists often.  
Don't get bored - boredom kills. If bored, then have **[fun](/doc/fun.md)**!  

[![Torti](https://i.ibb.co/MNrZN9v/billi.png)](https://ibb.co/MNrZN9v)
[![Billi](https://i.ibb.co/yF6TmQP/torti.png)](https://ibb.co/yF6TmQP)
[![Genie](https://i.ibb.co/Dt9VCQy/genie.png)](https://ibb.co/Dt9VCQy)  

Appreciation
------------

Course notes, books, online platforms, blogs, and tutorials.
Citations in respective source code docstring.  
