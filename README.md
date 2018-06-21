# string_utils
A single-header collection of utility functions for strings using C++17 `string_view`.

Status
---
Early WIP, and no guarantees but useable for simple single byte encoded strings; obviously not Unicode aware.

Examples
---
```C++
using namespace nonstd::string_utils;

// Check
starts_with("hello world", "hello"); // true
ends_with("apple orange", "banana");  // false

// Split
auto view = split("hello,world", ",");  // Returns vector<string_view>
auto copy = split_copy("hello,world", ",");  // Returns vector<string>
// Empty parts are kept by default
auto a = split("123-456-", "-");  // a.size() == 3, a[0] == "123", a[1] == "456", a[2] empty
// Ignore empty parts
auto b = split("123-456-", "-", false);  // b.size() == 2, b[0] == "123", b[1] == "456"

// Grab
auto line = std::string{"<AzureDiamond> doesnt look like stars to me"};
auto message = after_first(line, "> ");  // message = "doesnt look like stars to me"
auto name = between(line, "<", ">");  // name = "AzureDiamond"

// Replace
auto r = replace("hello world", "hello", "goodbye");  // r = "goodbye world"

// Conversion
auto i = as_int("42");  // i = 42
auto f = as_float("13.37");  // f = 13.37

// Awesome
auto csv = std::string{"42,13.37,no copies made"};
auto values = split(csv, ",");
auto i = as_uint8(values[0]);  // i = 42
auto f = as_float(values[1]);  // f = 13.37
auto sv = values[2]; // sv = "no copies made" (ok, as_float still does a copy until from_chars supports float)

// ASCII stuff
auto s1 = std::string{"abc"};
auto s2 = ascii::as_upper(s1);  // s1 == "abc", s2 == "ABC"
ascii::to_upper(s1);  // s1 == "ABC"
```

Test and benchmark
---
`g++ -std=c++17 -O2 -Wall -o test test.cpp`<br>
`g++ -std=c++17 -O2 -Wall -o bench bench.cpp`

Using the benchmark requires the hayai header files in a bench/hayai subdirectory.

Acknowledgements
---
[doctest](https://github.com/onqtam/doctest) and [hayai](https://github.com/nickbruun/hayai) for testing
