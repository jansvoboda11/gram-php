#ifndef GRAM_DIFF_CALCULATOR
#define GRAM_DIFF_CALCULATOR

#include <gram-php/PhpLiteral.h>

class DiffCalculator {
 public:
  double calculate(PhpLiteral first, PhpLiteral second) const;
 private:
  static constexpr double TYPE_DIFF = 1000.0;
};

#endif // GRAM_DIFF_CALCULATOR
