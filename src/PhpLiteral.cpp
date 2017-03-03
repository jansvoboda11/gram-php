#include "../include/PhpLiteral.h"

using namespace std;

PhpLiteral::PhpLiteral(string serialized) : serialized(serialized), type(PhpType::integer()) {
  // parse the type
}

double PhpLiteral::diff(const PhpLiteral& other, shared_ptr<DiffCalculator> diffCalculator) const {
  if (type != other.type) {
    return DIFFERENT_TYPE_DIFF;
  }

  if (type == PhpType::boolean()) {
    // parse values

    bool a = true;
    bool b = false;

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::integer()) {
    // parse values

    long a = 1;
    long b = 2;

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::decimal()) {
    // parse values

    double a = 1.0;
    double b = 2.0;

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::string()) {
    // parse values

    string a = "a";
    string b = "b";

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::array()) {
    double diff = 0.0;

    // iteratively and recursively handle array

    return diff;
  }

  return MAXIMUM_DIFF;
}
