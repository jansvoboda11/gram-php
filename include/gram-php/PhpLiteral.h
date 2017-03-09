#ifndef GRAM_PHP_LITERAL
#define GRAM_PHP_LITERAL

#include <string>

#include <gram-php/PhpType.h>

class PhpLiteral {
 public:
  PhpLiteral(bool value);
  PhpLiteral(int value);
  PhpLiteral(double value);
  PhpLiteral(std::string value);
  PhpType type();
  bool booleanValue();
  int integerValue();
  double decimalValue();
  std::string stringValue();
 private:
  PhpType _type;
  bool _booleanValue;
  int _integerValue;
  double _decimalValue;
  std::string _stringValue;
};

#endif // GRAM_PHP_LITERAL
