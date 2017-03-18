#include <gram-php/DiffCalculator.h>

#include <cstdlib>

using namespace std;

double DiffCalculator::calculate(PhpLiteral first, PhpLiteral second) const {
  if (first.type() != second.type()) {
    return TYPE_DIFF;
  }

  if (first.type() == PhpType::null()) {
    return 0.0;
  }

  if (first.type() == PhpType::boolean()) {
    return calculate(first.booleanValue(), second.booleanValue());
  }

  if (first.type() == PhpType::integer()) {
    return calculate(first.integerValue(), second.integerValue());
  }

  if (first.type() == PhpType::decimal()) {
    return calculate(first.decimalValue(), second.decimalValue());
  }

  if (first.type() == PhpType::string()) {
    return calculate(first.stringValue(), second.stringValue());
  }

  return 0.0;
}

double DiffCalculator::calculate(bool first, bool second) const {
  return 0.0;
}

double DiffCalculator::calculate(int first, int second) const {
  return abs(first - second);
}

double DiffCalculator::calculate(double first, double second) const {
  return 0.0;
}

double DiffCalculator::calculate(string first, string second) const {
  return 0.0;
}
