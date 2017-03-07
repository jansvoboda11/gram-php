#include "../include/PhpLiteral.h"

#include <regex>

using namespace std;

PhpLiteral::PhpLiteral(string serializedLiteral) : type(PhpType::boolean()), value("") {
  if (!parseSerializedLiteral(serializedLiteral)) {
    throw logic_error("Could not recognize serialized literal.");
  }
}

double PhpLiteral::diff(const PhpLiteral& other, shared_ptr<DiffCalculator> diffCalculator) const {
  if (type != other.type) {
    return TYPE_DIFF;
  }

  if (type == PhpType::boolean()) {
    bool a = parseSerializedBoolean();
    bool b = other.parseSerializedBoolean();

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::integer()) {
    long a = parseSerializedInteger();
    long b = other.parseSerializedInteger();

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::decimal()) {
    double a = parseSerializedDecimal();
    double b = other.parseSerializedDecimal();

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::string()) {
    string a = parseSerializedString();
    string b = other.parseSerializedString();

    return diffCalculator->calculate(a, b);
  }

  if (type == PhpType::array()) {
    double diff = 0.0;

    // handle array

    return diff;
  }

  return MAX_DIFF;
}

bool PhpLiteral::parseSerializedLiteral(string& serializedLiteral) {
  regex booleanPattern("^b:([01]);$");
  regex integerPattern("^i:(-?[1-9]+\\d*);$");
  regex decimalPattern("^d:(-?[0-9]+.[0-9]*);$"); // handle 0.
  regex stringPattern("^s:[1-9]+\\d*:\"(.*)\";$");

  smatch matches;

  if (regex_match(serializedLiteral, matches, booleanPattern)) {
    type = PhpType::boolean();
    value = matches[1];

    return true;
  }

  if (regex_match(serializedLiteral, matches, integerPattern)) {
    type = PhpType::integer();
    value = matches[1];

    return true;
  }

  if (regex_match(serializedLiteral, matches, decimalPattern)) {
    type = PhpType::decimal();
    value = matches[1];

    return true;
  }

  if (regex_match(serializedLiteral, matches, stringPattern)) {
    type = PhpType::string();
    value = matches[1];

    return true;
  }

  return false;
}

bool PhpLiteral::parseSerializedBoolean() const {
  if (value == "0") {
    return false;
  } else if (value == "1") {
    return true;
  } else {
    throw logic_error("Could not parse serialized boolean.");
  }
}

long PhpLiteral::parseSerializedInteger() const {
  try {
    return stol(value);
  } catch (...) {
    throw logic_error("Could not parse serialized integer.");
  }
}

double PhpLiteral::parseSerializedDecimal() const {
  try {
    return stod(value);
  } catch (...) {
    throw logic_error("Could not parse serialized decimal number.");
  }
}

std::string PhpLiteral::parseSerializedString() const {
  return value;
}
