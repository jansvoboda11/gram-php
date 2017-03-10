#include <catch.hpp>

#include <gram-php/DiffCalculator.h>

TEST_CASE("Literals with not matching types are assigned big difference") {
  PhpLiteral booleanLiteral(true);
  PhpLiteral integerLiteral(42);

  DiffCalculator calculator;

  double diff = calculator.calculate(booleanLiteral, integerLiteral);

  REQUIRE(diff > 100.0);
}
