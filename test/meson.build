# Tests

simple_test_exe = executable(
    'simple_test', 
    'simple_test.cpp',
    link_with: lib,
    include_directories: inc_dir
)

gtest_exe = executable(
  'gtest', 
  'google_test.cpp',
  link_with : lib,
  include_directories: inc_dir,
  dependencies : gtest_dep
)

args = [
  'primes',
  'exponentiation',
  'gcd',
  'sort',
  'modulo'
]

foreach arg : args
  test('simple_test', simple_test_exe, args: arg)
endforeach

test('gtest', gtest_exe)
