#include "../include/PhpType.h"

PhpType PhpType::boolean() {
  return PhpType(TYPE_BOOLEAN);
}

PhpType PhpType::integer() {
  return PhpType(TYPE_INTEGER);
}

PhpType PhpType::decimal() {
  return PhpType(TYPE_DECIMAL);
}

PhpType PhpType::string() {
  return PhpType(TYPE_STRING);
}

PhpType PhpType::array() {
  return PhpType(TYPE_ARRAY);
}

PhpType::PhpType(unsigned type) : type(type) {
  //
}

bool PhpType::operator==(const PhpType& other) const {
  return type == other.type;
}

bool PhpType::operator!=(const PhpType& other) const {
  return !operator==(other);
}
