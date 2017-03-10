#ifndef GRAM_PHP_UNSERIALIZER
#define GRAM_PHP_UNSERIALIZER

#include <string>

#include <gram-php/PhpLiteral.h>

class PhpUnserializer {
 public:
  PhpLiteral unserialize(std::string serializedLiteral) const;
 private:
  PhpLiteral unserializeBoolean(std::string value) const;
  PhpLiteral unserializeInteger(std::string value) const;
  PhpLiteral unserializeDecimal(std::string value) const;
  PhpLiteral unserializeString(std::string value, std::string promisedLength) const;
};

#endif // GRAM_PHP_UNSERIALIZER
