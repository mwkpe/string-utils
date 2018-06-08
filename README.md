# string utils
A single-header collection of utility functions for strings using C++17 string_views

Status
---
Early WIP, and no guarantees but useable for simple single byte encoded strings; obviously not Unicode aware.

Example
---
```C++
using namespace nonstd::string_utils;

auto s1 = std::string{"abc"};
auto s2 = ascii::as_upper(s1);  // s1 == "abc", s2 == "ABC"
ascii::to_upper(s1);  // s1 == "ABC"

starts_with("hello world", "hello"); // true
ends_with("apple orange", "banana");  // false

auto v = split("123,456", ',');  // v[0] == "123", v[1] == "456"
```

Test and benchmark
---
g++ -std=c++17 -O2 -Wall -o test test.cpp<br>
g++ -std=c++17 -O2 -Wall -o bench bench.cpp

Using the benchmark requires the hayai header files in a bench/hayai subdirectory.

Acknowledgements
---
[doctest](https://github.com/onqtam/doctest) and [hayai](https://github.com/nickbruun/hayai) for testing
