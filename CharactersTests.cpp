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
