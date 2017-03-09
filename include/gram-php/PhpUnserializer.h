#ifndef GRAM_PHP_UNSERIALIZER
#define GRAM_PHP_UNSERIALIZER

#include <string>

#include <gram-php/PhpLiteral.h>

class PhpUnserializer {
 public:
  PhpLiteral unserialize(std::string serializedLiteral) const;
};

#endif // GRAM_PHP_UNSERIALIZER
