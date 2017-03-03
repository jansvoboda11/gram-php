#ifndef GRAM_PHP_LITERAL
#define GRAM_PHP_LITERAL

#include <memory>
#include <string>

#include "DiffCalculator.h"
#include "PhpType.h"

class PhpLiteral {
 public:
  PhpLiteral(std::string serialized);
  double diff(const PhpLiteral& other, std::shared_ptr<DiffCalculator> diffCalculator) const;
 private:
  std::string serialized;
  PhpType type;
  static constexpr double DIFFERENT_TYPE_DIFF = 42.0;
  static constexpr double MAXIMUM_DIFF = 1000.0;
};

#endif // GRAM_PHP_LITERAL
