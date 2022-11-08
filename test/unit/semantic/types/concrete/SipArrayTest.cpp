#include "TipArray.h"
#include "TipBoolean.h"
#include "TipInt.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("TipArray: Test TipArrays are compared by their underlying term: Expected = TipInt" "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);

  SECTION("Equal when terms are the same") {
    auto term2 = std::make_shared<TipInt>();
    TipArray tipArray2(term2);
    REQUIRE(tipArray == tipArray2);
  }

  SECTION("Not equal when terms are different") {
    auto term3 = std::make_shared<TipBoolean>();
    TipArray tipArray3(term3);
    REQUIRE_FALSE(tipArray == tipArray3);
  }
}

TEST_CASE("TipArray: Test TipArrays are compared by their underlying term: Expected = TipBoolean" "[TipArray]") {
  auto term = std::make_shared<TipBoolean>();
  TipArray tipArray(term);

  SECTION("Equal when terms are the same") {
    auto term2 = std::make_shared<TipBoolean>();
    TipArray tipArray2(term2);
    REQUIRE(tipArray == tipArray2);
  }

  SECTION("Not equal when terms are different") {
    auto term3 = std::make_shared<TipInt>();
    TipArray tipArray3(term3);
    REQUIRE_FALSE(tipArray == tipArray3);
  }
}

TEST_CASE("TipArray: Test arity is one" "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);
  REQUIRE(1 == tipArray.arity());
}

TEST_CASE("TipArray: Test getter - int" "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);

  REQUIRE(*term == *tipArray.getArrayType());
}

TEST_CASE("TipArray: Test getter - boolean" "[TipArray]") {
  auto term = std::make_shared<TipBoolean>();
  TipArray tipArray(term);

  REQUIRE(*term == *tipArray.getArrayType());
}


TEST_CASE("TipArray: Test output stream - int" "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);

  auto expectedValue = "int[]";
  std::stringstream ss;
  ss << tipArray;
  REQUIRE(expectedValue == ss.str());
}

TEST_CASE("TipArray: Test output stream - boolean" "[TipArray]") {
  auto term = std::make_shared<TipBoolean>();
  TipArray tipArray(term);

  auto expectedValue = "bool[]";
  std::stringstream ss;
  ss << tipArray;
  REQUIRE(expectedValue == ss.str());
}