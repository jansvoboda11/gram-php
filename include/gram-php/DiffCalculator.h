#ifndef GRAM_DIFF_CALCULATOR
#define GRAM_DIFF_CALCULATOR

#include <string>

class DiffCalculator {
 public:
  double calculate(bool first, bool second) const;
  double calculate(long first, long second) const;
  double calculate(double first, double second) const;
  double calculate(std::string first, std::string second) const;
};

#endif // GRAM_DIFF_CALCULATOR
