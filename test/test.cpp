#include "../string_utils.h"
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


TEST_CASE("ascii split") {
  using namespace nonstd::string_utils;

  SUBCASE("1") {
    auto v = ascii::split("abcdefghijklmnop", 3);

    CHECK(v.size() == 6);
    CHECK(v[0] == "abc");
    CHECK(v[1] == "def");
    CHECK(v[2] == "ghi");
    CHECK(v[3] == "jkl");
    CHECK(v[4] == "mno");
    CHECK(v[5] == "p");
  }

  SUBCASE("2") {
    auto v = ascii::split("abc,def,ghi,jkl,mno,p", 3, 1);

    CHECK(v.size() == 6);
    CHECK(v[0] == "abc");
    CHECK(v[1] == "def");
    CHECK(v[2] == "ghi");
    CHECK(v[3] == "jkl");
    CHECK(v[4] == "mno");
    CHECK(v[5] == "p");
  }

  SUBCASE("3") {
    auto v = ascii::split("abc,def,ghi,jkl,mno,p", 0);
    CHECK(v.size() == 0);
  }

  SUBCASE("4") {
    auto v = ascii::split("", 1);
    CHECK(v.size() == 0);
  }

  SUBCASE("5") {
    auto v = ascii::split("abc", 1, 1);

    CHECK(v.size() == 2);
    CHECK(v[0] == "a");
    CHECK(v[1] == "c");
  }

  SUBCASE("6") {
    auto v = ascii::split("abc", 1, 2);

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


TEST_CASE("split_keep_empty") {
  using namespace nonstd::string_utils::detail;

  SUBCASE("1") {
    auto v = split_keep_empty("a,b,c", ',');

    CHECK(v.size() == 3);
    CHECK(v[0] == "a");
    CHECK(v[1] == "b");
    CHECK(v[2] == "c");
  }

  SUBCASE("2") {
    auto v = split_keep_empty("", ',');

    CHECK(v.size() == 1);
    CHECK(v[0].empty());
  }

  SUBCASE("3") {
    auto v = split_keep_empty(",", ',');

    CHECK(v.size() == 2);
    CHECK(v[0].empty());
    CHECK(v[1].empty());
  }

  SUBCASE("4") {
    auto v = split_keep_empty(",,", ',');

    CHECK(v.size() == 3);
    CHECK(v[0].empty());
    CHECK(v[1].empty());
    CHECK(v[2].empty());
  }

  SUBCASE("5") {
    auto v = split_keep_empty("a,", ',');

    CHECK(v.size() == 2);
    CHECK(v[0] == "a");
    CHECK(v[1].empty());
  }

  SUBCASE("6") {
    auto v = split_keep_empty(",$", ',');

    CHECK(v.size() == 2);
    CHECK(v[0].empty());
    CHECK(v[1] == "$");
  }

  SUBCASE("7") {
    auto v = split_keep_empty("ab:::b:ccc", ':');

    CHECK(v.size() == 5);
    CHECK(v[0] == "ab");
    CHECK(v[1].empty());
    CHECK(v[2].empty());
    CHECK(v[3] == "b");
    CHECK(v[4] == "ccc");
  }

  SUBCASE("8") {
    auto v = split_keep_empty(",alpha-beta,1-", '-');

    CHECK(v.size() == 3);
    CHECK(v[0] == ",alpha");
    CHECK(v[1] == "beta,1");
    CHECK(v[2].empty());
  }
}


TEST_CASE("split_ignore_empty") {
  using namespace nonstd::string_utils::detail;

  SUBCASE("1") {
    auto v = split_ignore_empty("a,b,c", ',');

    CHECK(v.size() == 3);
    CHECK(v[0] == "a");
    CHECK(v[1] == "b");
    CHECK(v[2] == "c");
  }

  SUBCASE("2") {
    auto v = split_ignore_empty("", ',');

    CHECK(v.size() == 0);
  }

  SUBCASE("3") {
    auto v = split_ignore_empty(",", ',');

    CHECK(v.size() == 0);
  }

  SUBCASE("4") {
    auto v = split_ignore_empty(",,", ',');

    CHECK(v.size() == 0);
  }

  SUBCASE("5") {
    auto v = split_ignore_empty("a,", ',');

    CHECK(v.size() == 1);
    CHECK(v[0] == "a");
  }

  SUBCASE("6") {
    auto v = split_ignore_empty(",$", ',');

    CHECK(v.size() == 1);
    CHECK(v[0] == "$");
  }

  SUBCASE("7") {
    auto v = split_ignore_empty("ab:::b:ccc", ':');

    CHECK(v.size() == 3);
    CHECK(v[0] == "ab");
    CHECK(v[1] == "b");
    CHECK(v[2] == "ccc");
  }

  SUBCASE("8") {
    auto v = split_ignore_empty(",alpha-beta,1-", '-');

    CHECK(v.size() == 2);
    CHECK(v[0] == ",alpha");
    CHECK(v[1] == "beta,1");
  }
}


TEST_CASE("ascii split and split cross check") {
  using namespace nonstd::string_utils;
  const char* s = "123,456,789,3";
  auto v1 = split(s, ',');
  auto v2 = ascii::split(s, 3, 1);
  CHECK(v1.size() == v2.size());
  CHECK(v1[0] == v2[0]);
  CHECK(v1[1] == v2[1]);
  CHECK(v1[2] == v2[2]);
  CHECK(v1[3] == v2[3]);
}
