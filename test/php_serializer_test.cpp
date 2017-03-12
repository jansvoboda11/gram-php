#include <catch.hpp>

#include <gram-php/PhpSerializer.h>

TEST_CASE("False boolean is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("b:0;");

  REQUIRE(literal.type() == PhpType::boolean());
  REQUIRE(literal.booleanValue() == false);
}

TEST_CASE("True boolean is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("b:1;");

  REQUIRE(literal.type() == PhpType::boolean());
  REQUIRE(literal.booleanValue() == true);
}

TEST_CASE("Not a boolean causes failure") {
  PhpSerializer serializer;

  REQUIRE_THROWS(serializer.deserialize("b:2;"));
}

TEST_CASE("Positive integer is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("i:1;");

  REQUIRE(literal.type() == PhpType::integer());
  REQUIRE(literal.integerValue() == 1);
}

TEST_CASE("Negative integer is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("i:-10;");

  REQUIRE(literal.type() == PhpType::integer());
  REQUIRE(literal.integerValue() == -10);
}

TEST_CASE("Zero integer is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("i:0;");

  REQUIRE(literal.type() == PhpType::integer());
  REQUIRE(literal.integerValue() == 0);
}

TEST_CASE("Two-zeroes integer causes failure") {
  PhpSerializer serializer;

  REQUIRE_THROWS(serializer.deserialize("i:00;"));
}

TEST_CASE("Too large integer causes failure") {
  PhpSerializer serializer;

  REQUIRE_THROWS(serializer.deserialize("i:2147483648;"));
}

TEST_CASE("Not an integer causes failure") {
  PhpSerializer serializer;

  REQUIRE_THROWS(serializer.deserialize("i:blah;"));
}

TEST_CASE("Positive decimal number is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("d:12.34;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == 12.34);
}

TEST_CASE("Negative decimal number is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("d:-12.34;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == -12.34);
}

TEST_CASE("Whole decimal number is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("d:1;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == 1.0);
}

TEST_CASE("Decimal number in scientific notation is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("d:1.234E+17;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == 123400000000000000.0);
}

TEST_CASE("Decimal number with one zero before dot is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("d:0.1234;");

  REQUIRE(literal.type() == PhpType::decimal());
  REQUIRE(literal.decimalValue() == 0.1234);
}

TEST_CASE("Decimal number with more zeroes before dot causes failure") {
  PhpSerializer serializer;

  REQUIRE_THROWS(serializer.deserialize("d:00.1234;"));
}

TEST_CASE("Not a decimal number causes failure") {
  PhpSerializer serializer;

  REQUIRE_THROWS(serializer.deserialize("d:bl.ah;"));
}

TEST_CASE("Normal string is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("s:5:\"hello\";");

  REQUIRE(literal.type() == PhpType::string());
  REQUIRE(literal.stringValue() == "hello");
}

TEST_CASE("Zero-length string is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("s:0:\"\";");

  REQUIRE(literal.type() == PhpType::string());
  REQUIRE(literal.stringValue() == "");
}

TEST_CASE("String containing quotation mark is unserialized") {
  PhpSerializer serializer;

  PhpLiteral literal = serializer.deserialize("s:11:\"hello\"world\";");

  REQUIRE(literal.type() == PhpType::string());
  REQUIRE(literal.stringValue() == "hello\"world");
}

TEST_CASE("String with non-matching length causes failure") {
  PhpSerializer serializer;

  REQUIRE_THROWS(serializer.deserialize("s:2:\"hello\";"));
}
