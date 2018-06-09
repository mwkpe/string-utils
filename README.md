# string utils
A single-header collection of utility functions for strings using C++17 `string_view`, i.e. no copies are made from the input. Functions will return a tuple, vector or simple `string_view`.

Status
---
Early WIP, and no guarantees but useable for simple single byte encoded strings; obviously not Unicode aware.

Examples
---
```C++
using namespace nonstd::string_utils;

starts_with("hello world", "hello"); // true
ends_with("apple orange", "banana");  // false

auto a = split("hello123world", "123");  // a.size() == 2, a[0] == "hello", a[1] == "world"
// Keep empty parts by default
auto b = split("123,456,", ",");  // b.size() == 3, b[0] == "123", b[1] == "456", b[2] empty
// Ignore empty parts
auto c = split("123,456,", ",", false);  // c.size() == 2, c[0] == "123", c[1] == "456"

auto s1 = std::string{"abc"};
auto s2 = ascii::as_upper(s1);  // s1 == "abc", s2 == "ABC"
ascii::to_upper(s1);  // s1 == "ABC"
```

Test and benchmark
---
g++ -std=c++17 -O2 -Wall -o test test.cpp<br>
g++ -std=c++17 -O2 -Wall -o bench bench.cpp

Using the benchmark requires the hayai header files in a bench/hayai subdirectory.

Acknowledgements
---
[doctest](https://github.com/onqtam/doctest) and [hayai](https://github.com/nickbruun/hayai) for testing
