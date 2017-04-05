#ifndef GRAM_PHP_LITERAL
#define GRAM_PHP_LITERAL

#include <string>
#include <vector>

#include <gram-php/PhpType.h>

class PhpLiteral {
 public:
  PhpLiteral();
  PhpLiteral(bool value);
  PhpLiteral(int value);
  PhpLiteral(double value);
  PhpLiteral(std::string value);
  PhpLiteral(std::vector<PhpLiteral> items);
  PhpType type();
  bool booleanValue();
  int integerValue();
  double decimalValue();
  std::string stringValue();
  std::vector<PhpLiteral> arrayValue();
  bool operator==(const PhpLiteral& other) const;
 private:
  PhpType _type;
  bool _booleanValue;
  int _integerValue;
  double _decimalValue;
  std::string _stringValue;
  std::vector<PhpLiteral> _arrayValue;
};

#endif // GRAM_PHP_LITERAL
