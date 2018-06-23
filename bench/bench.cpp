#include "../string_utils.h"
#include "hayai/hayai.hpp"
#include <string>
#include <random>
#include <fstream>


// https://www.youtube.com/watch?v=nXaxk27zwlk#t=40m
[[maybe_unused]] static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }
[[maybe_unused]] static void clobber() { asm volatile("" : : : "memory"); }


class RandomFixture : public hayai::Fixture
{
public:
  virtual void SetUp()
  {
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist{0,9};
    int digit_count = 100;
    int number_count = 100;
    for (int i=0; i<number_count; i++) {
      for (int j=0; j<digit_count; j++)
        s += std::to_string(dist(mt));
      s += ',';
    }
    s.pop_back();  // Remove trailing ','
  }
  virtual void TearDown() {}

  std::string s;
};


class TextFixture : public hayai::Fixture
{
public:
  virtual void SetUp()
  {
    std::ifstream fs{"text/OEB-2016.1-US.txt"};
    if (fs.is_open()) {
      std::stringstream ss;
      ss << fs.rdbuf();
      fs.close();
      text = ss.str();
    }
  }
  virtual void TearDown()
  {
    //std::ofstream fs{"text/replaced.txt"};
    //fs << text;
  }

  std::string text;
};


const char* csv_full = "988862858,689472910,562017896,668351927,222982619,758628814,764514667,"
    "849121270,60621066,584657136,152583039,572948523,777880448,794166280,813407618,293198796,"
    "549147080,987538342,878439310,880215256,826283467,64067515,931266377,426142721,760949057,"
    "889200041,956904446,900698529,627201793,649010313,305704529,809385228,200920601,203840307,"
    "699349343,36287027,434921268,949836050,647387199,971328165,441476752,182686417,776426200,"
    "699013768,899864534,636889809,620669416,858167520,67013303,380791573,76867084,850993214,"
    "362494819,701479279,621357743,52309287,923149453,390049127,964243275,777018907,577844072,"
    "251308834,797833775,785760268,870086147,878862279,306242630,192416754,69072708,594001515,"
    "617112269,943503087,657776166,41483490,83101903,485958323,819716853,437904795,47645936,"
    "7621680,818758136,393870514,988479247,4647226,799562434,519863624,947875927,264011174,"
    "382430321,981813154,698222232,360364977,473166205,348811730,703698476,189316690,179243423";

const char* csv_empty = ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
    ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";

const char* csv_mixed = ",689472910,,,222982619,,764514667,849121270,60621066,,152583039,,,"
    "794166280,813407618,293198796,549147080,987538342,878439310,880215256,,64067515,,,,,,"
    "900698529,627201793,,305704529,,200920601,,,36287027,434921268,949836050,,971328165,"
    "441476752,182686417,776426200,,899864534,,620669416,858167520,,380791573,76867084,850993214,"
    "362494819,701479279,,52309287,923149453,,,,,,,785760268,,878862279,,192416754,,,617112269,"
    "943503087,,,,485958323,819716853,437904795,47645936,7621680,,,988479247,,,519863624,"
    "947875927,,,981813154,,360364977,,,703698476,,";

const char* csv_constw = "116112,117178,129932,138393,151968,155886,163385,167179,174889,"
    "177697,190257,193274,248220,249049,258380,269186,270588,277949,279279,293064,296637,"
    "309054,317856,320514,321361,327076,327390,333643,338108,339869,361778,370175,373660,"
    "374379,395354,398175,399018,425017,436175,460271,461858,462006,476104,479780,484835,"
    "520592,520831,571391,582849,593089,600136,605397,607390,615537,616107,617026,617902,"
    "623960,639227,641958,646462,647224,652650,661655,669272,682496,701867,705980,710775,"
    "719266,732770,733818,736176,736337,741493,755542,757907,766336,773442,782817,784837,"
    "788282,796438,798506,801473,808019,810449,813513,817826,818428,826048,879258,879500,"
    "881416,898259,928830,958558,962443,994418,997562";

const char* leper = R"(On one occasion Jesus was staying in a town, when he saw a man who was
covered with leprosy. When the leper saw Jesus, he threw himself on his face and
implored his help, "Master, if only you are willing, you are able to make me
clean." Stretching out his hand, Jesus touched him, saying as he did so, "I am
willing; become clean."
    Instantly the leprosy left the man; and then Jesus impressed on him that he
was not to say a word to anyone, "but," he added, "set out and show yourself to
the priest, and make the offerings for your cleansing, in the manner directed by
Moses, as evidence of your cure." However, the story about Jesus spread all the
more, and great crowds came together to listen to him, and to be cured of their
illnesses; but Jesus used to withdraw to lonely places and pray.)";


/*
BENCHMARK(string, starts_with, 100, 1000000)
{
  using namespace nonstd::string_utils;
  bool b;
  escape(&b);
  b = starts_with("If you have nothing in quantum mechanics, you will always have something.",
      "If you have nothing in quantum mechanics");
  clobber();
}
*/


BENCHMARK(string, split, 100, 10000)
{
  auto v = nonstd::string_utils::split(csv_constw, ",");
  for (auto sv : v) {
    int i;
    escape(&i);
    i = nonstd::string_utils::as_int(sv);
    clobber();
  }
}


BENCHMARK(string, split_copy, 100, 10000)
{
  auto v = nonstd::string_utils::split_copy(csv_constw, ",");
  for (auto s : v) {
    int i;
    escape(&i);
    i = std::stoi(s);
    clobber();
  }
}


BENCHMARK(string, split_chars, 100, 10000)
{
  auto v = nonstd::string_utils::split_chars(csv_constw, 6, 1);
  for (auto sv : v) {
    int i;
    escape(&i);
    i = nonstd::string_utils::as_int(sv);
    clobber();
  }
}


/*
BENCHMARK_F(TextFixture, replace, 5, 1000)
{
  auto s = nonstd::string_utils::detail::replace(text, "Jesus", "Logos");
}


BENCHMARK_F(TextFixture, replace_inplace, 5, 1000)
{
  auto s = nonstd::string_utils::detail::replace_inplace(text, "Jesus", "Logos");
}
*/


/*
BENCHMARK(string, replace, 100, 100000)
{
  auto s = std::string{"The quick brown fox jumps over the lazy brown dog "
      "and eats a brown apple from a brown tree under a brown sky"};
  escape(&s);
  s = nonstd::string_utils::detail::replace(s, "brown", "blueorangeredgreen");
  clobber();
}


BENCHMARK(string, replace2, 100, 100000)
{
  auto s = std::string{"The quick brown fox jumps over the lazy brown dog "
      "and eats a brown apple from a brown tree under a brown sky"};
  escape(&s);
  s = nonstd::string_utils::detail::replace2(s, "brown", "blueorangeredgreen");
  clobber();
}


BENCHMARK(string, replace_inplace, 100, 10000)
{
  auto s = std::string{"The quick brown fox jumps over the lazy brown dog "
      "and eats a brown apple from a brown tree under a brown sky"};
  escape(&s);
  s = nonstd::string_utils::detail::replace_inplace(s, "brown", "green");
  clobber();
}


BENCHMARK(string, split_for_each, 100, 100000)
{
  nonstd::string_utils::ascii::split_for_each(csv_constw, 6, 1);
}


BENCHMARK_F(RandomFixture, split_at_char, 100, 100000)
{
  nonstd::string_utils::split(s, ',');
}


BENCHMARK_F(RandomFixture, split_at_count, 100, 100000)
{
  nonstd::string_utils::ascii::split(s, 100, 1);
}
*/


int main()
{ 
  hayai::ConsoleOutputter o;
  hayai::Benchmarker::AddOutputter(o);
  hayai::Benchmarker::RunAllTests();

  return 0;
}
