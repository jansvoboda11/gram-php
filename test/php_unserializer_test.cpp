#include <catch.hpp>

#include <gram-php/PhpUnserializer.h>

TEST_CASE("False boolean is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("b:0;");

  REQUIRE(literal.type() == PhpType::boolean());
  REQUIRE(literal.booleanValue() == false);
}

TEST_CASE("True boolean is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("b:1;");

  REQUIRE(literal.type() == PhpType::boolean());
  REQUIRE(literal.booleanValue() == true);
}

TEST_CASE("Not a boolean causes failure") {
  PhpUnserializer unserializer;

  REQUIRE_THROWS(unserializer.unserialize("b:2;"));
}

TEST_CASE("Positive integer is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("i:1;");

  REQUIRE(literal.type() == PhpType::integer());
  REQUIRE(literal.integerValue() == 1);
}

TEST_CASE("Negative integer is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("i:-10;");

  REQUIRE(literal.type() == PhpType::integer());
  REQUIRE(literal.integerValue() == -10);
}

TEST_CASE("Too large integer causes failure") {
  PhpUnserializer unserializer;

  REQUIRE_THROWS(unserializer.unserialize("i:2147483648;"));
}

TEST_CASE("Not an integer causes failure") {
  PhpUnserializer unserializer;

  REQUIRE_THROWS(unserializer.unserialize("i:blah;"));
}

TEST_CASE("Positive decimal number is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("d:12.34;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == 12.34);
}

TEST_CASE("Negative decimal number is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("d:-12.34;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == -12.34);
}

TEST_CASE("Whole decimal number is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("d:1;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == 1.0);
}

TEST_CASE("Decimal number in scientific notation is unserialized") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("d:1.234E+17;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == 123400000000000000.0);
}

TEST_CASE("Not a decimal number causes failure") {
  PhpUnserializer unserializer;

  REQUIRE_THROWS(unserializer.unserialize("d:bl.ah;"));
}
