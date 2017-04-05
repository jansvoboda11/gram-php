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

  if (first.type() == PhpType::array()) {
    return calculate(first.arrayValue(), second.arrayValue());
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

double DiffCalculator::calculate(std::vector<PhpLiteral> first, std::vector<PhpLiteral> second) const {
  if (first.size() != second.size()) {
    return COUNT_DIFF;
  }

  double fitness = 0.0;

  for (unsigned long i = 0; i < first.size(); i++) {
    fitness += calculate(first[i], second[i]);
  }

  return fitness;
}
