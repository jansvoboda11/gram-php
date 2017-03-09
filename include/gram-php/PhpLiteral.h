#ifndef GRAM_PHP_LITERAL
#define GRAM_PHP_LITERAL

#include <string>

#include <gram-php/PhpType.h>

class PhpLiteral {
 public:
  PhpLiteral(bool value);
  PhpLiteral(long value);
  PhpLiteral(double value);
  PhpLiteral(std::string value);
  PhpType type();
  bool booleanValue();
  long integerValue();
  double decimalValue();
  std::string stringValue();
 private:
  PhpType _type;
  bool _booleanValue;
  long _integerValue;
  double _decimalValue;
  std::string _stringValue;
};

#endif // GRAM_PHP_LITERAL
