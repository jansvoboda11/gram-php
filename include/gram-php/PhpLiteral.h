#ifndef GRAM_PHP_LITERAL
#define GRAM_PHP_LITERAL

#include <memory>
#include <string>

#include <gram-php/DiffCalculator.h>
#include <gram-php/PhpType.h>

class PhpLiteral {
 public:
  PhpLiteral(std::string serialized);
  double diff(const PhpLiteral& other, std::shared_ptr<DiffCalculator> diffCalculator) const;
 private:
  bool parseSerializedLiteral(std::string& serializedLiteral);
  bool parseSerializedBoolean() const;
  long parseSerializedInteger() const;
  double parseSerializedDecimal() const;
  std::string parseSerializedString() const;
  PhpType type;
  std::string value;
  static constexpr double TYPE_DIFF = 42.0;
  static constexpr double MAX_DIFF = 1000.0;
};

#endif // GRAM_PHP_LITERAL
