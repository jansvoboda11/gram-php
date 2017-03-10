#include <gram-php/PhpUnserializer.h>

#include <regex>

using namespace std;

PhpLiteral PhpUnserializer::unserialize(string serializedLiteral) const {
  regex booleanPattern("^b:([01]);$");
  regex integerPattern("^i:(-?(?:0|[1-9]+\\d*));$");
  regex decimalPattern("^d:(-?(?:0|[1-9]+\\d*)(?:.[0-9]*(?:[eE][+-][1-9]+\\d*)?)?);$");
  regex stringPattern("^s:(0|[1-9]+\\d*):\"(.*)\";$");

  smatch matches;

  if (regex_match(serializedLiteral, matches, booleanPattern)) {
    if (matches[1] == "0") {
      return PhpLiteral(false);
    }

    if (matches[1] == "1") {
      return PhpLiteral(true);
    }

    throw logic_error("Could not parse serialized boolean.");
  }

  if (regex_match(serializedLiteral, matches, integerPattern)) {
    try {
      int value = stoi(matches[1]);
      return PhpLiteral(value);
    } catch (...) {
      throw logic_error("Could not parse serialized integer.");
    }
  }

  if (regex_match(serializedLiteral, matches, decimalPattern)) {
    try {
      double value = stod(matches[1]);
      return PhpLiteral(value);
    } catch (...) {
      throw logic_error("Could not parse serialized decimal number.");
    }
  }

  if (regex_match(serializedLiteral, matches, stringPattern)) {
    string value = matches[2];
    int length;

    try {
      length = stoi(matches[1]);
    } catch (...) {
      throw logic_error("Could not parse serialized string length.");
    }

    if (length != value.length()) {
      throw logic_error("String length does not match promised length.");
    }

    return PhpLiteral(matches[2]);
  }

  throw logic_error("Could not parse serialized literal.");
}
