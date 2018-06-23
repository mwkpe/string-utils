#include "../string_utils.h"
#include <limits>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


TEST_CASE("ascii case functions") {
  using namespace nonstd::string_utils;

  SUBCASE("to_upper") {
    auto s = std::string{"abc_XYZ,-$"};
    ascii::to_upper(s);
    CHECK(s == "ABC_XYZ,-$");

    s = std::string{""};
    ascii::to_upper(s);
    CHECK(s == "");
  }

  SUBCASE("to_lower") {
    auto s = std::string{"abc_XYZ,-$"};
    ascii::to_lower(s);
    CHECK(s == "abc_xyz,-$");

    s = std::string{""};
    ascii::to_lower(s);
    CHECK(s == "");
  }

  SUBCASE("as_upper") {
    CHECK(ascii::as_upper("abc_XYZ,-$") == "ABC_XYZ,-$");
    CHECK(ascii::as_upper("") == "");
  }

  SUBCASE("as_lower") {
    CHECK(ascii::as_lower("abc_XYZ,-$") == "abc_xyz,-$");
    CHECK(ascii::as_lower("") == "");
  }
}


TEST_CASE("split_chars") {
  using namespace nonstd::string_utils;

  SUBCASE("1") {
    auto v = split_chars("abcdefghijklmnop", 3);
    CHECK(v.size() == 6);
    CHECK(v[0] == "abc");
    CHECK(v[1] == "def");
    CHECK(v[2] == "ghi");
    CHECK(v[3] == "jkl");
    CHECK(v[4] == "mno");
    CHECK(v[5] == "p");
  }

  SUBCASE("2") {
    auto v = split_chars("abc,def,ghi,jkl,mno,p", 3, 1);
    CHECK(v.size() == 6);
    CHECK(v[0] == "abc");
    CHECK(v[1] == "def");
    CHECK(v[2] == "ghi");
    CHECK(v[3] == "jkl");
    CHECK(v[4] == "mno");
    CHECK(v[5] == "p");
  }

  SUBCASE("3") {
    auto v = split_chars("abc,def,ghi,jkl,mno,p", 0);
    CHECK(v.size() == 0);
  }

  SUBCASE("4") {
    auto v = split_chars("", 1);
    CHECK(v.size() == 0);
  }

  SUBCASE("5") {
    auto v = split_chars("abc", 1, 1);
    CHECK(v.size() == 2);
    CHECK(v[0] == "a");
    CHECK(v[1] == "c");
  }

  SUBCASE("6") {
    auto v = split_chars("abc", 1, 2);
    CHECK(v.size() == 1);
    CHECK(v[0] == "a");
  }
}


TEST_CASE("starts_with") {
  using namespace nonstd::string_utils;

  CHECK(starts_with("hello world", "hello") == true);
  CHECK(starts_with("hello world", "h") == true);
  CHECK(starts_with("hello world", "hello w") == true);
  CHECK(starts_with("hello world", "hello world") == true);
  CHECK(starts_with(u8"初音ミク", u8"初音") == true);

  CHECK(starts_with("hello world", "world") == false);
  CHECK(starts_with("hello world", "") == false);
  CHECK(starts_with("", "hello") == false);
  CHECK(starts_with("hello world", "hello world ") == false);
  CHECK(starts_with("", "") == false);
  CHECK(starts_with(u8"初音ミク", u8"音") == false);
}


TEST_CASE("ends_with") {
  using namespace nonstd::string_utils;

  CHECK(ends_with("hello world", "world") == true);
  CHECK(ends_with("hello world", "d") == true);
  CHECK(ends_with("hello world", "o world") == true);
  CHECK(ends_with("hello world", "hello world") == true);
  CHECK(ends_with(u8"初音ミク", u8"ミク") == true);

  CHECK(ends_with("hello world", "hello") == false);
  CHECK(ends_with("hello world", "") == false);
  CHECK(ends_with("", "world") == false);
  CHECK(ends_with("hello world", " hello world") == false);
  CHECK(ends_with("", "") == false);
  CHECK(ends_with(u8"初音ミク", u8"音") == false);
}


TEST_CASE("split keep empty") {
  using namespace nonstd::string_utils;

  // Single character token
  //

  SUBCASE("1") {
    auto v = split("a,b,c", ",");
    CHECK(v.size() == 3);
    CHECK(v[0] == "a");
    CHECK(v[1] == "b");
    CHECK(v[2] == "c");
  }

  SUBCASE("2") {
    auto v = split(",bb,cc", ",");
    CHECK(v.size() == 3);
    CHECK(v[0].empty());
    CHECK(v[1] == "bb");
    CHECK(v[2] == "cc");
  }

  SUBCASE("3") {
    auto v = split("aaa,b,", ",");
    CHECK(v.size() == 3);
    CHECK(v[0] == "aaa");
    CHECK(v[1] == "b");
    CHECK(v[2].empty());
  }

  SUBCASE("4") {
    auto v = split("aaa,b,", "x");
    CHECK(v.size() == 1);
    CHECK(v[0] == "aaa,b,");
  }

  SUBCASE("5") {
    auto v = split("", ",");
    CHECK(v.size() == 1);
    CHECK(v[0].empty());
  }

  SUBCASE("6") {
    auto v = split(",", ",");
    CHECK(v.size() == 2);
    CHECK(v[0].empty());
    CHECK(v[1].empty());
  }

  SUBCASE("7") {
    auto v = split(",,", ",");
    CHECK(v.size() == 3);
    CHECK(v[0].empty());
    CHECK(v[1].empty());
    CHECK(v[2].empty());
  }

  // Multi-character token
  //

  SUBCASE("8") {
    auto v = split("a123b123c", "123");
    CHECK(v.size() == 3);
    CHECK(v[0] == "a");
    CHECK(v[1] == "b");
    CHECK(v[2] == "c");
  }

  SUBCASE("9") {
    auto v = split("123bb123cc", "123");
    CHECK(v.size() == 3);
    CHECK(v[0].empty());
    CHECK(v[1] == "bb");
    CHECK(v[2] == "cc");
  }

  SUBCASE("10") {
    auto v = split("aaa123b123", "123");
    CHECK(v.size() == 3);
    CHECK(v[0] == "aaa");
    CHECK(v[1] == "b");
    CHECK(v[2].empty());
  }

  SUBCASE("11") {
    auto v = split("aaa123b123", "xyz");
    CHECK(v.size() == 1);
    CHECK(v[0] == "aaa123b123");
  }

  SUBCASE("12") {
    auto v = split("", "123");
    CHECK(v.size() == 1);
    CHECK(v[0].empty());
  }

  SUBCASE("13") {
    auto v = split("123", "123");
    CHECK(v.size() == 2);
    CHECK(v[0].empty());
    CHECK(v[1].empty());
  }

  SUBCASE("14") {
    auto v = split("123123", "123");
    CHECK(v.size() == 3);
    CHECK(v[0].empty());
    CHECK(v[1].empty());
    CHECK(v[2].empty());
  }
}


TEST_CASE("split ignore empty") {
  using namespace nonstd::string_utils;

  // Single character token
  //

  SUBCASE("1") {
    auto v = split("a,b,c", ",", false);
    CHECK(v.size() == 3);
    CHECK(v[0] == "a");
    CHECK(v[1] == "b");
    CHECK(v[2] == "c");
  }

  SUBCASE("2") {
    auto v = split(",bb,cc", ",", false);
    CHECK(v.size() == 2);
    CHECK(v[0] == "bb");
    CHECK(v[1] == "cc");
  }

  SUBCASE("3") {
    auto v = split("aaa,b,", ",", false);
    CHECK(v.size() == 2);
    CHECK(v[0] == "aaa");
    CHECK(v[1] == "b");
  }

  SUBCASE("4") {
    auto v = split("aaa,b,", "x", false);
    CHECK(v.size() == 1);
    CHECK(v[0] == "aaa,b,");
  }

  SUBCASE("5") {
    auto v = split("", ",", false);
    CHECK(v.size() == 0);
  }

  SUBCASE("6") {
    auto v = split(",", ",", false);
    CHECK(v.size() == 0);
  }

  SUBCASE("7") {
    auto v = split(",,", ",", false);
    CHECK(v.size() == 0);
  }

  // Multi-character token
  //

  SUBCASE("8") {
    auto v = split("a123b123c", "123", false);
    CHECK(v.size() == 3);
    CHECK(v[0] == "a");
    CHECK(v[1] == "b");
    CHECK(v[2] == "c");
  }

  SUBCASE("9") {
    auto v = split("123bb123cc", "123", false);
    CHECK(v.size() == 2);
    CHECK(v[0] == "bb");
    CHECK(v[1] == "cc");
  }

  SUBCASE("10") {
    auto v = split("aaa123b123", "123", false);
    CHECK(v.size() == 2);
    CHECK(v[0] == "aaa");
    CHECK(v[1] == "b");
  }

  SUBCASE("11") {
    auto v = split("aaa123b123", "xyz", false);
    CHECK(v.size() == 1);
    CHECK(v[0] == "aaa123b123");
  }

  SUBCASE("12") {
    auto v = split("", "123", false);
    CHECK(v.size() == 0);
  }

  SUBCASE("13") {
    auto v = split("123", "123", false);
    CHECK(v.size() == 0);
  }

  SUBCASE("14") {
    auto v = split("123123", "123", false);
    CHECK(v.size() == 0);
  }
}


TEST_CASE("split first/last") {
  using namespace nonstd::string_utils;

  SUBCASE("1") {
    CHECK(split_first("The quick brown fox", "o") == std::make_tuple("The quick br", "wn fox"));
    CHECK(split_first("The quick brown fox", "x") == std::make_tuple("The quick brown fo", ""));
    CHECK(split_first("The quick brown fox", "The") == std::make_tuple("", " quick brown fox"));
    CHECK(split_first("The quick brown fox", "") == std::make_tuple("", "The quick brown fox"));
    CHECK(split_first("The quick brown fox", "banana") == std::make_tuple("The quick brown fox", ""));
    CHECK(split_first("", "banana") == std::make_tuple("", ""));
    CHECK(split_first("", "") == std::make_tuple("", ""));

    CHECK(split_last("The quick brown fox", "o") == std::make_tuple("The quick brown f", "x"));
    CHECK(split_last("The quick brown fox", "x") == std::make_tuple("The quick brown fo", ""));
    CHECK(split_last("The quick brown fox", "The") == std::make_tuple("", " quick brown fox"));
    CHECK(split_last("The quick brown fox", "") == std::make_tuple("The quick brown fox", ""));
    CHECK(split_last("The quick brown fox", "banana") == std::make_tuple("The quick brown fox", ""));
    CHECK(split_last("", "banana") == std::make_tuple("", ""));
    CHECK(split_last("", "") == std::make_tuple("", ""));
  }
}


TEST_CASE("before/after first/last") {
  using namespace nonstd::string_utils;

  SUBCASE("1") {
    CHECK(before_first("The quick brown fox", "o") == "The quick br");
    CHECK(before_first("The quick brown fox", "x") == "The quick brown fo");
    CHECK(before_first("The quick brown fox", "The") == "");
    CHECK(before_first("The quick brown fox", "The quick brown fox") == "");
    CHECK(before_first("The quick brown fox", "banana") == "");
  }

  SUBCASE("2") {
    CHECK(before_last("The quick brown fox", "o") == "The quick brown f");
    CHECK(before_last("The quick brown fox", "x") == "The quick brown fo");
    CHECK(before_last("The quick brown fox", "The") == "");
    CHECK(before_last("The quick brown fox", "The quick brown fox") == "");
    CHECK(before_last("The quick brown fox", "banana") == "");
  }

  SUBCASE("3") {
    CHECK(after_first("The quick brown fox", "o") == "wn fox");
    CHECK(after_first("The quick brown fox", "x") == "");
    CHECK(after_first("The quick brown fox", "The") == " quick brown fox");
    CHECK(after_first("The quick brown fox", "The quick brown fox") == "");
    CHECK(after_first("The quick brown fox", "banana") == "");
  }

  SUBCASE("4") {
    CHECK(after_last("The quick brown fox", "o") == "x");
    CHECK(after_last("The quick brown fox", "x") == "");
    CHECK(after_last("The quick brown fox", "The") == " quick brown fox");
    CHECK(after_last("The quick brown fox", "The quick brown fox") == "");
    CHECK(after_last("The quick brown fox", "banana") == "");
  }

  SUBCASE("5") {
    const char* s = "<AzureDiamond> doesnt look like stars to me";
    CHECK(after_first(before_first(s, ">"), "<") == "AzureDiamond");
  }
}


TEST_CASE("between") {
  using namespace nonstd::string_utils;
  const char* s = "<AzureDiamond> doesnt <look> like stars to me";
  CHECK(between(s, "<", ">") == "AzureDiamond");
  CHECK(between(s, "<", ">", true) == "AzureDiamond> doesnt <look");
  CHECK(between(s, ">", "<") == "");
  CHECK(rbetween(s, ">", "<") == "look");
  CHECK(rbetween(s, ">", "<", true) == "AzureDiamond> doesnt <look");
  CHECK(rbetween(s, "<", ">") == "");
}


TEST_CASE("replace") {
  using namespace std::string_literals;
  using namespace nonstd::string_utils;

  SUBCASE("1") {
    auto s1 = replace("hello beautiful world", "beautiful", "wretched");
    auto s2 = replace(s1, "hello", "goodbye");
    auto s3 = replace(s2, "world", "existence");
    CHECK(s1 == "hello wretched world");
    CHECK(s2 == "goodbye wretched world");
    CHECK(s3 == "goodbye wretched existence");
  }

  SUBCASE("2") {
    auto s = replace("man fears time", "time", "the pyramids");
    s = replace(s, "man", "time");
    CHECK(s == "time fears the pyramids");
  }

  SUBCASE("3") {
    CHECK(replace("abc", "a", "x") == "xbc");
    CHECK(replace("abc", "b", "x") == "axc");
    CHECK(replace("abc", "c", "x") == "abx");
    CHECK(replace("aabbcc", "a", "x") == "xxbbcc");
    CHECK(replace("aabbcc", "b", "x") == "aaxxcc");
    CHECK(replace("aabbcc", "c", "x") == "aabbxx");
  }

  SUBCASE("4") {
    auto s = std::string{"test with test ok, test123 test"};
    CHECK(replace(s, "test", "rofl") == "rofl with rofl ok, rofl123 rofl");
  }

  SUBCASE("5") {
    auto s = std::string{"test with test ok, test123 test"};
    CHECK(detail::replace_inplace(s, "test", "rofl") == "rofl with rofl ok, rofl123 rofl");
  }
}


TEST_CASE("readme") {
  using namespace nonstd::string_utils;
  auto csv = std::string{"42,13.37,test"};
  auto values = split(csv, ",");
  auto i = as_uint8(values[0]);
  auto f = as_float(values[1]);
  auto s = as_string(values[2]);
  CHECK(values.size() == 3);
  CHECK(i == 42);
  CHECK(f == doctest::Approx(13.37));
  CHECK(s == "test");
}


TEST_CASE("split and split_chars cross check") {
  using namespace nonstd::string_utils;
  const char* s = "123,456,789,3";
  auto v1 = split(s, ",");
  auto v2 = split_chars(s, 3, 1);
  CHECK(v1.size() == v2.size());
  CHECK(v1[0] == v2[0]);
  CHECK(v1[1] == v2[1]);
  CHECK(v1[2] == v2[2]);
  CHECK(v1[3] == v2[3]);
}


#ifdef NONSTD_STRING_UTILS_CHARCONV
TEST_CASE("parse_number") {
  using namespace nonstd::string_utils;
  CHECK(as_string("0") == "0");
  CHECK(as_int("0") == 0);
  CHECK(as_int("1024") == 1024);
  CHECK(as_int("-1024") == -1024);
  CHECK(as_int("7FFFFFFF", 16) == 0x7FFFFFFF);
  CHECK(as_int("80000000", 16) == 0);
  CHECK(as_int("") == 0);
  CHECK(as_int("0.0") == 0);
  CHECK(as_int("13.37") == 13);
  CHECK(as_float("13.37") == doctest::Approx(13.37));
  CHECK(as_uint8("255") == 255);
  CHECK(as_uint8("256") == 0);
  CHECK(as_uint8("257") == 0);
  CHECK(as_uint8("-1") == 0);
  CHECK(as_int8("-1") == -1);
  CHECK(as_int8("-128") == -128);
  CHECK(as_int8("-129") == 0);
  CHECK(as_int8("127") == 127);
  CHECK(as_int8("128") == 0);
}
#endif
