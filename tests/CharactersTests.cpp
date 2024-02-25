#include <Characters.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Created aggregator is empty", "[characters]") {
  swo::chars::Characters a;
  REQUIRE(a.count() == 0);
}

TEST_CASE("Characters counts added values", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('x');
  a.collect('2');
  REQUIRE(a.count() == 4);
}

TEST_CASE("Characters counts non-letters", "[characters]") {
  swo::chars::Characters a;
  a.collect('1');
  a.collect('2');
  a.collect('3');
  a.collect('4');
  a.collect('5');
  REQUIRE(a.letterFrequency() == Catch::Approx(0));
}

TEST_CASE("Characters counts letters", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('c');
  a.collect('d');
  a.collect('e');
  REQUIRE(a.letterFrequency() == Catch::Approx(1));
}

TEST_CASE("Characters counts letters and non-letters", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('c');
  a.collect('d');
  a.collect('e');
  a.collect('1');
  a.collect('2');
  a.collect('3');
  a.collect('4');
  a.collect('5');
  REQUIRE(a.letterFrequency() == Catch::Approx(0.5));
}

TEST_CASE("Count only numbers", "[characters]") {
  swo::chars::Characters a;
  a.collect('1');
  a.collect('2');
  a.collect('3');
  a.collect('4');
  a.collect('5');
  REQUIRE(a.count() == 5);
}

TEST_CASE("Count only letters", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('c');
  a.collect('d');
  a.collect('e');
  REQUIRE(a.count() == 5);
}

TEST_CASE("Frequency irrational number", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('c');
  a.collect('d');
  a.collect('e');
  a.collect('1');
  a.collect('2');
  REQUIRE(a.letterFrequency() == Catch::Approx((double)5 / 7));
}

TEST_CASE("Frequency certain letter", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  REQUIRE(a.frequencyCertainLetter('a') == Catch::Approx(0.5));
}

TEST_CASE("Frequency certain letter case insensitive", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  REQUIRE(a.frequencyCertainLetter('A') == Catch::Approx(0.5));
}

TEST_CASE("Frequency certain letter irrational number", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('c');
  a.collect('d');
  a.collect('e');
  a.collect('1');
  a.collect('2');
  REQUIRE(a.frequencyCertainLetter('a') == Catch::Approx((double)1 / 7));
}

TEST_CASE("Frequency equal to zero", "[characters]") {
  swo::chars::Characters a;
  a.collect('1');
  a.collect('2');
  a.collect('3');
  a.collect('4');
  a.collect('5');
  REQUIRE(a.frequencyCertainLetter('a') == Catch::Approx(0));
}
TEST_CASE("Letter is not alpha", "[characters]") {
  swo::chars::Characters a;
  REQUIRE_THROWS_AS(a.frequencyCertainLetter('1'), std::invalid_argument);
}
TEST_CASE("Minimum frequency equal to one", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  std::vector<char> data = a.getData();
  REQUIRE(a.getLowestFrequency(data) == Catch::Approx(1));
}

TEST_CASE("Minimum frequency draw", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  std::vector<char> data = a.getData();
  REQUIRE(a.getLowestFrequency(data) == Catch::Approx(0.5));
}

TEST_CASE("Vector Empty", "[characters]") {
  swo::chars::Characters a;
  REQUIRE_THROWS_AS(a.checkIfEmpty(), std::invalid_argument);
}

TEST_CASE("Vector Empty message", "[characters]") {
  swo::chars::Characters a;
  try {
    a.checkIfEmpty();
  } catch (std::invalid_argument& e) {
    REQUIRE(e.what() == std::string("Vector is empty"));
  }
}

TEST_CASE("Get only letters", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('c');
  a.collect('d');
  a.collect('e');
  a.collect('1');
  a.collect('2');
  a.collect('3');
  a.collect('4');
  a.collect('5');
  std::vector<char> letters = {'a', 'b', 'c', 'd', 'e'};
  REQUIRE(a.getLetters() == letters);
}

TEST_CASE("Get only letters empty", "[characters]") {
  swo::chars::Characters a;
  std::vector<char> letters;
  REQUIRE(a.getLetters() == letters);
}

TEST_CASE("Get least frequent letter", "[characters]") {
  swo::chars::Characters a;
  a.collect('a');
  a.collect('b');
  a.collect('c');
  a.collect('d');
  a.collect('e');
  a.collect('1');
  a.collect('2');
  a.collect('3');
  a.collect('4');
  a.collect('5');
  std::vector<char> expected_results = {'a', 'b', 'c', 'd', 'e'};
  std::vector<char> actual_results = a.getLeastFrequentLetter();
  std::sort(expected_results.begin(), expected_results.end());
  std::sort(actual_results.begin(), actual_results.end());
  REQUIRE(expected_results == actual_results);
}

TEST_CASE("Get least frequent letter empty", "[characters]") {
  swo::chars::Characters a;
  std::vector<char> letters;
  REQUIRE_THROWS_AS(a.getLeastFrequentLetter(), std::invalid_argument);
}