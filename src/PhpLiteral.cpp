#include <gram-php/PhpLiteral.h>

#include <stdexcept>

using namespace std;

PhpLiteral::PhpLiteral(bool value) : _type(PhpType::boolean()), _booleanValue(value) {
  //
}

PhpLiteral::PhpLiteral(int value) : _type(PhpType::integer()), _integerValue(value) {
  //
}

PhpLiteral::PhpLiteral(double value) : _type(PhpType::decimal()), _decimalValue(value) {
  //
}

PhpLiteral::PhpLiteral(string value) : _type(PhpType::string()), _stringValue(value) {
  //
}

PhpType PhpLiteral::type() {
  return _type;
}

bool PhpLiteral::booleanValue() {
  if (_type != PhpType::boolean()) {
    throw logic_error("The literal is not a boolean.");
  }

  return _booleanValue;
}

int PhpLiteral::integerValue() {
  if (_type != PhpType::integer()) {
    throw logic_error("The literal is not an integer.");
  }

  return _integerValue;
}

double PhpLiteral::decimalValue() {
  if (_type != PhpType::decimal()) {
    throw logic_error("The literal is not a decimal number.");
  }

  return _decimalValue;
}

std::string PhpLiteral::stringValue() {
  if (_type != PhpType::string()) {
    throw logic_error("The literal is not a string.");
  }

  return _stringValue;
}
