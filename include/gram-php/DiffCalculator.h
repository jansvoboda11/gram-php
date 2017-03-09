#ifndef GRAM_DIFF_CALCULATOR
#define GRAM_DIFF_CALCULATOR

#include <gram-php/PhpLiteral.h>

class DiffCalculator {
 public:
  double calculate(PhpLiteral first, PhpLiteral second) const;
};

#endif // GRAM_DIFF_CALCULATOR
