#include <gram-php/PhpLiteral.h>

#include <stdexcept>
#include <vector>

using namespace std;

PhpLiteral::PhpLiteral() : _type(PhpType::null()) {
  //
}

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

PhpLiteral::PhpLiteral(vector<PhpLiteral> items) : _type(PhpType::array()), _arrayValue(items) {
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

std::vector<PhpLiteral> PhpLiteral::arrayValue() {
  if (_type != PhpType::array()) {
    throw logic_error("The literal is not an array.");
  }

  return _arrayValue;
}

bool PhpLiteral::operator==(const PhpLiteral &other) const {
  if (_type != other._type) {
    return false;
  }

  if (_type == PhpType::boolean()) {
    return _booleanValue == other._booleanValue;
  }

  if (_type == PhpType::integer()) {
    return _integerValue == other._integerValue;
  }

  if (_type == PhpType::decimal()) {
    return _decimalValue == other._decimalValue;
  }

  if (_type == PhpType::string()) {
    return _stringValue == other._stringValue;
  }

  if (_type == PhpType::array()) {
    return _arrayValue == other._arrayValue;
  }

  return false;
}
