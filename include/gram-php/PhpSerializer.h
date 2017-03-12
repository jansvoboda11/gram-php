#ifndef GRAM_PHP_SERIALIZER
#define GRAM_PHP_SERIALIZER

#include <string>

#include <gram-php/PhpLiteral.h>

class PhpSerializer {
 public:
  PhpLiteral deserialize(std::string serializedLiteral) const;
 private:
  PhpLiteral deserializeBoolean(std::string value) const;
  PhpLiteral deserializeInteger(std::string value) const;
  PhpLiteral deserializeDecimal(std::string value) const;
  PhpLiteral deserializeString(std::string value, std::string promisedLength) const;
};

#endif // GRAM_PHP_SERIALIZER
