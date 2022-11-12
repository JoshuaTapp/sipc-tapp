#include "TipArray.h"
#include "TipBoolean.h"
#include "TipInt.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("TipArray: Test TipArrays are compared by their underlying term: "
          "Expected = TipInt"
          "[TipArray]") {
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

TEST_CASE("TipArray: Test TipArrays are compared by their underlying term: "
          "Expected = TipBoolean"
          "[TipArray]") {
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

TEST_CASE("TipArray: Test TipArrays are compared by their underlying term: "
          "Expected = TipArray"
          "[TipArray]") {
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
TEST_CASE("TipArray: Test TipArray operators"
          "[TipArray]") {
  auto term = std::make_shared<TipBoolean>();
  TipArray tipArray(term);
  TipArray tipArrayArray(tipArray);

  SECTION("Equal when terms are the same") {
    auto term2 = std::make_shared<TipBoolean>();
    TipArray tipArray2(term2);
    REQUIRE_FALSE(tipArray != tipArray2);
  }

  SECTION("Equal when terms are the same - 2D Array") {
    auto term2 = std::make_shared<TipInt>();
    TipArray tipArray2(term2);
    TipArray tipArrayArray2(tipArray2);
    REQUIRE_FALSE(tipArrayArray == tipArrayArray2);
  }

  SECTION("Not equal when terms are different") {
    auto term3 = std::make_shared<TipInt>();
    TipArray tipArray3(term3);
    REQUIRE(tipArray != tipArray3);
  }

  SECTION("Not equal when terms are different - op(==) returns false") {
    auto term3 = std::make_shared<TipInt>();
    TipArray tipArray3(term3);
    REQUIRE_FALSE(tipArray == tipArray3);
  }

  SECTION("Not equal when terms are different - 2D Array") {
    auto term3 = std::make_shared<TipInt>();
    TipArray tipArray3(term3);
    TipArray tipArrayArray3(tipArray3);
    REQUIRE(tipArrayArray != tipArrayArray3);
  }

  SECTION("Not equal when terms are different - 2D Array - op(==) returns "
          "false") {
    auto term3 = std::make_shared<TipInt>();
    TipArray tipArray3(term3);
    TipArray tipArrayArray3(tipArray3);
    REQUIRE_FALSE(tipArrayArray == tipArrayArray3);
  }
}

TEST_CASE("TipArray: Test arity is one"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);
  REQUIRE(1 == tipArray.arity());
}

TEST_CASE("TipArray: Test arity is one - 2D Array"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);
  TipArray tipArrayArray(tipArray);
  REQUIRE(1 == tipArrayArray.arity());
}

TEST_CASE("TipArray: Test getter - int"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);

  REQUIRE(*term == *tipArray.getArrayType());
}

TEST_CASE("TipArray: Test getter - boolean"
          "[TipArray]") {
  auto term = std::make_shared<TipBoolean>();
  TipArray tipArray(term);

  REQUIRE(*term == *tipArray.getArrayType());
}

TEST_CASE("TipArray: Test getter - 2D Array"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);
  TipArray tipArrayArray(tipArray);

  auto tipArrayArrayTerm =
      std::make_shared<TipArray>(tipArrayArray.getArrayType());

  REQUIRE(*term == *tipArrayArrayTerm->getArrayType());
}

TEST_CASE("TipArray: Test output stream - int"
          "[TipArray]") {
  auto term = std::make_shared<TipInt>();
  TipArray tipArray(term);

  auto expectedValue = "[] int";
  std::stringstream ss;
  ss << tipArray;
  REQUIRE(expectedValue == ss.str());
}

TEST_CASE("TipArray: Test output stream - boolean"
          "[TipArray]") {
  auto term = std::make_shared<TipBoolean>();
  TipArray tipArray(term);

  auto expectedValue = "[] bool";
  std::stringstream ss;
  ss << tipArray;
  REQUIRE(expectedValue == ss.str());
}
