#ifndef GRAM_DIFF_CALCULATOR
#define GRAM_DIFF_CALCULATOR

#include <gram-php/PhpLiteral.h>

class DiffCalculator {
 public:
  double calculate(PhpLiteral first, PhpLiteral second) const;
 private:
  double calculate(bool first, bool second) const;
  double calculate(int first, int second) const;
  double calculate(double first, double second) const;
  double calculate(std::string first, std::string second) const;
  double calculate(std::vector<PhpLiteral> first, std::vector<PhpLiteral> second) const;
  static constexpr double TYPE_DIFF = 1000.0;
  static constexpr double COUNT_DIFF = 10.0;
};

#endif // GRAM_DIFF_CALCULATOR
