#include <catch.hpp>

#include <gram-php/PhpUnserializer.h>

TEST_CASE("") {
  PhpUnserializer unserializer;

  PhpLiteral literal = unserializer.unserialize("i:1;");

  REQUIRE(literal.type() == PhpType::integer());
  REQUIRE(literal.integerValue() == 1);
}
